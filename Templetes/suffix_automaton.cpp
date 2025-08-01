struct suffix_automaton {
    struct state : map<int, int> {
        int fail = -1, len{}, cnt = 1;
        bool ed = false;
    };
    int lst, n{};
    vector<state> tr;
    explicit suffix_automaton(const string& s = ""s) : tr(1), lst(0) {
        tr.reserve(s.size() * 2);
        for(auto i : s) add(i);
    }
    void add(int c) {
        int x = (int)(tr.size());
        tr.emplace_back(), n++;
        tr[x].len = tr[lst].len + 1;
        int p = lst, q;
        while(~p && (q = tr[p].emplace(c, x).first->second) == x) p = tr[p].fail;
        if(p == -1) tr[x].fail = 0;
        else {
            if(tr[p].len + 1 == tr[q].len) tr[x].fail = q;
            else {
                int y = (int)(tr.size()); tr.emplace_back(tr[q]);
                tr[y].cnt = 0, tr[y].len = tr[p].len + 1;
                while(~p && tr[p][c] == q) tr[p][c] = y, p = tr[p].fail;
                tr[x].fail = tr[q].fail = y;
            }
        }
        lst = x;
    }
    void init() { // to build cnt, end
        for(int p = lst; ~p; tr[p].ed = true, p = tr[p].fail);
        vector b(n + 1, vector(0, 0));
        for(int i = 0; i < tr.size(); ++i) b[tr[i].len].push_back(i);
        for(int l = n; l >= 1; --l)
            for(int u : b[l])
                tr[tr[u].fail].cnt += tr[u].cnt;
    }
    
    long long distinct_substrings() {
        long long res = 0;
        for(int i = 1; i < tr.size(); ++i)
            res += tr[i].len - tr[tr[i].fail].len;
        return res;
    }
};

string longest_common_substring(const string& s, const string& t) {
    suffix_automaton sa(s);
    int max_len = 0, pos = 0;
    int current_len = 0, current_state = 0;
    for (int i = 0; i < t.size(); ++i) {
        while (current_state != 0 && sa.tr[current_state].find(t[i]) == sa.tr[current_state].end()) {
            current_state = sa.tr[current_state].fail;
            current_len = sa.tr[current_state].len;
        }
        if (sa.tr[current_state].find(t[i]) != sa.tr[current_state].end()) {
            current_state = sa.tr[current_state][t[i]];
            current_len++;
            if (current_len > max_len) {
                max_len = current_len;
                pos = i - max_len + 1;
            }
        }
    }
    return t.substr(pos, max_len);
}

vector<int> find_occurrences(const string& s, const string& p) {
    suffix_automaton sa(s);
    int state = 0;
    for (char c : p) {
        if (sa.tr[state].find(c) == sa.tr[state].end())
            return {};
        state = sa.tr[state][c];
    }
    vector<int> occurrences;
    queue<int> q;
    q.push(state);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (sa.tr[u].ed) occurrences.push_back(sa.tr[u].len - p.size());
        for (auto [c, v] : sa.tr[u]) q.push(v);
    }
    return occurrences;
}

string lex_smallest_substring(const string& s, int k) {
    suffix_automaton sa(s);
    string res;
    int state = 0;
    for (int i = 0; i < k; ++i) {
        for (auto [c, v] : sa.tr[state]) {
            res += c;
            state = v;
            break;
        }
    }
    return res;
}

string longest_repeated_substring(const string& s) {
    suffix_automaton sa(s);
    sa.init();
    int max_len = 0, state = 0;
    for (int i = 1; i < sa.tr.size(); ++i) {
        if (sa.tr[i].cnt > 1 && sa.tr[i].len > max_len) {
            max_len = sa.tr[i].len;
            state = i;
        }
    }
    string res;
    while (state != 0) {
        for (auto [c, v] : sa.tr[state]) {
            res += c;
            state = sa.tr[state].fail;
            break;
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

string longest_palindromic_substring(const string& s) {
    string t = s + '#' + string(s.rbegin(), s.rend());
    suffix_automaton sa(t);
    return longest_common_substring(s, string(s.rbegin(), s.rend()));
}
