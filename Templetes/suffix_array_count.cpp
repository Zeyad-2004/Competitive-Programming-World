class suffixArray {
    private:
        string s;
        int n;
        vector<int> p; // p[i] -> the i-th string (the value is the first position in the suffix)
        vector<int> c; // c[i] -> the class of the i-th smallest string (the class is the group)
        vector<int> lcp;

    void countSort(vector<int> &p, vector<int> &c){
        int n = p.size();
    
        vector<int> cnt(n);
        for(auto &x: c){
            cnt[x]++;
        }
    
        vector<int> p_new(n), pos(n);
        pos[0] = 0;
        for(int i = 1; i < n; i++){
            pos[i] = pos[i-1] + cnt[i-1];
        }
    
        for(auto &x: p){
            int i = c[x];
            p_new[pos[i]] = x;
            pos[i]++;
        }
    
        p = p_new;
    }
    void createLcp(){
        lcp.resize(n);
        int k = 0;
        for(int i = 0; i < n-1; i++){
            int pi = this->c[i];
            int j = this->p[pi - 1];
 
            // lcp[i] = lcp(s[i], s[j])
            while(s[i + k] == s[j + k]) k++;
 
            lcp[pi] = k;
            k = max(k - 1, (int)0);
        }
    }
    public:
        explicit suffixArray(string &str) : s(str) {
            s += ' ';
            n = (int)(s.size());
            p.resize(n), c.resize(n);
    
            {
                vector<pair<char, int>> a(n);
                
                for (int i = 0; i < n; ++i){ 
                    a[i] = {s[i], i};
                } // O(n)
    
                sort(a.begin(), a.end());
                
                for (int i = 0; i < n; i++){
                    p[i] = a[i].second; // we can just use a[i].second but for readability
                }
    
                c[p[0]] = 0; // smallest string has class 0
                for (int i = 1; i < n; ++i) {
                    
                    if(a[i].first == a[i-1].first){
                        c[p[i]] = c[p[i-1]];
                    }
                    else{
                        c[p[i]] = c[p[i-1]] + 1;
                    }
                }
            }
            
            int k = 0;
            while ((1 << k) < n) {
                
                for(int i = 0; i < n; i++){
                    p[i] = (p[i] - (1 << k) + n) %n;
                }
    
                countSort(p, c);
    
                vector<int> c_new(n);
                c_new[p[0]] = 0;
    
                for (int i = 1; i < n; ++i) {
                    pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) %n]};
                    pair<int, int> now = {c[p[i]], c[(p[i] + (1 << k)) %n]};
    
                    if(now == prev){
                        c_new[p[i]] = c_new[p[i-1]];
                    }
                    else{
                        c_new[p[i]] = c_new[p[i-1]] + 1;
                    }            
                }
                c = c_new;
                k++;
            }
            createLcp();
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
    };
