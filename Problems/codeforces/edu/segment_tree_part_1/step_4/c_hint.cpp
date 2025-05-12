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

struct each{
    int freq[44];
    ll cnt;
};

int r;
struct segmentTree{

    int size;
    vector<each> sums;

    each combine(each a, each b){
        each result;
        memset(result.freq, 0, sizeof(result.freq));

        for(int i=0; i < 44; i++){
            result.freq[i] = a.freq[i] + b.freq[i];
        }
        result.cnt = a.cnt + b.cnt;

        for (int i = 0; i < 44; i++){
            for (int j = i+1; j < 44; j++){
                result.cnt += a.freq[j] * b.freq[i];
            }
            
        }
        
        return result;
    }

    
    each start;
    void init(int n){
        size = 1;
        while(size < n){
            size *= 2;
        }

        sums.assign(2 * size, start);
    }

    void build(vector<int> &nums, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < (int)nums.size()) {
                memset(sums[x].freq, 0, sizeof(sums[x].freq));
                sums[x].freq[nums[lx]]++;
                sums[x].cnt = 0;
            }
            return;
        }
        
        int mid = (rx + lx) / 2;
        build(nums, 2 * x + 1, lx, mid);
        build(nums, 2 * x + 2, mid, rx);
        
        sums[x] = combine(sums[2 * x + 1] , sums[2 * x + 2]);
    }
    
    void build(vector<int> &nums){
        memset(start.freq, 0, sizeof start.freq);
        start.cnt = 0;
        
        build(nums, 0, 0, size);
    }
    
    void set(int i, int v, int x, int lx, int rx){
        if(rx - lx == 1){
            memset(sums[x].freq, 0, sizeof(sums[x].freq));
            sums[x].freq[v]++;
            sums[x].cnt=0;
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
    void set(int i, int v){
        set(i, v, 0, 0, size);
    }

    each calc(int l, int r, int x, int lx, int rx){
        if(l >= rx || lx >= r) return start;
        if(lx >= l && rx <= r) return sums[x];

        int mid = (rx + lx) / 2;
        auto a = calc(l, r, 2 * x + 1, lx, mid);
        auto b = calc(l, r, 2 * x + 2, mid, rx);

        return combine(a ,b);
    }

    ll calc(int l, int r){
        return calc(l, r, 0, 0, size).cnt;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    getVec(num, n);

    segmentTree st;
    st.init(n+5);
    st.build(num);

    while(q--){
        int x, a, b;
        cin >> x >> a >> b;
        a--;

        if(x == 1){
            cout << st.calc(a, b) << endl;
        }
        else{
            st.set(a, b);
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