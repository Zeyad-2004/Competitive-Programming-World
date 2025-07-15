vector<vector<int>> leetCode_input_twoDimension(string &s){
    vector<vector<int>> ret;
    vector<int> tmp;
    long long n=0;

    bool have = false, neg = false;
    for (int i = 1; i < s.size(); ++i) {
        if(s[i] == '-'){
            neg = true;
        }
        if(s[i] >= '0' && s[i] <= '9'){
            n *= 10;
            n += s[i] - '0';

            have = true;
        }
        else{
            if(have) {
                tmp.push_back(n*((neg)? -1: 1));
                neg = false;
            }
            n = 0;

            if(s[i] == ']' && !tmp.empty()){
                ret.push_back(tmp);
                tmp.clear();
            }
            have = false;
        }
    }

    return ret;
}
