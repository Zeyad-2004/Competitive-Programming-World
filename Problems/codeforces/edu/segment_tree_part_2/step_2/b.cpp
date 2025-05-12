#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define ll long long
#define ull unsigned long long
#define ld long double
#define BegEnd(num) num.begin(), num.end()
#define RBegEnd(num) num.rbegin(), num.rend()

#define getVec(arr, size)   \
    vector<int> arr(size);  \
    for (auto &input : arr) \
        cin >> input;

#define print(z, n)                                            \
    for (int i = 0; (n && i < n) || (!n && i < z.size()); i++) \
        cout << z[i] << ' ';                                   \
    cout << endl;

#define F first
#define S second
// #define int ll

#define FIO                               \
    {                                     \
        ios_base::sync_with_stdio(false); \
        cin.tie(nullptr);                 \
        cout.tie(nullptr);                \
    }

const int M = 1e9 + 7, OO = 1e9;

int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
int dy[] = {0, 0, 1, -1, -1, 1, -1, 1};
string dd[] = {"U", "D", "R", "L", "UL", "UR", "DL", "DR"};


struct segmentTree{
    int size;
    vector<long long> values, operations;
    long long NEUTRAL_ELEMENT = 0;


    void init(int n){
        size = 1;
        while(size < n){
            size *= 2;
        }

        values.assign(2 * size, 0LL);
        operations.assign(2 * size, 1LL);
    }

    long long modify(long long a, long long b){
        return (a * b) %M;
    }

    long long calc(long long a, long long b){
        return (a + b) %M;
    }

    void apply_mod(long long &a, long long b){
        a = modify(a, b);
    }

    void build(int x, int lx, int rx){
        if(rx - lx == 1){
            values[x] = 1;
            return;
        }

        int mid = (rx + lx) / 2;
        build(2 * x + 1, lx, mid);
        build(2 * x + 2, mid, rx);

        values[x] = calc(values[2 * x + 1], values[2 * x + 2]);
    }

    void build(){
        build(0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx){
        if(rx - lx == 1){
            values[x] = v;
            return;
        }
        int mid = (rx + lx) / 2;
        if(i < mid){
            set(i, v, 2 * x + 1, lx, mid);
        }
        else{
            set(i, v, 2 * x + 2, mid, rx);
        }
        values[x] = values[2 * x + 1] + values[2 * x + 2];
    }
    void set(int i, int v){
        set(i, v, 0, 0, size);
    }
    
    void update(int l, int r, int v, int x, int lx, int rx){
        if(lx >= r || rx <= l) return;
        if(lx >= l && rx <= r){
            apply_mod(values[x], v);
            apply_mod(operations[x], v);
            return;
        }

        int mid = (rx + lx) / 2;
        update(l, r, v, 2 * x + 1, lx, mid);
        update(l, r, v, 2 * x + 2, mid, rx);

        values[x] = calc(values[2*x + 1], values[2*x + 2]);
        apply_mod(values[x], operations[x]);
    }

    void update(int l, int r, int v){
        update(l, r, v, 0, 0, size);
    }

    long long sum(int l, int r, int x, int lx, int rx){
        if(l >= rx || lx >= r) return NEUTRAL_ELEMENT;
        if(lx >= l && rx <= r) return values[x];

        int mid = (rx + lx) / 2;
        long long a = sum(l, r, 2 * x + 1, lx, mid);
        long long b = sum(l, r, 2 * x + 2, mid, rx);

        long long res = calc(a, b);
        apply_mod(res, operations[x]);

        return res;
    }

    long long sum(int l, int r){
        return sum(l, r, 0, 0, size);
    }
};


void solve(){
    int n, m;
    cin >> n >> m;

    segmentTree st;
    st.init(n+5);
    st.build();

    while(m--){
        int x, l, r, v;
        cin >> x >> l >> r;

        if(x == 1){
            cin >> v;
            st.update(l, r, v);
        }
        else{
            cout << st.sum(l, r) << endl;
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
    for (int i = 1; i <= t; i++)
    {

        solve();
        cout << endl;
    }
    //        cerr << clock() / 1000.0 << " Secs";
}

// ####################
// ##### 3BcarenO #####
// ####################