constexpr int MOD = 1e9 + 7;
constexpr int MAX = 3 * 1e6 + 5;

long long fact[MAX], invFact[MAX];

inline long long modAdd(long long a, long long b) {
    return (a + b + 2 * MOD) % MOD;
}

inline long long modSub(long long a, long long b) {
    return (a - b + MOD) % MOD;
}

inline long long modMul(const long long &a,const long long &b){
    return (a % MOD + MOD) * (b % MOD + MOD) % MOD;
}

long long power(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while (b) {
        if (b & 1) res = modMul(res, a);
        a = modMul(a, a);
        b >>= 1;
    }
    return res;
}

inline long long modInverse(long long a) {
    return power(a, MOD - 2);
}

inline long long modDivide(long long a, long long b) {
    return modMul(a, modInverse(b));
}


inline long long nCr(int n, int r) {
    if (r > n || r < 0) return 0;
    return modMul(fact[n], modMul(invFact[r], invFact[n - r]));
}

inline long long nPr(int n, int r) {
    if (r > n || r < 0) return 0;
    return modMul(fact[n], invFact[n - r]);
}

inline long long catalanNumber(int n){
    return nCr(2 * n, n) / (n + 1);
}

int preprocess = []() {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i < MAX; i++) {
        fact[i] = modMul(fact[i - 1], i);
    }
    invFact[MAX - 1] = modInverse(fact[MAX - 1]);
    for (int i = MAX - 2; i >= 1; i--) {
        invFact[i] = modMul(invFact[i + 1], i + 1);
    }
    return 0;
}();
