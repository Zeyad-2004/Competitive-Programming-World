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
    vector<int> values;
    void init(int n){
        size = 1;
        while(size < n){
            size *= 2;
        }

        values.assign(2 * size, 0);
    }

    void build(vector<int> &nums, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < (int)nums.size()) {
                values[x] = nums[lx];
            }
            return;
        }

        int mid = (rx + lx) / 2;
        build(nums, 2 * x + 1, lx, mid);
        build(nums, 2 * x + 2, mid, rx);

        values[x] = max(values[2 * x + 1], values[2 * x + 2]);
    }

    void build(vector<int> &nums){
        build(nums, 0, 0, size);
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
        values[x] = max(values[2 * x + 1], values[2 * x + 2]);
    }
    void set(int i, int v){
        set(i, v, 0, 0, size);
    }

    void mx(int v, int x, int lx, int rx, int &ans){
        if(~ans || values[x] < v) return;
        if(rx - lx == 1){
            if(values[x] >= v) ans = lx;

            return;
        }

        int mid = (rx + lx) / 2;
        if(values[2 * x + 1] >= v){
            mx(v, 2 * x + 1, lx, mid, ans);
        }
        else if(values[2 * x + 2] >= v){
            mx(v, 2 * x + 2, mid, rx, ans);
        }

    }

    long long mx(int v){
        int ans = -1;
        mx(v, 0, 0, size, ans);
        return ans;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    getVec(num, n);

    segmentTree st;
    st.init(n);
    // st.build(num);
    for(int i=0; i<n; i++){
        st.set(i, num[i]);
    }

    while(q--){
        int a, b, c;
        cin >> a >> b;

        if(a == 1){
            cin >> c;
            if(c != num[b]){
                st.set(b, c);
                num[b] = c;
            }
        }
        else{
            int ans = st.mx(b);
            cout << ans << endl;
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