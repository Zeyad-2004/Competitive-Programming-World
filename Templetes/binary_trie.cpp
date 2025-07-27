template<int Log = 62>
class trie_xor {
    struct node {
        int cnt{};
        node* mp[2]{};
    } *root = new node;

    void clear(node* x) {
        if (!x) return;
        for (auto& i : x->mp) clear(i);
        delete x;
    }

public:
//    ~trie_xor() { clear(root); }

    // Insert number `num` with count `c` (default = 1)
    void add(int num, int c = 1) {
        node* x = root;
        for (int i = Log; i >= 0; --i) {
            x->cnt += c;
            bool b = (num >> i) & 1LL;
            if (!x->mp[b]) x->mp[b] = new node;
            x = x->mp[b];
        }
        x->cnt += c;
    }
    // Erase number `n` from the trie
    void erase(int n) {
        node *cur = root;
        for (int i = Log; i >= 0; i--) {
            bool idx = (n >> i) & 1LL;
            node *next = cur->mp[idx];
            next->cnt--;
            if (next->cnt == 0) {
                delete next;
                cur->mp[idx] = nullptr;
                return;
            }
            cur = next;
        }
    }
    // Return whether number exists in the trie
    bool contains(int num) {
        node* x = root;
        for (int i = Log; i >= 0; --i) {
            bool b = (num >> i) & 1LL;
            if (!x->mp[b] || x->mp[b]->cnt == 0) return false;
            x = x->mp[b];
        }
        return x->cnt > 0;
    }

    // Return the number in the trie that gives min xor with `num`
    int min_xor(int num) {
        if (root->cnt == 0) return -1;
        node* x = root;
        int ans = 0;
        for (int i = Log; i >= 0; --i) {
            bool b = (num >> i) & 1LL;
            if (x->mp[b]) {
                x = x->mp[b];
            } else {
                ans |= (1LL << i);
                x = x->mp[(!b)];
            }
        }
        return ans;
    }

    // Return the number in the trie that gives max xor with `num`
    int max_xor(int num) {
        if (root->cnt == 0) return -1;
        node* x = root;
        int ans = 0;
        for (int i = Log; i >= 0; --i) {
            bool b = ((num >> i) & 1LL) ^ 1LL;
            if (x->mp[b]) {
                ans |= (1LL << i);
                x = x->mp[b];
            } else {
                x = x->mp[(!b)];
            }
        }
        return ans;
    }

    void clear() {
        clear(root);
        root = new node;
    }
};