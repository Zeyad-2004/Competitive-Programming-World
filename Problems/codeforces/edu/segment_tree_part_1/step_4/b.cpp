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
#define int ll
#define FIO {ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);}
const int mod = 1e9 + 7, OO = 1e9;

int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
int dy[] = {0, 0, 1, -1, -1, 1, -1, 1};
string dd[] = {"U", "D", "R", "L", "UL", "UR", "DL", "DR"};

struct matrix{
    int a, b, c, d;
};

int r;
struct segmentTree{
    int size;
    vector<matrix> sums;

    matrix combine(matrix a, matrix b){
        return {
            (a.a * b.a + a.b * b.c) % r,
            (a.a * b.b + a.b * b.d) % r,
            (a.c * b.a + a.d * b.c) % r,
            (a.c * b.b + a.d * b.d) % r
        };
    }

    void init(int n){
        size = 1;
        while(size < n){
            size *= 2;
        }

        sums.assign(2 * size, {1, 0, 0, 1});
    }

    void build(vector<matrix> &nums, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < (int)nums.size()) {
                sums[x] = nums[lx];
            }
            return;
        }

        int mid = (rx + lx) / 2;
        build(nums, 2 * x + 1, lx, mid);
        build(nums, 2 * x + 2, mid, rx);

        sums[x] = combine(sums[2 * x + 1] , sums[2 * x + 2]);
    }

    void build(vector<matrix> &nums){
        build(nums, 0, 0, size);
    }

    void set(int i, matrix v, int x, int lx, int rx){
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
        sums[x] = combine(sums[2 * x + 1] , sums[2 * x + 2]);
    }
    void set(int i, matrix v){
        set(i, v, 0, 0, size);
    }

    matrix calc(int l, int r, int x, int lx, int rx){
        if(l >= rx || lx >= r) return {1, 0, 0, 1};
        if(lx >= l && rx <= r) return sums[x];

        int mid = (rx + lx) / 2;
        matrix a = calc(l, r, 2 * x + 1, lx, mid);
        matrix b = calc(l, r, 2 * x + 2, mid, rx);

        return combine(a ,b);
    }

    matrix calc(int l, int r){
        return calc(l, r, 0, 0, size);
    }
};

void print_matrix(matrix a){
    cout << a.a << ' ' << a.b << endl;
    cout << a.c << ' ' << a.d << endl;
}

void solve() {
    int n, q;
    cin >> r >> n >> q;

    segmentTree st;
    st.init(n + 5);

    vector<matrix> have(n);
    for(int i=0; i<n; i++){
        cin >> have[i].a >> have[i].b >> have[i].c >> have[i].d;
    }
    st.build(have);

    while(q--){
        int l, r;
        cin >> l >> r;
        l--;
        print_matrix(st.calc(l, r));
        cout << endl;
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