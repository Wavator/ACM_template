    /*
     * 简单的extgcd
     */
    void ext_gcd(ll a, ll b, ll &d, ll &x, ll &y) {
        if (b) {
            ext_gcd(b, a % b, d, y, x);
            y -= x * (a / b);
        } else {
            d = a, x = 1, y = 0;
        }
    }

    /*
     * 中国剩余定理
     * x=a[i](mod m[i]), 0 base
     * 这里要求m必须互质
     * */
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

    /*
     * 同余方程合并， m[i]可以不互质
     * x = c[i] mod m[i], c[i] < m[i]
     * 返回-1表示解不存在
     */
    ll crt_general(int n, ll *c, ll *m) {
        auto mod = [](ll x, ll y)->ll {
            x %= y;
            if (x < 0) x += y;
            return x;
        };
        ll ans = c[0], LCM = m[0];
        for (int i = 1; i < n; ++i) {
            ll g, x, y;
            ext_gcd(LCM, m[i], g, x, y);
            if ((c[i] - ans) % g) {
                return -1;
            }
            ll tmp = mod((c[i] - ans) / g * x, m[i] / g);
            ans = mod(ans + LCM * tmp, LCM / g * m[i]);
            LCM = LCM / g * m[i];
        }
        return mod(ans, LCM);
    }
