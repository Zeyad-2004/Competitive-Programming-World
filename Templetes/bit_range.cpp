template<typename T>
class BITRange { // 0-based
    int n;
    vector<T> B1, B2;

    void add(vector<T>& bit, int i, T x) {
        for (++i; i <= n; i += i & -i)
            bit[i] += x;
    }

    T query(vector<T>& bit, int i) {
        T res = 0;
        for (++i; i > 0; i -= i & -i)
            res += bit[i];
        return res;
    }

public:
    explicit BITRange(int size) : n(size + 5), B1(n + 2), B2(n + 2) {}

    void add(int l, int r, T x) {
        add(B1, l, x);
        add(B1, r + 1, -x);
        add(B2, l, x * (l - 1));
        add(B2, r + 1, -x * r);
    }
    void add(int i, T x) { add(B2, i, -x); }

    T query(int i) {
        return query(B1, i) * i - query(B2, i);
    }

    T range(int l, int r) {
        if (l > r) return T();
        return query(r) - query(l - 1);
    }
};