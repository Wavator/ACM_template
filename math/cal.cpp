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
const ll mod = 1e9+7;
ll ext_gcd(ll a, ll b, ll &d, ll &x, ll &y) {
    if (b) {
        ext_gcd(b, a % b, d, y, x);
        y -= x * (a / b);
    } else {
        d = a, x = 1, y = 0;
    }
}

ll inv(ll a, ll n = mod) {
    ll d, x, y;
    ext_gcd(a, n, d, x, y);
    return d == 1? (x + n) % n: -1;
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
