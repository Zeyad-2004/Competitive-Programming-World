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
        set(i-1, v, 0, 0, size);
    }

    long long sum(int l, int r, int x, int lx, int rx){
        if(l >= rx || lx >= r) return 0;
        if(lx >= l && rx <= r) return sums[x];

        int mid = (rx + lx) / 2;
        long long a = sum(l, r, 2 * x + 1, lx, mid);
        long long b = sum(l, r, 2 * x + 2, mid, rx);

        return a + b;
    }

    long long sum(int l, int r){
        return sum(l, r, 0, 0, size);
    }

};


void solve() {
    
    int n;
    cin >> n;
    getVec(num, n*2);

    segmentTree st;
    st.init(2*n);

    vector<int> prev(n+1, -1);
    vector<int> ans(n);
    for(int i=0; i < 2*n; i++){
        if(~prev[num[i]]){
            ans[num[i]-1] = st.sum(prev[num[i]], i);
            st.set(prev[num[i]], 1);
        }
        else{
            prev[num[i]] = i;
        }
    }
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