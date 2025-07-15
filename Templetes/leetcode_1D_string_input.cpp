vector<string> leetCode_input_oneDimension(string &s){
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
                break;
            }
            have = false;
        }
    }

    return tmp;
}