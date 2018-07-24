ll ext_gcd(ll a, ll b, ll &d, ll &x, ll &y) {
    if (b) {
        ext_gcd(b, a % b, d, y, x);
        y -= x * (a / b);
    } else {
        d = a, x = 1, y = 0;
    }
}

