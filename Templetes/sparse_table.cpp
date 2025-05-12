pair<int, int> mx_log(int n){
    int ans = 1, len = 1;
    while(n >= len){
        ans++;
        len *= 2;
    }
    return {ans-1, len /2};
}

vector<vector<int>> sparseTable(mx_log(n).F, vector<int> (n));
for(int i=0; i<n; i++){
    sparseTable[0][i] = num[i];
}    
for(int i = 1, now = 2; i < sparseTable.size(); i++, now *= 2){
    for(int j=0; j < n-now+1; j++){
        int a = j, b = j + now / 2;
        sparseTable[i][j] = min(sparseTable[i-1][j], sparseTable[i-1][j + now/2]);
    }
}