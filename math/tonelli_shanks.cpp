typedef long long ll;

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

/*
 * 模意义下sqrt(n)
 */
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
