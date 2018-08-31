struct Factor {
    typedef long long ll;
    const ll mod = (ll) 1e9 + 7;
    int p, sz;
    vector<bool> is_prime;
    vector<int> prime, phi, miu, pi;

    number_theory(int n = (int) 5e6 + 5) : sz(n) {
        sieve();
    }

    int sieve() {
        static bool f = false;
        if (f) {
            return p;
        }
        f = true;
        is_prime.assign(sz + 1, false);
        pi.resize(sz + 1, 0);
        for (int i = 1; i <= sz; ++i) {
            pi[i] = i;
        }
        for (int i = 2; i <= sz; i++) {
            if (pi[i] == i) {
                prime.push_back(i);
                ++p;
            }
            for (int j = 0, t1; j < p && (t1 = prime[j] * i) <= sz; j++) {
                pi[t1] = prime[j];
                if (i % prime[j] == 0) {
                    break;
                }
            }
        }
        for (int i = 2; i <= sz; ++i) {
            if (pi[i] == i) {
                is_prime[i] = true;
            }
        }
        return p;
    }

    void gen_phi() {
        static bool f = false;
        if (f) {
            return;
        }
        f = true;
        int p = 0;
        phi.resize(sz + 1, 0);
        phi[1] = 1;
        for (int i = 2; i <= sz; i++) {
            if (is_prime[i]) {
                p++;
                phi[i] = i - 1;
            }
            for (int j = 0; j < p; j++) {
                if (prime[j] * i > sz) {
                    break;
                }
                phi[i * prime[j]] = phi[i] * (i % prime[j] ? prime[j] - 1 : prime[j]);
                if (i % prime[j] == 0) {
                    break;
                }
            }
        }
    }

    void gen_miu() {
        static bool f = false;
        if (f) {
            return;
        }
        f = true;
        int p = 0;
        miu.assign(sz + 1, 0);
        miu[1] = 1;
        for (int i = 2; i <= sz; i++) {
            if (is_prime[i]) {
                p++;
                miu[i] = -1;
            }
            for (int j = 0; j < p; j++) {
                if (prime[j] * i > sz) {
                    break;
                }
                miu[i * prime[j]] = i % prime[j] ? -miu[i] : 0;
                if (i % prime[j] == 0) {
                    break;
                }
            }
        }
    }

    void gen_phi_miu() {
        static bool f = false;
        if (f) {
            return;
        }
        f = true;
        phi.assign(sz + 1, 0);
        miu.assign(sz + 1, 0);
        int p = 0;
        phi[1] = 1;
        miu[1] = 1;
        for (int i = 2; i <= sz; i++) {
            if (is_prime[i]) {
                p++;
                phi[i] = i - 1;
                miu[i] = -1;
            }
            for (int j = 0; j < p; j++) {
                if (prime[j] * i > sz) {
                    break;
                }
                phi[i * prime[j]] = phi[i] * (i % prime[j] ? prime[j] - 1 : prime[j]);
                miu[i * prime[j]] = i % prime[j] ? -miu[i] : 0;
                if (i % prime[j] == 0) {
                    break;
                }
            }
        }
    }

    vector<ll> segment_seive(ll a, ll b) {//[a, b) primes
        vector<ll> prime;
        unsigned sz = (unsigned) sqrt(b);
        while ((ll) sz * sz <= b) {
            ++sz;
        }
        vector<bool> is_prime_small(sz + 1, true);
        vector<bool> is_prime(b - a, true);
        for (ll i = 2; (ll) i * i <= b; i++) {
            if (is_prime_small[i]) {
                for (ll j = 2 * i; (ll) j * j <= b; j += i) {
                    is_prime_small[j] = false;
                }
                for (ll j = max(2LL, (a + i - 1) / i) * i; j < b; j += i) {
                    is_prime[j - a] = false;
                }
            }
        }
        for (ll i = 0; i < b - a; i++) {
            if (is_prime[i] && a + i != 1) {
                prime.push_back(a + i);
            }
        }
        return prime;
    }

    vector<int> prime_factor(int x) const {
        vector<int> res;
        for (int i = 0; prime[i] * prime[i] <= x; ++i) {
            if (x % prime[i] == 0) {
                res.push_back(prime[i]);
                while (x % prime[i] == 0) {
                    x /= prime[i];
                }
            }
        }
        if (x != 1) {
            res.push_back(x);
        }
        return res;
    }

    vector<ll> all_factor(ll x) const {
        vector<ll> res;
        for (ll i = 1; i * i <= x; ++i) {
            if (x % i == 0) {
                res.push_back(i);
                if (i * i != x) {
                    res.push_back(x / i);
                }
            }
        }
        return res;
    }

    vector<pair<int, int> > prime_factorize(int x) const {
        vector<pair<int, int> > res;
        for (int i = 0; prime[i] * prime[i] <= x; ++i) {
            if (x % prime[i] == 0) {
                int cnt = 0;
                while (x % prime[i] == 0) {
                    ++cnt;
                    x /= prime[i];
                }
                res.emplace_back(prime[i], cnt);
            }
        }
        if (x != 1) {
            res.emplace_back(x, 1);
        }
        return res;
    }

    inline bool check_prime(ll x) const {
        if (x <= is_prime.size() && x >= 0) {
            return is_prime[x];
        }
        for (ll i = 2; i * i <= x; ++i) {
            if (x % i == 0) {
                return false;
            }
        }
        return x >= 2;
    }

    inline ll mull(ll a, ll b, ll p) const {
        if (p <= 1000000000) {
            return a * b % p;
        } else if (p <= 1000000000000ll) {
            return (((a * (b >> 20) % p) << 20) + (a * (b & ((1 << 20) - 1)))) % p;
        } else {
            ll d = (ll) floor(a * (long double) b / p + 0.5);
            ll ret = (a * b - d * p) % p;
            if (ret < 0) ret += p;
            return ret;
        }
    }

    inline ll pow_mod(ll a, ll b) {
        ll res = 1;
        for (a %= mod; b; b >>= 1, a = a * a % mod) {
            if (b & 1) {
                res = res * a % mod;
            }
        }
        return res;
    }

    ll powl(ll a, ll b, ll p) {
        ll ans = 1;
        for (; b; b >>= 1) {
            if (b & 1) ans = mull(ans, a, p);
            a = mull(a, a, p);
        }
        return ans;
    }

    bool witness(ll a, ll n) {
        int t = 0;
        ll u = n - 1;
        for (; ~u & 1; u >>= 1) {
            t++;
        }
        ll x = powl(a, u, n), _x = 0;
        for (; t; t--) {
            _x = mull(x, x, n);
            if (_x == 1 && x != 1 && x != n - 1) return 1;
            x = _x;
        }
        return _x != 1;
    }


    inline long long randll() {
        return (ll) rand() << 30 | rand();
    }


    bool miller(ll n) {
        if (n < 2) {
            return 0;
        }
        if (n <= sz) {
            return is_prime[n];
        }
        if (~n & 1) {
            return 0;
        }
        for (int j = 0; j <= 7; j++) {
            if (witness(randll() % (n - 1) + 1, n)) {
                return 0;
            }
        }
        return 1;
    }

    ll gcd(ll a, ll b) {
        ll ret = 1;
        while (a != 0) {
            if ((~a & 1) && (~b & 1)) {

                ret <<= 1, a >>= 1, b >>= 1;
            } else if (~a & 1) {
                a >>= 1;
            } else if (~b & 1) {
                b >>= 1;
            } else {
                if (a < b) {
                    swap(a, b);
                }
                a -= b;
            }
        }
        return ret * b;
    }


    ll rho(ll n) {
        static ll a[1001000];
        for (;;) {
            ll X = rand() % n, Y, Z, T = 1, *lY = a, *lX = lY;
            int tmp = 20;
            int C = rand() % 10 + 3;
            X = mull(X, X, n) + C;
            *(lY++) = X;
            lX++;
            Y = mull(X, X, n) + C;
            *(lY++) = Y;
            for (; X != Y;) {
                ll t = X - Y + n;
                Z = mull(T, t, n);
                if (Z == 0) {
                    return gcd(T, n);
                }
                tmp--;
                if (tmp == 0) {
                    tmp = 20;
                    Z = gcd(Z, n);
                    if (Z != 1 && Z != n) {
                        return Z;
                    }
                }
                T = Z;
                Y = *(lY++) = mull(Y, Y, n) + C;
                Y = *(lY++) = mull(Y, Y, n) + C;
                X = *(lX++);
            }
        }
    }

    vector<ll> fac;

    void _factor(ll n) {
        for (ll &ft: fac) {
            if (n % ft == 0) {
                n /= ft;
                fac.push_back(ft);
            }
        }
        if (n <= sz) {
            for (; n != 1; n /= pi[n]) fac.push_back(pi[n]);
            return;
        }
        if (miller(n)) {
            fac.push_back(n);
        } else {
            ll x = rho(n);
            _factor(x);
            _factor(n / x);
        }
    }

    vector<ll> fact_big(ll n) {
        fac.clear();
        _factor(n);
        return fac;
    }

    inline int inv_normal(int a) {
        a %= mod;
        if (a < 0) a += mod;
        int b = mod, u = 0, v = 1;
        for (; a;) {
            int t = b / a;
            b -= t * a;
            swap(a, b);
            u -= t * v;
            swap(u, v);
        }
        if (b != 1)
            return -1;
        if (u < 0) u += mod;
        return u;
    }

    ll euler_phi(ll x) {
        //map<ll,ll> pf;
        ll num = 1;
        ll num2 = x;
        for (ll i = 0; prime[i] * prime[i] <= x; i++) {
            if (x % prime[i] == 0) {
                num2 /= prime[i];
                num *= (prime[i] - 1);
            }
            while (x % prime[i] == 0) {
                x /= prime[i];
                //pf[prime[i]]++;
            }
        }
        if (x > 1) {
            //pf[x]++;
            num2 /= x;
            num *= (x - 1);
        }
        num *= num2;
        return num;
    }

    ll inv_general(ll a, ll mod) {
        ll ph = euler_phi(mod);
        ph--;
        return powl(a, ph, mod);
    }

    vector<ll> sumdiv;

    void SieveSumDiv() {
        sumdiv.resize(sz + 1);
        for (int i = 1; i <= sz; ++i) {
            for (int j = i; j <= sz; j += i) {
                sumdiv[j] += i;
            }
        }
    }

    void ext_gcd(ll a, ll b, ll &d, ll &x, ll &y) {
        if (b) {
            ext_gcd(b, a % b, d, y, x);
            y -= x * (a / b);
        } else {
            d = a, x = 1, y = 0;
        }
    }

    // x=a[i](mod m[i]), 0 base
    ll crt(int n, ll *a, ll *m) {
        ll M = 1, d, y, x = 0, w;
        for (int i = 0; i < n; ++i) {
            M *= m[i];
        }
        for (int i = 0; i < n; ++i) {
            w = M / m[i];
            ext_gcd(m[i], w, d, d, y);
            x = (x + y * w * a[i]) % mod;
        }
        return (x + mod) % mod;
    }

    ll tonelli_shanks(ll n, ll p = (ll) 1e9 + 9) {//sqrt(n)
        if (p == 2)
            return (n & 1) ? 1 : -1;
        if (powl(n, p >> 1, p) != 1)
            return -1;
        if (p & 2)
            return powl(n, (p + 1) >> 2, p);
        int s = __builtin_ctzll(p ^ 1);
        ll q = p >> s, z = 2;
        for (; powl(z, p >> 1, p) == 1; ++z);
        ll c = powl(z, q, p), r = powl(n, (q + 1) >> 1, p), t = powl(n, q, p), tmp;
        for (int m = s, i; t != 1;) {
            for (i = 0, tmp = t; tmp != 1; ++i) tmp = tmp * tmp % p;
            for (; i < --m;) c = c * c % p;
            r = r * c % p;
            c = c * c % p;
            t = t * c % p;
        }
        return r;
    }

    vector<ll> sum_miu;
    map<ll, ll> sum_miu_mp;

    ll cal_sum_miu(ll x) {
        if (x <= sz) {
            return sum_miu[x];
        }
        if (sum_miu_mp.find(x) != sum_miu_mp.end()) {
            return sum_miu_mp[x];
        }
        ll ans = 1;
        for (ll i = 2, j; i <= x; i = j + 1) {
            j = x / (x / i), ans -= (j - i + 1) * cal_sum_miu(x / i);
        }
        return sum_miu_mp[x] = ans;
    }

    ll cal_sum_phi(ll x) {
        ll ans = 0;
        for (ll i = 1, j; i <= x; i = j + 1) {
            j = x / (x / i), ans += (x / i) * (x / i) * (cal_sum_miu(j) - cal_sum_miu(i - 1));
        }
        return ((ans - 1) >> 1) + 1;
    }

    void gen_sum() { // sz = 5000000
        gen_miu();
        sum_miu.resize(sz + 1);
        sum_miu[0] = miu[0];
        for (int i = 1; i <= sz; ++i) {
            sum_miu[i] = sum_miu[i - 1] + miu[i];
        }
    }



} nt;
