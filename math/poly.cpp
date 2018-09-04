namespace poly {
    const int mod = (int) 1e9 + 7;

    inline int inc(int a, int b) {
        a += b;
        return a < mod ? a : a - mod;
    }

    inline int dec(int a, int b) {
        a -= b;
        return a < 0 ? a + mod : a;
    }

    inline int inv(int a) {
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

    inline ll mull(ll a, ll b, ll p) {
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

    vector<int> fa, fb, fc, fd;

    vector<int> get_inv(vector<int> &a, int n) {
        assert(a[0] != 0);
        if (n == 1) {
            fa.resize(1);
            fa[0] = inv(a[0]);
            return fa;
        }
        fa = get_inv(a, (n + 1) >> 1);
        fb = fft::multiply_mod(fa, fa, mod, 1);
        fb = fft::multiply_mod(fb, a, mod);
        fa.resize(n);
        for (int i = 0; i < n; i++) {
            fa[i] = inc(fa[i], fa[i]);
            fa[i] = dec(fa[i], fb[i]);
        }
        return fa;
    }

    vector<int> get_sqrt(vector<int> &a, int n) {
        if (n == 1) {
            fc.resize(1);
            int x = tonelli_shanks(a[0], mod);
            assert(x != -1);
            fc[0] = x;
            return fc;
        }
        fd = get_sqrt(a, (n + 1) >> 1);
        fc = get_inv(fd, (n + 1) >> 1);
        fd = fft::multiply_mod(fd, fd, mod, 1);
        for (int i = 0; i < (n + 1) / 2; i++) fc[i] = 1LL * fc[i] * ((mod + 1) / 2) % mod;
        for (int i = 0; i < n; i++) fd[i] = inc(fd[i], a[i]);
        fd = fft::multiply_mod(fd, fc, mod);
        fd.resize(n);
        return fd;
    }

    vector<int> diff(vector<int> &a) {
        for (int i = 1; i < (int) a.size(); i++) a[i - 1] = 1LL * a[i] * i % mod;
        if (a.size() >= 1) a.resize((int) a.size() - 1);
        return a;
    }

    vector<int> intg(vector<int> &a) {
        int sz = (int) a.size();
        a.resize(sz + 1);
        static vector<int> Inv(sz + 1);
        Inv[1] = 1;
        for (int i = 2; i <= sz; i++) Inv[i] = dec(mod, 1LL * Inv[mod % i] * (mod / i) % mod);
        for (int i = sz; i >= 1; i--) a[i] = 1LL * a[i - 1] * Inv[i] % mod;
        a[0] = 0;
        return a;
    }
};
