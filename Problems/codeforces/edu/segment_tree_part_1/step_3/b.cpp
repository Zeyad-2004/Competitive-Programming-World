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
    vector<long long> sums;
    void init(int n){
        size = 1;
        while(size < n){
            size *= 2;
        }

        sums.assign(2 * size, 0LL);
    }

    void build(vector<int> &nums, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < (int)nums.size()) {
                sums[x] = 1;
            }
            return;
        }

        int mid = (rx + lx) / 2;
        build(nums, 2 * x + 1, lx, mid);
        build(nums, 2 * x + 2, mid, rx);

        sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
    }

    void build(vector<int> &nums){
        build(nums, 0, 0, size);
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
        sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
    }
    void set(int i, int v=1){
        set(i, v, 0, 0, size);
    }

    void getRev(int target, int x, int lx, int rx, int have, int &ans){
        if(~ans) return;
        if(rx - lx == 1){
            if(sums[x] && have + 1 == target) ans = lx+1;
            return;
        }
        
        int mid = (rx + lx) / 2;
        if(have + sums[2 * x + 1] >= target){
            getRev(target, 2 * x + 1, lx, mid, have, ans);
        }
        else{
            getRev(target, 2 * x + 2, mid, rx, have + sums[2 * x + 1], ans);
        }

    }
    int getRev(int val, int len){
        int ans = -1;
        getRev(len - val, 0, 0, size, 0, ans);
        return ans;
    }
};


void solve() {
    int n;
    cin >> n;
    getVec(num, n);
    reverse(BegEnd(num));

    segmentTree st;
    st.init(n);
    st.build(num);
    // for(int i=0; i<n; i++) st.set(i, 1);
        
    vector<int> ans;
    for(auto &x: num){
        ans.push_back(st.getRev(x, n - ans.size()));
        st.set(ans.back()-1, 0);
    }
    reverse(BegEnd(ans));
    print(ans, 0);
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