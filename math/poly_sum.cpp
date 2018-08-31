/*
 * 杜教插值，一看就很牛逼
 */
namespace poly_sum {
    const int D = 101000;
    typedef long long ll;
    constexpr ll mod = (ll) 1e9 + 7;

    ll pow_mod(ll a, ll b) {
        ll r = 1;
        for (; b; b >>= 1, a = a * a % mod) {
            if (b & 1) {
                r = r * a % mod;
            }
        }
        return r;
    }

    ll fact[D], finv[D], p1[D], p2[D], h[D][2], C[D];

    ll calcn(int d, ll *a, ll n) {
        if (n <= d) return a[n];
        p1[0] = p2[0] = 1;
        for (int i = 0; i <= d; ++i) {
            ll t = (n - i + mod) % mod;
            p1[i + 1] = p1[i] * t % mod;
        }
        for (int i = 0; i <= d; ++i) {
            ll t = (n - d + i + mod) % mod;
            p2[i + 1] = p2[i] * t % mod;
        }
        ll ans = 0;
        for (int i = 0; i <= d; ++i) {
            ll t = finv[i] * finv[d - i] % mod * p1[i] % mod * p2[d - i] % mod * a[i] % mod;
            if ((d - i) & 1) {
                ans = (ans - t + mod) % mod;
            } else ans = (ans + t) % mod;
        }
        return ans;
    }

    void init(int M) {
        fact[0] = fact[1] = finv[0] = finv[1] = 1;
        for (int i = 2; i < M + 5; ++i) {
            fact[i] = fact[i - 1] * i % mod;
        }
        finv[M + 4] = pow_mod(fact[M + 4], mod - 2);
        for (int i = M + 3; i; --i) finv[i] = finv[i + 1] * (i + 1) % mod;
    }

    ll polysum(ll n, ll *a, ll m) { // a[0].. a[m] \sum_{i=0}^{n-1} a[i]
        a[m + 1] = calcn(m, a, m + 1);
        for (int i = 1; i < m + 2; ++i) {
            a[i] = (a[i - 1] + a[i]) % mod;
        }
        return calcn(m + 1, a, n - 1);
    }

    ll qpolysum(ll R, ll n, ll *a, ll m) { // a[0].. a[m] \sum_{i=0}^{n-1} a[i]*R^i
        if (R == 1) return polysum(n, a, m);
        a[m + 1] = calcn(m, a, m + 1);
        ll r = pow_mod(R, mod - 2), p3 = 0, p4 = 0, c, ans;
        h[0][0] = 0;
        h[0][1] = 1;
        for (int i = 1; i < m + 2; ++i) {
            h[i][0] = (h[i - 1][0] + a[i - 1]) * r % mod;
            h[i][1] = h[i - 1][1] * r % mod;
        }
        for (int i = 0; i < m + 2; ++i) {
            ll t = finv[i] * finv[m + 1 - i] % mod;
            if (i & 1) {
                p3 = ((p3 - h[i][0] * t) % mod + mod) % mod, p4 = ((p4 - h[i][1] * t) % mod + mod) % mod;
            } else {
                p3 = (p3 + h[i][0] * t) % mod, p4 = (p4 + h[i][1] * t) % mod;
            }
        }
        c = pow_mod(p4, mod - 2) * (mod - p3) % mod;
        for (int i = 0; i < m + 2; ++i) {
            h[i][0] = (h[i][0] + h[i][1] * c) % mod;
        }
        for (int i = 0; i < m + 2; ++i) {
            C[i] = h[i][0];
        }
        ans = (calcn(m, C, n) * pow_mod(R, n) - c) % mod;
        if (ans < 0) ans += mod;
        return ans;
    }
}
