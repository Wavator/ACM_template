struct Factor {
    typedef long long ll;
    const ll mod = (ll) 1e9 + 7;
    int p, sz;
    vector<bool> is_prime;
    vector<int> prime, phi, miu, pi;

    Factor(int n = (int) 1e6 + 5) : sz(n) { sieve(); }

    /*
     * 得到<=sz的素数，is_prime 存储是不是素数，素数存储在prime中；
     * pi表示一个数的最小素因子，pi=i也说明i是素数(i >= 2);
     * sieve不需要调暗勇，但需要注意杜教筛n最好是maxn的2/3次
     * */
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

    /*
     * 得到<=sz的phi函数，存储在phi中
     */
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

    /*
    * 得到<=sz的miu函数，存储在miu中
    */
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

    //保证速度，将phi,miu放到一起筛
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

    /*
     * 分段打表，得到[a,b)以内的素数,答案存储在返回的vector<ll>里，复杂度sqrt(b) + (b-a)
     */
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

    /*
     * 得到x的所有素数因子，复杂度是sqrt(x)中的素数个数
     * x应该小于筛的范围的最大素数的平方
     */
    vector<ll> prime_factor(ll x) const {
        vector<ll> res;
        for (int i = 0; (ll) prime[i] * prime[i] <= x; ++i) {
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

    /*
     * 得到x的所有因数，sqrt(x)的复杂度
     */
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

    /*
     * 得到x的所有素因子，以及在x的唯一分解定理意义下该素数的幂次，
     * pair<ll,int>代表因子，幂次
     * 复杂度是sqrt(x)中的素数个数
     */
    vector<pair<ll, int> > prime_factorize(ll x) const {
        vector<pair<ll, int> > res;
        for (int i = 0; (ll) prime[i] * prime[i] <= x; ++i) {
            if (x % prime[i] == 0) {
                int cnt = 0;
                while (x % prime[i] == 0) {
                    ++cnt;
                    x /= prime[i];
                }
                res.emplace_back((ll) prime[i], cnt);
            }
        }
        if (x != 1) {
            res.emplace_back(x, 1);
        }
        return res;
    }

    /*
     * 简单素性测试,根据合数sqrt(x)内一定有一个素因子
     * 复杂度：sqrt(x)以内的素数个数
     */
    inline bool check_prime(ll x) const {
        if (x < 2) {
            return false;
        }
        if (x < is_prime.size()) {
            return is_prime[x];
        }
        for (int i = 0; i < (int) prime.size(); ++i) {
            if ((long long) prime[i] * prime[i] > x) {
                break;
            }
            if (x % prime[i] == 0) {
                return false;
            }
        }
        return true;
    }

    /*
     * ll范围内模意义快速乘法
     */
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

    /*
     * 基本快速幂 log
     */
    inline ll pow_mod(ll a, ll b) {
        ll res = 1;
        for (a %= mod; b; b >>= 1, a = a * a % mod) {
            if (b & 1) {
                res = res * a % mod;
            }
        }
        return res;
    }

    /*
     * 任意模数ll内快速幂 log
     */
    ll powl(ll a, ll b, ll p) {
        ll ans = 1;
        for (; b; b >>= 1) {
            if (b & 1) ans = mull(ans, a, p);
            a = mull(a, a, p);
        }
        return ans;
    }

    /*
     * Miller素性检测使用
     */
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

    /*
     * Miller素性检测使用
     */
    inline long long randll() {
        return (ll) rand() << 30 | rand();
    }

    /*
     * 快速检测素性
     */
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

    /*
     * 光速gcd
     */
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

    /*
     * 快速扒出n的一个素因子
     */
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

    /*
     * 对一个巨大的数做因数分解，存在fac里，理论上ll范围内都很快得到
     */
    vector<ll> fact_big(ll n) {
        fac.clear();
        _factor(n);
        return fac;
    }

    /*
     * 基于ext_gcd的逆元，log，-1代表没有逆元
     */
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

    /*
     * 计算phi(x), 复杂性sqrt(x)的质数个数
     */
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

    /*
     * 广义的逆元，根据欧拉降幂
     */
    ll inv_general(ll a, ll mod) {
        ll ph = euler_phi(mod);
        ph--;
        return powl(a, ph, mod);
    }

    /*
     * 对sz以内的数，计算因子的和，存在sumdiv里
     */
    vector<ll> sumdiv;

    void SieveSumDiv() {
        sumdiv.resize(sz + 1);
        for (int i = 1; i <= sz; ++i) {
            for (int j = i; j <= sz; j += i) {
                sumdiv[j] += i;
            }
        }
    }

    /*
     * 类似线性筛的筛出[1,n]的每个数的因子
     * n不能筛的很大，最多1e5,因为空间无法接受
     */
    vector<vector<int> > factor_range(int n = 0) {
        if (n == 0) {
            n = sz;
        }
        vector<vector<int>> res((unsigned) n + 1, vector<int>());
        for (int i = 1; i <= n; ++i) {
            for (int j = i; j <= sz; j += i) {
                res[j].push_back(i);
            }
        }
        return res;
    }

    /*
     * 类似线性筛筛出[1,n]以内每个数的素因子
     */
    vector<vector<int> > prime_fact_range() {
        vector<vector<int> > res(sz + 1, vector<int>());
        for (const int &p: prime) {
            for (int j = p; j <= sz; j += p) {
                res[j].push_back(p);
            }
        }
        return res;
    }

    /*
     * 计算miu的前缀和，复杂性n^(3/4),能跑2e9,calphi类似，计算前要调用gen_sum函数
     */
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

} hlsnb;
