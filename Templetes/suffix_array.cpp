class suffixArray {
    string s;
    int n;
    vector<int> p; // p[i] -> the i-th string (the value is the first position in the suffix)
    vector<int> c; // c[i] -> the class of the i-th smallest string (the class is the group)
 
 
public:
    explicit suffixArray(string &str) : s(str) {
        s += '$';
        n = (int)(s.size());
        p.resize(n), c.resize(n);

        {
            vector<pair<char, int>> a;
            a.reserve(n);
            
            for (int i = 0; i < n; ++i){ 
                a.emplace_back(s[i], i);
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
            vector<pair<pair<int, int>, int>> a;
            a.reserve(n);
            
            for (int i = 0; i < n; ++i) {
                a.push_back({{c[i], c[(i + (1 << k)) % n]}, i});
            }

            sort(a.begin(), a.end());

            for (int i = 0; i < n; i++){
                p[i] = a[i].second;
            }

            c[p[0]] = a[0].second;
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