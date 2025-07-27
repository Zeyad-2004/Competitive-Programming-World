struct LCA {
    int n;
    const int LOG = 20;
    vector<vector<pair<int, int>>> adj;
    vector<vector<int>> up, mn, mx;
    vector<int> depth, total;

    LCA(int _n) : n(_n) {
        adj.resize(n);
        total.resize(n);
        up.assign(n, vector<int>(LOG));
        mn.assign(n, vector<int>(LOG, INT_MAX));
        mx.assign(n, vector<int>(LOG, 0));
        depth.assign(n, 0);
    }

    void addEdge(int u, int v, int w = 0) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    void dfs(int node, int parent) {
        total[node] += total[parent];

        for (auto [child, weight] : adj[node]) {
            if (child == parent) continue;

            depth[child] = depth[node] + 1;
            up[child][0] = node;
            mn[child][0] = weight;
            mx[child][0] = weight;

            total[child] += weight;
            for (int j = 1; j < LOG; j++) {
                up[child][j] = up[up[child][j - 1]][j - 1];
                mn[child][j] = min(mn[child][j - 1], mn[up[child][j - 1]][j - 1]);
                mx[child][j] = max(mx[child][j - 1], mx[up[child][j - 1]][j - 1]);
            }

            dfs(child, node);
        }
    }

    void build(int root = 0) {
        up[root][0] = root;
        dfs(root, root);
    }

    int getLCA(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        int diff = depth[a] - depth[b];
        for (int i = 0; i < LOG; i++) {
            if (diff & (1 << i))
                a = up[a][i];
        }

        if (a == b) return a;

        for (int i = LOG - 1; i >= 0; i--) {
            if (up[a][i] != up[b][i]) {
                a = up[a][i];
                b = up[b][i];
            }
        }

        return up[a][0];
    }

    int getKthAncestor(int node, int k) {
        if(k > depth[node]){
            return -1;
        }
        
        for(int i=0; i < LOG; i++){
            if(k & (1 << i)){
                node = up[node][i];
            }
        }
        return node;
    }

    pair<int, int> getKthMinMax(int node, int k) {
        if (k > depth[node]) return {-1, -1};
        pair<int, int> ret = {INT_MAX, 0};

        for (int i = 0; i < LOG; i++) {
            if (k & (1 << i)) {
                ret.first = min(ret.first, mn[node][i]);
                ret.second = max(ret.second, mx[node][i]);
                node = up[node][i];
            }
        }

        return ret;
    }

    // Returns {minEdge, maxEdge} on path between a and b
    pair<int, int> getMinMaxEdgeOnPath(int a, int b) {
        int lca = getLCA(a, b);
        auto aa = getKthMinMax(a, depth[a] - depth[lca]);
        auto bb = getKthMinMax(b, depth[b] - depth[lca]);

        return {min(aa.first, bb.first), max(aa.second, bb.second)};
    }
};
