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
    vector<ll> sums;

    void init(int n){
        size = 1;
        while(size < n){
            size *= 2;
        }

        sums.assign(2 * size, 0);
    }
    
    void setRange(int l, int r, int v, int x, int lx, int rx){
        if(l >= rx || lx >= r) return;
        if(lx >= l && rx <= r) {
            sums[x] += v;
            return;
        }
        int mid = (rx + lx) / 2;
        setRange(l, r, v, 2 * x + 1, lx, mid);
        setRange(l, r, v, 2 * x + 2, mid, rx);
        
    }
    void setRange(int l,int r, int v){
        setRange(l, r, v, 0, 0, size);
    }
    
    void calc(int i, int x, int lx, int rx, ll &ans){
        
        if(rx - lx == 1){
            ans += sums[x];
            return;
        } 

        int mid = (rx + lx) / 2;
        if(i < mid){
            calc(i, 2 * x + 1, lx, mid, ans);
        }
        else{
            calc(i, 2 * x + 2, mid, rx, ans);
        }
        ans += sums[x];
    }

    ll calc(int idx){
        ll ans = 0;
        calc(idx, 0, 0, size, ans);
        return ans;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    segmentTree st;
    st.init(n+5);

    while(q--){
        int x;
        cin >> x;
        if(x == 1){
            int l, r, v;
            cin >> l >> r >> v;

            st.setRange(l, r, v);
        }
        else{
            int v;
            cin >> v;
            cout << st.calc(v) << endl;
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