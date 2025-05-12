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
//#define int ll
#define FIO {ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);}
const int mod = 1e9 + 7, OO = 1e9;

int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
int dy[] = {0, 0, 1, -1, -1, 1, -1, 1};
string dd[] = {"U", "D", "R", "L", "UL", "UR", "DL", "DR"};

struct segmentTree{
    int size;
    vector<pair<int, int>> sums;
    void init(int n){
        size = 1;
        while(size < n){
            size *= 2;
        }

        sums.assign(2 * size, {INT_MAX, 1});
    }

    pair<int, int> get_min_count(pair<int, int> a, pair<int, int> b){
        if(a.F == b.F) return {a.F, a.S + b.S};
        else if(a.F < b.F) return a;
        else return b;
    }

    void build(vector<int> &nums, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < (int)nums.size()) {
                sums[x] = {nums[lx], 1};
            }
            return;
        }

        int mid = (rx + lx) / 2;
        build(nums, 2 * x + 1, lx, mid);
        build(nums, 2 * x + 2, mid, rx);


        sums[x] = get_min_count(sums[2 * x + 1], sums[2 * x + 2]);
    }

    void build(vector<int> &nums){
        build(nums, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx){
        if(rx - lx == 1){
            sums[x] = {v, 1};
            return;
        }
        int mid = (rx + lx) / 2;
        if(i < mid){
            set(i, v, 2 * x + 1, lx, mid);
        }
        else{
            set(i, v, 2 * x + 2, mid, rx);
        }

        sums[x] = get_min_count(sums[2 * x + 1], sums[2 * x + 2]);
    }
    void set(int i, int v){
        set(i, v, 0, 0, size);
    }

    pair<int, int> min_count(int l, int r, int x, int lx, int rx){
        if(l >= rx || lx >= r) return {INT_MAX, 1};
        if(lx >= l && rx <= r) return sums[x];

        int mid = (rx + lx) / 2;
        auto a = min_count(l, r, 2 * x + 1, lx, mid);
        auto b = min_count(l, r, 2 * x + 2, mid, rx);

        return get_min_count(a, b);

    }
    pair<int, int> min_count(int l, int r){
        return min_count(l, r, 0, 0, size);
    }
};


void solve() {
    int n, q;
    cin >> n >> q;
    getVec(num, n);

    segmentTree st;
    st.init(n);
    st.build(num);

    while(q--){
        int a, b, c;
        cin >> a >> b >> c;

        if(a == 1){
            st.set(b, c);
        }
        else{
            auto ans = st.min_count(b, c);
            cout << ans.F << ' ' << ans.S << endl;
        }
    }
}

signed main()
{
    FIO

    int t = 1;
//    cin >> t;
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