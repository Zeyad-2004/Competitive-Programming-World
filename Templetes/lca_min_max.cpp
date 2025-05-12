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
 
const int LOG = 20;
const int MAX_N = 2e5 + 10;
int up[MAX_N][LOG];
int depth[MAX_N];

vector<vector<int>> mn, mx;


void dfs(int a, int p, vector<vector<pair<int, int>>> &adj) {
    
	for(auto [x, y] : adj[a]) {
        if(x == p) continue;
        
		depth[x] = depth[a] + 1;
		up[x][0] = a;
        
        mn[x][0] = y;
        mx[x][0] = y;
		for(int j = 1; j < LOG; j++) {
			up[x][j] = up[up[x][j-1]][j-1];

            mn[x][j] = min({mn[x][j-1], y, mn[up[x][j-1]][j-1]});
            mx[x][j] = max({mx[x][j-1], y, mx[up[x][j-1]][j-1]});
		}
		dfs(x, a, adj);
	}
}
 
int get_lca(int a, int b){
    if(depth[a] < depth[b]) swap(a, b);
    
    int diff = depth[a] - depth[b];
    
    for(int i = 0; i < LOG; i++){
        if(diff & (1 << i)){
            a = up[a][i];
        }
    }
    
    if(a == b) return a;
    
    for(int i = LOG-1; i >= 0; i--){
        if(up[a][i] != up[b][i]){
            a = up[a][i];
            b = up[b][i];
        }
    }
    
    return up[a][0];
}
 
pair<int, int> getKthAncestor(int node, int k) {
    if(k > depth[node]){
        return {-1, -1};
    }
    else{
        pair<int, int> ret = {INT_MAX, 0};
        for(int i=0; i < LOG; i++){
            if(k & (1 << i)){
                ret.F = min(ret.F, mn[node][i]);
                ret.S = max(ret.S, mx[node][i]);
                
                node = up[node][i];
            }
        }
        return ret;
    }
}
void solve(){
    mn = vector<vector<int>>(MAX_N, vector<int>(LOG, INT_MAX));
    mx = vector<vector<int>>(MAX_N, vector<int>(LOG, 0));

    int n;
    cin >> n;
    vector<vector<pair<int, int>>> adj(n);
    for(int i = 0; i < n-1; i++){
        int a, b, w;
        cin >> a >> b >> w;
        a--; b--;
        adj[a].push_back({b, w});
        adj[b].push_back({a, w});
    }

    dfs(0, 0, adj);

    int q;
    cin >> q;
    while(q--){
        int a, b;
        cin >> a >> b;
        a--, b--;
       
        int lca = get_lca(a, b);
        auto aa = getKthAncestor(a, depth[a] - depth[lca]);
        auto bb = getKthAncestor(b, depth[b] - depth[lca]);

        cout << min(aa.F, bb.F) << " " << max(aa.S, bb.S) << endl;
    }
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
        cout << endl;
    }
    //    cerr << clock() / 1000.0 << " Secs";
 
}
 
// ####################
// ##### 3BcarenO #####
// ####################