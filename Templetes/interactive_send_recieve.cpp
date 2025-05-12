int answer(vector<int> have){

    cout << "? ";
    for(auto &x: have) cout << x << ' ';
    cout << endl;
    
    cout.flush();

    int ans; cin >> ans;
    return ans;
}