
class suffixArray {
    private:
        string s;
        int n;
        vector<int> p; // p[i] -> the i-th string (the value is the first position in the suffix)
        vector<int> c; // c[i] -> the class of the i-th smallest string (the class is the group)
    
        void radixSort(vector<pair<pair<int, int>, int>> &a){
    
            {
                vector<int> cnt(n);
                for (auto x : a) {
                    cnt[x.first.second]++;
                }
                vector<pair<pair<int, int>, int>> a_new(n);
                vector<int> pos(n);
                pos[0] = 0;
                for (int i=1; i<n; i++) {
                    pos[i] = pos[i-1] + cnt[i-1];
                }
                for (auto x: a) {
                    int i = x.first.second;
                    a_new[pos[i]] = x;
                    pos[i]++;
                }
                a = a_new;
            }
                {
                vector<int> cnt(n);
                for (auto x : a) {
                    cnt[x.first.first]++;
                }
                vector<pair<pair<int, int>, int>> a_new(n);
                vector<int> pos(n);
                pos[0] = 0;
                for (int i=1; i<n; i++) {
                    pos[i] = pos[i-1] + cnt[i-1];
                }
                for (auto x: a) {
                    int i = x.first.first;
                    a_new[pos[i]] = x;
                    pos[i]++;
                }
                a = a_new;
            }
        }
     
    public:
        explicit suffixArray(string &str) : s(str) {
            s += '$';
            n = (int)(s.size());
            p.resize(n), c.resize(n);
    
            {
                vector<pair<char, int>> a(n);
                
                for (int i = 0; i < n; ++i){ 
                    a[i] = {s[i], i};
                }
    
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
                vector<pair<pair<int, int>, int>> a(n); 
    
                for (int i = 0; i < n; i++) {
                    a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
                }
    
                radixSort(a);
    
                for (int i = 0; i < n; i++){
                    p[i] = a[i].second;
                }
    
                c[p[0]] = 0;
                for (int i = 1; i < n; ++i) {
                
                    if(a[i].first == a[i-1].first){
                        c[p[i]] = c[p[i-1]];
                    }
                    else{
                        c[p[i]] = c[p[i-1]] + 1;
                    }            
                }
                k++;
            }
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
    };
    