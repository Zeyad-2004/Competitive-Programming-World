int mul(int a, int b) {
    return (1LL * (a %mod) * (b %mod)) % mod;
}

int divide(int a, int b) {
    return mul(a, mul(b, mod-2)) % mod;
}

int add(int a, int b) {
    a = (a + mod) % mod;
    b = (b + mod) % mod;
    return (a + b) % mod;
}

int fp(int b, int p) {
    if (b == 1 or p == 0)
        return 1;

    int ret = fp(b, p >> 1);
    ret = mul(ret, ret);

    if (p & 1)
        ret = mul(ret, b);

    return ret%mod;
}

ll modInv(ll n) {
    return fp(n, mod - 2);
}

ll fact[N], inv[N];

void pre() {
    fact[0] = inv[0] = 1;
    for (ll i = 1; i < N; i++)
        fact[i] = (fact[i - 1] * i), inv[i] = fp(fact[i], mod - 2);
}

ll nCr(ll n, ll r) {
    if (r > n)return 0;
    if (n == r)return 1LL;
    return ((fact[n] * inv[r]) * inv[n - r]);
}

ll nPr(ll n, ll r) {
    return ((fact[n] * inv[n - r])) % mod;
}