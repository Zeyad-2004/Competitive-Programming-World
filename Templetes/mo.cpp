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

struct query{
    int l, r, idx;

    query(){};
};


void solve(){
    int n, q, k;
    cin >> n >> q >> k;
    getVec(num, n);
    
    int Z = sqrt(n) + 1;
    
    vector<int> ans(q);
    vector<query> qu(q);

    for(int i=0, l, r; i<q; i++){
        cin >> l >> r;
        l--, r--;
        qu[i].l = l, qu[i].r = r, qu[i].idx = i;
    }

    sort(BegEnd(qu), [&](query &a, query &b){
        if(a.l / Z == b.l / Z){
            return a.r < b.r;
        }
        else{
            return a.l < b.l;
        }
    });

    ll tmp = 0;
    auto add = [&](int idx){
        // code
    };
    auto rem = [&](int idx){
        // code
    };

    int l = 0, r = -1;
    for(auto &x: qu){
        while(l > x.l){
            l--;
            add(l);
        }
        while(r < x.r){
            r++;
            add(r);
        }
        while(r > x.r){
            rem(r);
            r--;
        }
        while(l < x.l){
            rem(l);
            l++;
        }
        ans[x.idx] = tmp;
    }

    for(auto &x: ans) cout << x << endl;
}


signed main()
{
    FIO
    
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    int t = 1;
    // cin >> t;
    for(int i=1; i <= t ; i++)
    {
        solve();
        // cout << endl;
    }
    //   cerr << clock() / 1000.0 << " Secs";
 
}
 
// ####################
// ##### 3BcarenO #####
// ####################