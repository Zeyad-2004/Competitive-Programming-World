
class DSU {

public:
    vector <int> par;
    vector<vector<int>> group;
    DSU(int __N) {
        par.resize(__N + 1);
        group.resize(__N + 1);
        for(int i = 0; i <= __N; i++) {
            group[i].push_back(i);
            par[i] = i;
        }
    }
    
    int find(int u) {
        if(par[u] == u) return u;
        return par[u] = find(par[u]);
    }
    
    bool unite(int s, int t) {
        t = find(t), s = find(s);
    
        if(s == t) return false;
        if(group[t].size() < group[s].size())
            swap(t, s);
    
        for(auto i: group[s])
            group[t].push_back(i);
    
        group[s].clear();
        par[s] = t;
    
        return true;
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    vector<vector<int>> boundries(){
        map<int, vector<int>> tmp;
        vector<vector<int>> ret;
        for(int i = 1; i < group.size()-1; i++){
            tmp[find(i)].push_back(i);
        }
        for(auto &[a, b]: tmp) ret.push_back(b);
        return ret;
    }
};
    
struct Edge {
    int u, v, weight, idx;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};
 
class MST {
private:
    int n;
    std::vector<Edge> edges;
 
public:
    MST(int nodes){
        n = nodes;
    }
 
    void addEdge(int u, int v, int weight, int idx) {
        edges.push_back({u, v, weight, idx});
    }
 
    vector<int> kruskal() {
        std::sort(edges.begin(), edges.end());
        DSU dsu(n);
        int totalWeight = 0;
 
        vector<int> ret;
        for (const auto& edge : edges) {
            if (!dsu.connected(edge.u, edge.v)) {
                dsu.unite(edge.u, edge.v);
                totalWeight += edge.weight;
                ret.push_back(edge.idx);
                // std::cout << "Edge added: (" << edge.u << ", " << edge.v << ") -> " << edge.weight << "\n";
            }
        }
        sort(BegEnd(ret));
        return ret;
    }
};