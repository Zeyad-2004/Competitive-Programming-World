const int N = 1e5 + 5, P1 = 31, P2 = 37, M = 1e9 + 7;
int pw1[N], pw2[N], inv1[N], inv2[N];
int mul(int a, int b) {
    a = ((a % M) + M) % M;
    b = ((b % M) + M) % M;
    return (a * 1LL * b) % M;
}
int add(int a, int b) {
    a = ((a % M) + M) % M;
    b = ((b % M) + M) % M;
    return (a + b) % M;
}
int fastPower(int base, int power) {
    if (!power) return 1;
    int ret = fastPower(base, power >> 1);
    ret = mul(ret, ret);
    if (power % 2) ret = mul(ret, base);
    return ret;
}
int pre = []() {
    pw1[0] = inv1[0] = pw2[0] = inv2[0] = 1;
    int mulInv1 = fastPower(P1, M - 2);
    int mulInv2 = fastPower(P2, M - 2);
    for (int i = 1; i < N; i++) {
        pw1[i] = mul(pw1[i - 1], P1);
        pw2[i] = mul(pw2[i - 1], P2);
        inv1[i] = mul(inv1[i - 1], mulInv1);
        inv2[i] = mul(inv2[i - 1], mulInv2);
    }
    return 0;
}();

struct Hash {
    vector<pair<int, int>> prefixHash;
    Hash(string s) {
        prefixHash = vector<pair<int, int>> (s.size(), {0, 0});
        for (int i = 0; i < s.size(); i++) {
            prefixHash[i].F = mul(s[i] - 'a' + 1, pw1[i]);
            prefixHash[i].S = mul(s[i] - 'a' + 1, pw2[i]);
            if (i) prefixHash[i] = {
                        add(prefixHash[i].F, prefixHash[i - 1].F),
                        add(prefixHash[i].S, prefixHash[i - 1].S)
                };
        }
    }
    pair<int, int> getHashVal() {
        return prefixHash.back();
    }
    pair<int, int> getRangeHashVal(int l, int r) { // 0-based
        if(r < l) return {0, 0};

        return {
                mul(add(prefixHash[r].F, -(l ? prefixHash[l - 1].F : 0)), inv1[l]),
                mul(add(prefixHash[r].S, -(l ? prefixHash[l - 1].S : 0)), inv2[l])
        };
    }
    pair<int, int> getHashValWithoutRange(int l, int r){ // 0-based
        if(r < l) return getHashVal();

        auto rem = getRangeHashVal(l, r);
        auto hash = getHashVal();

        return{
            add(hash.F, -mul(rem.F, fastPower(P1, l))),
            add(hash.S, -mul(rem.S, fastPower(P2, l)))
        };
    }
    pair<int, int> addRangeFromMeToAnotherHash(pair<int, int> secondHash, int l, int r){ // 0-based
        if(r < l) return secondHash;

        auto over = getRangeHashVal(l, r);

        return{
            add(secondHash.F, mul(over.F, fastPower(P1, l))),
            add(secondHash.S, mul(over.S, fastPower(P2, l)))
        };
    }
};