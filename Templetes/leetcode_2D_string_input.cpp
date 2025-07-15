vector<vector<string>> leetCode_input_twoDimension(string &s){
    vector<vector<string>> ret;
    vector<string> tmp;
    string word;

    bool have = false;
    for (int i = 1; i < s.size(); ++i) {
        if(s[i] >= 'a' && s[i] <= 'z'){
            word += s[i];

            have = true;
        }
        else {
            if(have) {
                tmp.push_back(word);
            }
            word.clear();

            if(s[i] == ']' && !tmp.empty()){
                ret.push_back(tmp);
                tmp.clear();
            }
            have = false;
        }
    }

    return ret;
}