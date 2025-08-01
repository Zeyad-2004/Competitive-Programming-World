class SuffixArray {
private:
    string s;
    int n;
    vector<int> p;  // Suffix array (sorted suffixes)
    vector<int> c;  // Equivalence classes
    vector<int> lcp; // Longest Common Prefix array
    
    // Counting sort for suffix array construction
    void countSort(vector<int> &p, vector<int> &c) {
        vector<int> cnt(n, 0);
        for (auto x : c) cnt[x]++;
        
        vector<int> p_new(n);
        vector<int> pos(n);
        pos[0] = 0;
        for (int i = 1; i < n; i++)
            pos[i] = pos[i-1] + cnt[i-1];
        
        for (auto x : p) {
            int i = c[x];
            p_new[pos[i]] = x;
            pos[i]++;
        }
        p = p_new;
    }
    
    // Kasai's algorithm for LCP array
    void buildLCP() {
        lcp.resize(n);
        int k = 0;
        for (int i = 0; i < n-1; i++) {
            int pi = c[i];
            int j = p[pi-1];
            
            while (s[i+k] == s[j+k]) k++;
            lcp[pi] = k;
            k = max<ll>(k-1, 0);
        }
    }

public:
    explicit SuffixArray(string &str, char terminal = '$') : s(str) {
        s += terminal;
        n = s.size();
        p.resize(n);
        c.resize(n);
        
        // Initial sorting (k=1)
        {
            vector<pair<char, int>> a(n);
            for (int i = 0; i < n; i++)
                a[i] = {s[i], i};
            
            sort(a.begin(), a.end());
            for (int i = 0; i < n; i++)
                p[i] = a[i].second;
            
            c[p[0]] = 0;
            for (int i = 1; i < n; i++)
                c[p[i]] = (a[i].first == a[i-1].first) ? c[p[i-1]] : c[p[i-1]]+1;
        }
        
        // Iterative doubling (k=2,4,8,...)
        int k = 0;
        while ((1 << k) < n) {
            // Shift positions
            for (int i = 0; i < n; i++)
                p[i] = (p[i] - (1 << k) + n) % n;
            
            countSort(p, c);
            
            vector<int> c_new(n);
            c_new[p[0]] = 0;
            for (int i = 1; i < n; i++) {
                pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << k)) % n]};
                pair<int, int> curr = {c[p[i]], c[(p[i] + (1 << k)) % n]};
                c_new[p[i]] = (curr == prev) ? c_new[p[i-1]] : c_new[p[i-1]]+1;
            }
            c = c_new;
            k++;
        }
        
        buildLCP();
    }
    
    // Accessors
    const vector<int>& getSuffixArray() const { return p; }
    const vector<int>& getLCP() const { return lcp; }
    
    // Utility functions
    void printSuffixes() {
        for (int i = 0; i < n; i++)
            cout << p[i] << ": " << s.substr(p[i]) << endl;
    }
    
    void printLCP() {
        for (int i = 1; i < n; i++)
            cout << lcp[i] << " ";
        cout << endl;
    }
    void printOrder() {
        for (int i = 0; i < n; ++i) {
            cout << p[i] << " \n"[i == n - 1];
        }
    }

    void printStrings() {
        for (int i = 0; i < n; ++i) {
            cout << p[i] << ' ' << s.substr(p[i]) << '\n';
        }
    }

    void printC(){
        for(auto &x: this->c){
            cout << x << ' ';
        }
        cout << endl;
    }
    
    // Applications
    int countDistinctSubstrings() {
        int total = 0;
        for (int i = 1; i < n; i++)
            total += (n - p[i] - 1) - lcp[i];
        return total;
    }
    
    string longestCommonSubstring(string &s1, string &s2) {
        string combined = s1 + "$" + s2;
        SuffixArray sa(combined, '#');
        const vector<int>& sa_vec = sa.getSuffixArray();
        const vector<int>& lcp_vec = sa.getLCP();
        
        int max_len = 0, pos = -1;
        int s1_len = s1.size();
        
        for (int i = 1; i < sa_vec.size(); i++) {
            if ((sa_vec[i-1] < s1_len && sa_vec[i] > s1_len) || 
                (sa_vec[i] < s1_len && sa_vec[i-1] > s1_len)) {
                if (lcp_vec[i] > max_len) {
                    max_len = lcp_vec[i];
                    pos = min(sa_vec[i-1], sa_vec[i]);
                }
            }
        }
        
        return (max_len > 0) ? combined.substr(pos, max_len) : "";
    }
};