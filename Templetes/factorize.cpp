map<int, int> factors;
void factorize(long long n)
{
    factors.clear();

    for (int i = 2; i * i <= n; ++i) {
        int power = 0;
        while (n % i == 0) {
            ++power;
            n /= i;
        }
        if (power > 0) factors[i] = power;
    }
    if (n != 1) factors[n] = 1;
}
