class _2DPrefixSum {
public:
    vector<vector<int>> values;
    int n, m;

    explicit _2DPrefixSum(vector<vector<int>> &arr){
        n = arr.size(), m = arr.front().size();
        values.resize(n+1, vector<int> (m+1));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                values[i+1][j+1]  = arr[i][j];
                values[i + 1][j + 1] += values[i + 1][j] - values[i][j];
                values[i+1][j+1] += values[i][j+1];
            }
        }
    }

    int squareTotal(int p1_x, int p1_y, int p2_x, int p2_y) {
        if(max(p1_x, p2_x) >= n || max(p1_y, p2_y) >= values.front().size() - 1) return -1;

        return
                values[max(p1_x, p2_x) + 1][max(p1_y, p2_y) + 1]
                -   values[max(p1_x, p2_x) + 1][min(p1_y, p2_y)    ]
                -   values[min(p1_x, p2_x)    ][max(p1_y, p2_y) + 1]
                +   values[min(p1_x, p2_x)    ][min(p1_y, p2_y)    ];
    }

    void printPrefixMatrix() {
        for(auto &row: values){
            for(auto &val: row){
                cout << val << ' ';
            }
            cout << endl;
        }
    }

};