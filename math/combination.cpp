struct comb_cal {
    typedef long long ll;
    /*
     * 模意义下的快速运算
     */
    const int mod = (int) 1e9 + 7;

    inline int add(int a, int b) const {
        a += b;
        return a < mod ? a : a - mod;
    }

    inline int sub(int a, int b) const {
        a -= b;
        return a < 0 ? a + mod : a;
    }

    inline int mul(ll a, int b) const {
        a *= b;
        return a < mod ? a : a - a / mod * mod;
    }

    inline int pow_mod(int a, ll b) const {
        int res = 1;
        for (; b; b >>= 1, a = mul(a, a))if (b & 1)res = mul(res, a);
        return res;
    }

    inline int inv(int a) const {
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
     * 运用n!/(m!*(n-m)!),On的预处理阶乘和阶乘的逆元之后，O1计算C(n,m)
     * 使用：最开始init一次，通过使用C(n,m)计算
     * 模数有要求
     */
    vector<int> fact, finv;
    void init_comb_1(unsigned n = 1000000) {
        fact[0] = 1;
        for (int i = 1; i <= n; ++i) {
            fact[i] = mul(fact[i - 1], i);
        }
        finv[n] = inv(fact[n]);
        for (int i = n - 1; ~i; --i) {
            finv[i] = mul(finv[i + 1], (i + 1));
#ifdef Wavator
            assert(1ll * fact[i] * finv[i] % mod == 1);
#endif
        }
    }

    inline int C(int n, int m) const {
        if (n < m) return 0;
        return (int) (((ll) fact[n] * finv[m] % mod) * finv[n - m] % mod);
    }

    /*
     * 卢卡斯定理
     */
    inline int lucas(int n, int m) const {
        if (n < m) return 0;
        if (!m || n == m) return 1;
        return mul(lucas(n / mod, m / mod), C(n % mod, m % mod));
    }

    /*
     * n^2预处理，递推出C，对模数没有要求，调用的话重载了()运算符，使用comb(n,m)计算C(n,m)
     */
    vector<vector<int>> c2;
    void init_combsqr(int n = 3000) {
        c2.assign(n+1,vector<int>(n+1,0));
        c2[0][0] = 1;
        for(int i=1;i<=n;++i) {
            c2[i][0]=c2[i][i]=1;
            for(int j=1;j<i;++j) {
                c2[i][j]=c2[i-1][j-1]+c2[i-1][j];
                if (c2[i][j] >= mod) {
                    c2[i][j] -= mod;
                }
            }
        }
    }
    int operator()(int n, int m) const {
        return n < m? 0: c2[n][m];
    }

    /*
     * 快速计算val^k,但是题目里的val必须是定的，比如题目问1e8次2的1e10次内的幂
     * 预处理是sqrt(maxn)的，计算是O1的，非常方便
     */
    vector<int> const_power_head, const_init_power;
    unsigned power_block = 100000;

    void gen_const_power(ll val) {
        const_power_head.resize(power_block + 2);
        const_init_power.resize(power_block + 2);
        const_init_power[0] = 1;
        for (int i = 1; i <= power_block; ++i) {
            const_init_power[i] = mul(val, const_init_power[i - 1]);
        }
        const_power_head[0] = 1;
        for (int i = 1; i <= power_block; ++i) {
            const_power_head[i] = mul(const_power_head[i - 1], const_init_power[power_block]);
        }
    }

    inline int get_const_power(ll x) { // val ^ x
        if (x >= mod - 1) {
            x %= mod - 1;// x %= euler_phi(mod);
        }
        return mul(const_power_head[x / power_block], const_init_power[x % power_block]);
    }
} comb;
