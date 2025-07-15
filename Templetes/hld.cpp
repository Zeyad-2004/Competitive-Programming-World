struct HLD
{

    vector<int> big, head, sz, par, id, dep;

    void dfs(int v, const vector<vector<int>> &adj)
    {
        for (int u : adj[v])
        {
            if (u == par[v])
                continue;

            par[u] = v;
            dep[u] = dep[v] + 1;
            dfs(u, adj);
            sz[v] += sz[u];
            if (big[v] == 0 || sz[u] > sz[big[v]])
                big[v] = u;
        }
    }
    void flatten(int v, const vector<vector<int>> &adj, int &nxt)
    {
        id[v] = nxt++;
        if (big[v])
            head[big[v]] = head[v], flatten(big[v], adj, nxt); // heavy edge

        for (int u : adj[v])
        {
            if (u == par[v] || u == big[v])
                continue;
            // light edge
            head[u] = u;
            flatten(u, adj, nxt);
        }
    }

    HLD(int n, const vector<vector<int>> &adj) : big(n + 1), head(n + 1), sz(n + 1, 1), par(n + 1, 0), id(n + 1), dep(n + 1, 0)
    {
        dfs(1, adj);
        int nxt = 0;
        head[1] = 1;
        flatten(1, adj, nxt);
    }

    vector<pair<int, int>> path(int u, int v)
    {
        vector<pair<int, int>> res;

        while (true)
        {
            if (head[u] == head[v])
            {
                if (dep[u] > dep[v])
                    swap(u, v);

                res.emplace_back(id[u], id[v]);
                return res;
            }
            if (dep[head[u]] > dep[head[v]])
                swap(u, v);

            res.emplace_back(id[head[v]], id[v]);
            v = par[head[v]];
        }
    }
};