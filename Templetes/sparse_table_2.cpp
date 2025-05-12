class SparseTable{
    public: 
    int n;
    vector<vector<int>> sparseTable;
    
    SparseTable(int __N){
        n = __N;
        sparseTable = vector<vector<int>> (mx_log(n).F, vector<int> (n));
    }
    pair<int, int> mx_log(int n){
        int ans = 1, len = 1;
        while(n >= len){
            ans++;
            len *= 2;
        }
        return {ans-1, len /2};
    }
    void set(vector<int> &num){
        for(int i=0; i<n; i++){
            sparseTable[0][i] = num[i];
        }

        for(int i = 1, now = 2; i < sparseTable.size(); i++, now *= 2){
            for(int j=0; j < n-now+1; j++){
                int a = j, b = j + now / 2;
                sparseTable[i][j] = max(sparseTable[i-1][j], sparseTable[i-1][j + now/2]);
            }
        }
    }

    int query(int l, int r){
        auto log = mx_log(r-l+1);
        auto a = sparseTable[log.F-1][l], b = sparseTable[log.F-1][r - log.S+1];
     
        return max(a, b);
    }
};