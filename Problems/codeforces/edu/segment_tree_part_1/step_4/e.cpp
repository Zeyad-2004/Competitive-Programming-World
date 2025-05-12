#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define ll long long
#define ull unsigned long long
#define ld long double
#define BegEnd(num) num.begin(), num.end()
#define RBegEnd(num) num.rbegin(), num.rend()
#define getVec(arr, size)  vector<int> arr(size); for (auto &input : arr) cin >> input;
#define print(z, n) for (int i=0; (n && i<n ) || ( !n && i<z.size() ) ; i++) cout << z[i] << ' '; cout << endl;
#define F first
#define S second
// #define int ll
#define FIO {ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);}
const int mod = 1e9 + 7, OO = 1e9;

int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
int dy[] = {0, 0, 1, -1, -1, 1, -1, 1};
string dd[] = {"U", "D", "R", "L", "UL", "UR", "DL", "DR"};


struct segmentTree{

    int size;
    vector<int> sums;

    void init(int n){
        size = 1;
        while(size < n){
            size *= 2;
        }

        sums.assign(2 * size, INT_MAX);
    }
    
    void set(int i, int v, int x, int lx, int rx){
        if(rx - lx == 1){
            sums[x] = v;
            return;
        }

        int mid = (rx + lx) / 2;
        if(i < mid){
            set(i, v, 2 * x + 1, lx, mid);
        }
        else{
            set(i, v, 2 * x + 2, mid, rx);
        }

        sums[x] = min(sums[2 * x + 1] , sums[2 * x + 2]);
    }
    void set(int i, int v){
        set(i, v, 0, 0, size);
    }
    
    int calc(int l, int r, int p, int x, int lx, int rx){
        if(l >= rx || lx >= r || sums[x] > p) return 0;
        
        if(rx - lx == 1){
            sums[x] = INT_MAX;
            return 1;
        }
        
        int mid = (rx + lx) / 2;
        auto a = calc(l, r, p, 2 * x + 1, lx, mid);
        auto b = calc(l, r, p, 2 * x + 2, mid, rx);
        
        sums[x] = min(sums[2 * x + 1] , sums[2 * x + 2]);

        return a + b;
    }

    int calc(int l, int r, int p){
        return calc(l, r, p, 0, 0, size);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    segmentTree st;
    st.init(n+5);
    st.set(0, INT_MAX);

    while(q--){
        int x, a, b;
        cin >> x >> a >> b;

        if(x == 1){
            st.set(a, b);
        }
        else{
            int p;
            cin >> p;
            cout << st.calc(a, b, p) << endl;
        }
    }
}   

signed main()
{
    FIO
    #ifdef _3BCAR
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int t = 1;
    // cin >> t;
    for(int i=1; i <= t ; i++)
    {

        solve();
        cout << endl;
    }
//        cerr << clock() / 1000.0 << " Secs";

}

// ####################
// ##### 3BcarenO #####
// ####################