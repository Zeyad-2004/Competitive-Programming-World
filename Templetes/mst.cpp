
class DSU {
    private:
    public:
    std::vector<int> parent, rank;
    DSU(int n) {
            parent.resize(n);
            rank.resize(n, 0);
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }
    
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
    
        void unite(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
    
            if (rootX == rootY) return;
    
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    
        bool connected(int x, int y) {
            return find(x) == find(y);
        }
    
        map<int, set<int>> bounders(){
            map<int, set<int>> ret;
            for(int i=1; i < parent.size(); i++){
                ret[parent[i]].insert(i);
            }
            return ret;
        }
        int groups(){
            int cnt = 0;
            for(int i=1; i < parent.size(); i++){
                if(parent[i] == i) cnt++;
            }
            return cnt;
        }
    };
    
    struct Edge {
        int u, v, weight;
        bool operator<(const Edge& other) const {
            return weight < other.weight;
        }
    };
    
    class MST {
    private:
        int n;
        std::vector<Edge> edges;
    
    public:
        MST(int nodes) : n(nodes) {}
    
        void addEdge(int u, int v, int weight) {
            edges.push_back({u, v, weight});
        }
    
        int kruskal() {
            std::sort(edges.begin(), edges.end());
            DSU dsu(n);
            int totalWeight = 0;
    
            for (const auto& edge : edges) {
                if (!dsu.connected(edge.u, edge.v)) {
                    dsu.unite(edge.u, edge.v);
                    totalWeight += edge.weight;
                    // std::cout << "Edge added: (" << edge.u << ", " << edge.v << ") -> " << edge.weight << "\n";
                }
            }
    
            return totalWeight;
        }
    };
    
