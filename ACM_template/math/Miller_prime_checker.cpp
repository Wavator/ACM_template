namespace check_prime {

    void init() {
        srand(time(0));
    }

    typedef long long ll;

    typedef long double ldb;

    inline ll multiply(ll x, ll y, const ll &mod) {
        return ((x * y - (ll)(((ldb)x * y + 0.5) / mod) * mod) % mod + mod) % mod;
    }

    inline ll powMod(ll x, ll y, const ll &mod) {
        ll r = 1;
        for (; y; y >>= 1, x = multiply(x, x, mod)) {
            if (y & 1) {
                r = multiply(r, x, mod);
            }
        }
        return r;
    }
    inline long long rand_ll() {
        return (ll) rand() << 30 | rand();
    }

    inline bool check(ll n) {
        if (n == 2) {
            return true;
        }
        if (n < 2 || !(n & 1)) {
            return false;
        }
        ll a, x, y, u = n - 1;
        int t = 0;
        for (; !(u & 1); u >>= 1, ++t);
        for (int i = 0; i < 10; ++i) {
            a = rand_ll() % (n - 1) + 1, x = powMod(a, u, n);
            for (int j = 0; j < t; ++j, x = y) {
                if ((y = multiply(x, x, n)) == 1 && x != 1 && x != n - 1) {
                    return false;
                }
            }
            if (x != 1) {
                return false;
            }
        }
        return true;
    }

    inline bool check_prime_normal(ll x) {
        for(ll i = 2;i * i <= x; ++i)
            if(x % i == 0)
                return false;
        return true;
    }

}
