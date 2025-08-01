class TrieString {
    struct Node {
        Node* child[26]{};
        // unordered_map<char, Node*> child; // Uncomment this line to use unordered_map for flexibility

        int wordCount = 0;
        int prefixCount = 0;
        char value = 'a';

        Node() = default;
    };

    Node* root;

public:
    TrieString() : root(new Node()) {}

    void insert(const string& s) {
        Node* cur = root;
        for (char ch : s) {
            int idx = ch - cur->value;
            if (!cur->child[idx]) cur->child[idx] = new Node();
            cur = cur->child[idx];
            cur->prefixCount++;
        }
        cur->wordCount++;
    }

    bool contains(const string& s) const {
        Node* cur = root;
        for (char ch : s) {
            int idx = ch - cur->value;
            if (!cur->child[idx]) return false;
            cur = cur->child[idx];
        }
        return cur->wordCount > 0;
    }

    int countWord(const string& s) const {
        Node* cur = root;
        for (char ch : s) {
            int idx = ch - cur->value;
            if (!cur->child[idx]) return 0;
            cur = cur->child[idx];
        }
        return cur->wordCount;
    }

    int countPrefix(const string& s) const {
        Node* cur = root;
        for (char ch : s) {
            int idx = ch - cur->value;
            if (!cur->child[idx]) return 0;
            cur = cur->child[idx];
        }
        return cur->prefixCount;
    }

    void erase(const string& s) {
        Node* cur = root;

        for (char ch : s) {
            int idx = ch - cur->value;
            if (!cur->child[idx]) return;

            Node *next = cur->child[idx];
            next->prefixCount--;

            if(next->prefixCount == 0){
                delete next;
                cur->child[idx] = nullptr;
                return;
            }

            cur = next;
        }

        if (cur->wordCount == 0) return; // word not present
        cur->wordCount--;
    }

    void clear(Node* node) {
        if (!node) return;
        for (Node* child : node->child) clear(child);
        delete node;
    }

//    ~TrieString() clear(root);

};