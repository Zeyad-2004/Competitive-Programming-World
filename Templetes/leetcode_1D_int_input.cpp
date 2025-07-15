vector<int> leetCode_input(string &s){
    vector<int> tmp;
    long long n=0;
    bool neg = false;
    for (int i = 1; i < s.size(); ++i) {
        if(s[i] == '-'){
            neg = true;
        }
        else if(s[i] >= '0' && s[i] <= '9'){
            n *= 10;
            n += s[i] - '0';
        }
        else{
            tmp.push_back(n*((neg)? -1: 1));
            n = 0;
            neg = false;
        }
    }

    return tmp;
}