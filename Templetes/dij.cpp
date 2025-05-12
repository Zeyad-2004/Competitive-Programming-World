priority_queue<abcd, vector<abcd>, greater<abcd>> pq;
pq.push({});
while(!pq.empty()){
    int cost = pq.top().F;
//    int node = pq.top().S;  // ONE-DIMENSION
//    int ii = pq.top().S.F, jj = pq.top().S.S;  // TWO-DIMENSION
    
    pq.pop();
    
}