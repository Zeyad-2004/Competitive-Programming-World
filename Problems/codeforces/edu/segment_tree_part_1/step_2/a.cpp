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

struct item{
    long long seg, pref, suf, sum;
};

struct segmentTree{
    int size;
    vector<item> values;

    item NEUTRAL_ELEMENT = {0,0,0,0};

    item merge(item a, item b){
        return {
            max(a.seg, max(b.seg, a.suf + b.pref)),
            max(a.pref, a.sum + b.pref),
            max(b.suf, b.sum + a.suf),
            a.sum + b.sum
        };
    }

    item single(int v){
        if (v > 0){
            return {v, v, v, v};
        }
        else{
            return {0, 0, 0, v};
        }
    }
    void init(int n){
        size = 1;
        while(size < n){
            size *= 2;
        }

        values.resize(2 * size);
    }

    void build(vector<int> &nums, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < (int)nums.size()) {
                values[x] = single(nums[lx]);
            }
            return;
        }

        int mid = (rx + lx) / 2;
        build(nums, 2 * x + 1, lx, mid);
        build(nums, 2 * x + 2, mid, rx);

        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void build(vector<int> &nums){
        build(nums, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx){
        if(rx - lx == 1){
            values[x] = single(v);
            return;
        }
        int mid = (rx + lx) / 2;
        if(i < mid){
            set(i, v, 2 * x + 1, lx, mid);
        }
        else{
            set(i, v, 2 * x + 2, mid, rx);
        }
        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }
    void set(int i, int v){
        set(i, v, 0, 0, size);
    }

    item calc(int l, int r, int x, int lx, int rx){
        if(lx >= r || l >= rx) return NEUTRAL_ELEMENT;
        if(lx >= l && rx <= r) return values[x];

        int mid = (lx+rx)/2;
        item s1 = calc(l, r, 2 * x + 1, lx, mid);
        item s2 = calc(l, r, 2 * x + 2, mid, rx);
        
        return merge(s1, s2);
    }

    item calc(int l, int r){
        return calc(l, r, 0, 0, size);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    getVec(num, n);

    segmentTree st;
    st.init(n);
    st.build(num);
    // for(int i=0; i<n; i++){
    //     st.set(i, num[i]);
    // }

    cout << st.calc(0, n).seg << endl;
    while(q--){
        int a, b;
        cin >> a >> b;

        st.set(a, b);
        cout << st.calc(0, n).seg << endl;
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