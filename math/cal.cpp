const long long mod = 1e9 + 7;

inline long long add(const long long &a, const long long &b) {
    long long res = a + b;
    if (res > mod)
        res -= mod;
    return res;
}

inline long long sub(const long long &a, const long long &b) {
    return (a - b + mod) % mod;
}

inline long long mul(const long long &a, const long long &b) {
    return (a * b) % mod;
}

inline long long mul_inv(long long a, long long b = mod) {
    long long t1 = a, t2 = b, t3;
    long long v1 = 1, v2 = 0, v3;
    while (t2 != 1) {
        long long x = t1 / t2;
        t3 = t1 - x * t2;
        v3 = v1 - x * v2;
        t1 = t2, t2 = t3;
        v1 = v2, v2 = v3;
    }
    return (v2 + b) % b;
}

inline long long div(long long a, long long b) {
    return a * mul_inv(b) % mod;
}

long long powMod(long long a, long long b) {
    long long res = 1;
    for (a %= mod; b; b >>= 1, a = a * a % mod)
        if (b & 1)
            res = res * a % mod;
    return res;
}
