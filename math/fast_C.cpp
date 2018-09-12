/*
 * C(z, y) % P p is not prime
 */
struct fast_combination {
    typedef pair<int,int> pii;
    ll aa[50], mm[50];
    ll pres[1001000];
    ll pp[50], cc[50], ppp[50], tot;

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
            x = (x + y * w * a[i]) % M;
        }
        return (x + M) % M;
    }

    void init(int p, int pp) {
        pres[0] = 1;
        for (int i = 1; i <= pp; i++) {
            if (i % p == 0) {
                pres[i] = pres[i - 1];
            } else {
                pres[i] = pres[i - 1] * i % pp;
            }
        }
    }

    pii dfs(int n, int p, int c, int pp) {
        int b = n / p;
        if (b == 0) {
            return pii(pres[n], 0);
        } else {
            pii pr = dfs(b, p, c, pp);
            return pii((pr.first * pres[n % pp] % pp) * pow_mod(pres[pp], n / pp, pp) % pp, pr.second + b);
        }
    }

    void gao(int m, int n, int c) {
        tot = 0;
        for (int i = 2; i * i <= c; i++) {
            if (c % i == 0) {
                pp[tot] = i;
                cc[tot] = 0;
                ppp[tot] = 1;
                while (c % i == 0) {
                    cc[tot]++;
                    ppp[tot] *= pp[tot];
                    c /= i;
                }
                tot++;
            }
        }
        if (c != 1) {
            pp[tot] = c;
            cc[tot] = 1;
            ppp[tot] = c;
            tot++;
            //c = 1;
        }
        for (int i = 0; i < tot; i++) {
            init(pp[i], ppp[i]);
            pii pn = dfs(n, pp[i], cc[i], ppp[i]);
            pii pa = dfs(m, pp[i], cc[i], ppp[i]);
            pii pb = dfs(n - m, pp[i], cc[i], ppp[i]);
            if (pn.second - pa.second - pb.second >= cc[i]) {
                aa[i] = 0;
                mm[i] = ppp[i];
            } else {
                aa[i] = pn.first * (inv(pa.first, ppp[i]) * inv(pb.first, ppp[i]) % ppp[i]) % ppp[i];
                for (int j = 0; j < pn.second - pa.second - pb.second; j++)
                    aa[i] = (ll) aa[i] * pp[i] % ppp[i];
                mm[i] = ppp[i];
            }
        }
        printf("%lld\n", crt(tot, aa, mm));
    }
} fastCombination;
