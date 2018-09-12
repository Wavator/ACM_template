struct ext_bsgs {
    int bsgs(ll s, ll a, ll b, ll c) {
        hasher.init();
        int m = (int) ceil(sqrt(c + 0.5));
        for (int i = 0; i < m; i++) {
            if (s == b) return i;
            hasher.insert(s, i);
            s = s * a % c;
        }
        ll am = 1;
        for (int i = 0; i < m; i++)
            am = am * a % c;
        am = inv(am, c);
        b = b * am % c;
        for (int i = m; i < c; i += m) {
            int j = hasher.query(b);
            if (j != -1) return i + j;
            b = b * am % c;
        }
        return -1;
    }

    int exbsgs(ll a, ll b, ll c) {
        ll s = 1;
        for (int i = 0; i < 32; i++) {
            if (s == b) return i;
            s = s * a % c;
        }
        ll cd;
        s = 1;
        int rt = 0;
        while ((cd = __gcd(a, c)) != 1) {
            rt++;
            s *= a / cd;
            if (b % cd) return -1;
            b /= cd;
            c /= cd;
            s %= c;
        }
        int p = bsgs(s, a, b, c);
        if (p == -1) return -1;
        return rt + p;
    }

    void solve(int a, int b, int c) {
        int res = exbsgs(a, b, c);
        if (res == -1) {
            printf("Math Error\n");
        }
        else {
            printf("%lld\n", res);
        }
    }
} bsgs;
