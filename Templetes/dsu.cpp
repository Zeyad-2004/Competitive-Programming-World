class DSU {
    private:
        std::vector<int> parent, rank;
    public:
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
    };
    