ll ext_gcd(ll a, ll b, ll &x, ll &y)
{
    ll d = a;
    if(b) {
        d = ext_gcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
    else {
        x = 1;
        y = 0;
    }
    return d;
}
