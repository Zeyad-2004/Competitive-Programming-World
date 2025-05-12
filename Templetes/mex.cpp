int MEX(set<int> &MEX_set){
    int MEX_result = 0;
    vector<int>loop(MEX_set.begin() , MEX_set.end());
    for(int i = 0 ; i <(int)loop.size() ; i ++){
        MEX_result = loop[i] + 1;
        if(i != loop[i])return i ;
    }
    return MEX_result;
}