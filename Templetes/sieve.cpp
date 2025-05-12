const int N = 1e8;
vector<ll> primes;
vector<bool> is_prime(N + 1);
 
void sieve() {
    is_prime[0] = is_prime[1] = true;
 
    for (int i = 2; i <= N; ++i) {
        if (!is_prime[i]) {
            primes.push_back(i);
 
            for (int j = i + i; j <= N; j += i)
                is_prime[j] = true;
        }
    }
}