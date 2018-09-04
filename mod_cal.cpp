namespace Mod {

    constexpr int mod = (int)1e9 + 7;

    inline int add(int a, int b) {
        a += b;
        return a < mod? a: a - mod;
    }

    inline int sub(int a, int b) {
        a -= b;
        return a < 0? a + mod: a;
    }

    inline int mul(ll a, int b) {
        a *= b;
        return (int)(a < mod? a: a - a / mod * mod);
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

    ll powl(ll a, ll b, ll p) {
        ll ans = 1;
        for (; b; b >>= 1) {
            if (b & 1) ans = mull(ans, a, p);
            a = mull(a, a, p);
        }
        return ans;
    }

    ll tonelli_shanks(ll n, ll p = (ll) 1e9 + 9) {//sqrt(n)
        if (p == 2) {
            return (n & 1) ? 1 : -1;
        }
        if (powl(n, p >> 1, p) != 1) {
            return -1;
        }
        if (p & 2) {
            return powl(n, (p + 1) >> 2, p);
        }
        int s = __builtin_ctzll(p ^ 1);
        ll q = p >> s, z = 2;
        for (; powl(z, p >> 1, p) == 1; ++z);
        ll c = powl(z, q, p), r = powl(n, (q + 1) >> 1, p), t = powl(n, q, p), tmp;
        for (int m = s, i; t != 1;) {
            for (i = 0, tmp = t; tmp != 1; ++i) {
                tmp = tmp * tmp % p;
            }
            for (; i < --m;) {
                c = c * c % p;
            }
            r = r * c % p;
            c = c * c % p;
            t = t * c % p;
        }
        return r;
    }

    inline int pow_mod(int a, ll b) {
        int res = 1;
        for(; b; b>>=1,a=mul(a,a))if(b&1)res=mul(res,a);
        return res;
    }

    inline int pow_mod(int a, ll b, int mod) {
        int res = 1;
        for (; b; b >>= 1, a = (ll)a * a % mod) {
            if (b & 1) {
                res = (ll) res * a % mod;
            }
        }
        return res;
    }

    inline int inv(int a) {
        a %= mod;
        if (a < 0) a += mod;
        int b = mod, u = 0, v = 1;
        for(;a ;) {
            int t = b / a;
            b -= t * a;swap(a, b);
            u -= t * v;swap(u, v);
        }
        if (b != 1)
            return -1;
        if (u < 0) u += mod;
        return u;
    }

    /*
     *
     * a ^ x = b(mod n), n is prime, return -1 if no solution
     */
    int log_mod(int a, int b, int n) {
        int m = (int)sqrt(n + 0.5);
        int v = inv(pow_mod(a, m, n));
        map<int, int> mp;
        mp.emplace(1, 0);
        for (int i = 1; i < m; ++i) {
            int e = 1ll * e * a % n;
            if (!mp.count(e)) {
                mp.emplace(e, i);
            }
        }
        for (int i = 0; i < m; ++i) {
            if (mp.count(b)) {
                return i * m + mp[b];
            }
            b = 1ll * b * v % n;
        }
        return -1;
    }

    

}
using Mod::add;
using Mod::sub;
using Mod::inv;
using Mod::mul;
using Mod::pow_mod;
