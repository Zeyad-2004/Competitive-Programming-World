template<class T>
struct BIT { // 0-based
    int n;
    vector<T> tree;
    explicit BIT(int size) : n(size + 5), tree(n + 1) { }

    void add(int i, T val) {
        for (i++; i <= n; i += i & -i) tree[i] += val;
    }

    T query(int i) {
        T sum = 0;
        for (i++; i > 0; i -= i & -i) sum += tree[i];
        
        return sum;
    }

    T range(int l, int r) {
        if(l > r) return T();
        return query(r) - query(l - 1);
    }

    int lower_bound(T target) {
        if(target <= 0) return 0;
        int pos = 0;
        T sum = 0;
        for (int i = 1 << __lg(n); i > 0; i >>= 1) {
            if(pos + i <= n && sum + tree[pos + i] < target) {
                sum += tree[pos + i];
                pos += i;
            }
        }
        return pos;
    }
};
