
inline long long modMul(const long long &a,const long long &b, const long long moood){
    return __int128(a) * (b % moood + moood) % moood;
}

long long power(long long a, long long b, long long moood) {
    long long res = 1;
    a %= moood;
    while (b) {
        if (b & 1) res = modMul(res, a, moood);
        a = modMul(a, a, moood);
        b >>= 1;
    }
    return res;
}

// Miller-Rabin test for a single base
bool millerTest(ll d, ll n, ll a) {
    ll x = power(a, d, n);
    if (x == 1 || x == n - 1)
        return true;

    while (d != n - 1) {
        x = modMul(x, x, n);
        d *= 2;

        if (x == 1) return false;
        if (x == n - 1) return true;
    }

    return false;
}

// Miller-Rabin Primality Test (deterministic for < 2^64)
bool isPrime(ll n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0) return false;

    ll d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    // Deterministic bases for 64-bit integers
    vector<ll> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    for (ll a : bases) {
        if (a >= n) break;
        if (!millerTest(d, n, a))
            return false;
    }

    return true;
}

// Pollard's Rho algorithm
long long pollards_rho(long long n) {
    if (n % 2 == 0) return 2;
    long long x = 2, y = 2, d = 1, c = rand() % (n - 1) + 1;
    while (d == 1) {
        x = (modMul(x, x, n) + c) % n;
        y = (modMul(y, y, n) + c) % n;
        y = (modMul(y, y, n) + c) % n;
        d = gcd((x > y) ? x - y : y - x, n);
        if (d == n) return pollards_rho(n);
    }
    return d;
}

// Recursive factorization
void factor(long long n, map<long long, int>& factors) {
    if (n == 1) return;
    if (isPrime(n)) {
        ++factors[n];
        return;
    }
    long long d = pollards_rho(n);
    factor(d, factors);
    factor(n / d, factors);
}

map<long long, int> factorize(long long n){
    map<long long, int> factors;

    if(n == 1) {
        factors[0] = -1;
    }
    else{
        factor(n, factors);
    }

    return factors;
}
