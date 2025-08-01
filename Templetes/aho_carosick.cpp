struct corasick {
    struct node {
        array<int, 26> nxt{}, go{};
        vector<int> idx; // all string's indexes have any suffix
        int p, link;
        char ch;
        int cnt = 0;
        explicit node(int p = -1, char ch = '?') : p(p), ch(ch), link(-1) {
            nxt.fill(-1);
            go.fill(-1);
        }
    };
    vector<node> tr;
    explicit corasick(vector<string> &v) : tr(1) {
        for(int i = 0; i < v.size(); i++) {
            int x = 0;
            for(char c : v[i]) {
                if(tr[x].nxt[c - 'a'] == -1) {
                    tr[x].nxt[c - 'a'] = (int)(tr.size());
                    tr.emplace_back(x, c);
                }
                x = tr[x].nxt[c - 'a'];
            }
            tr[x].idx.push_back(i);
        }
        for(int i = 0; i < tr.size(); i++) {
            mxSuffix(i);
        }
    }
    int plus(int x, char c) {
        if(tr[x].go[c - 'a'] == -1) {
            if(tr[x].nxt[c - 'a'] != -1)
                tr[x].go[c - 'a'] = tr[x].nxt[c - 'a'];
            else
                tr[x].go[c - 'a'] = x == 0? 0: plus(mxSuffix(x), c);
        }
        return tr[x].go[c - 'a'];
    }
    int mxSuffix(int x) {
        if(tr[x].link == -1) {
            if(!x || !tr[x].p)
                tr[x].link = 0;
            else
                tr[x].link = plus(mxSuffix(tr[x].p), tr[x].ch);

            mxSuffix(tr[x].link);
            tr[x].idx.reserve(tr[x].idx.size() + tr[tr[x].link].idx.size());
            for(int y : tr[tr[x].link].idx)
                tr[x].idx.push_back(y);
        }
        return tr[x].link;
    }
    vector<int> match(const string &text, int n) {
        vector<int> pattern_count(n);
        int state = 0;
        for(char c : text) {
            state = plus(state, c);
            tr[state].cnt++;
        }

        vector<int> order(tr.size());
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return depth(a) > depth(b);
        });

        for(int i : order) {
            if(tr[i].link != -1)
                tr[tr[i].link].cnt += tr[i].cnt;
        }

        for(int i = 0; i < tr.size(); i++) {
            for(int pat : tr[i].idx) {
                pattern_count[pat] += tr[i].cnt;
            }
        }
        return pattern_count;
    }

    int depth(int x) {
        int d = 0;
        while(x != 0) {
            x = tr[x].p;
            ++d;
        }
        return d;
    }
};