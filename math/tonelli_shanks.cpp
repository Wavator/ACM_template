typedef long long ll;
const ll mod = (ll)1e9+9;
ll pow_mod(ll a, ll b, ll mod=::mod) {
    assert(b>=0);ll res=1;
    for(a%=mod;b;b>>=1,a=a*a%mod)if(b&1)res=res*a%mod;
    return res;
}

ll tonelli_shanks(ll n,ll p=::mod) {//sqrt(n)
    if(p == 2)
        return (n & 1)? 1: -1;
    if(pow_mod(n, p >> 1,p) != 1)
        return -1;
    if(p & 2)
        return pow_mod(n, (p + 1) >> 2, p);
    int s = __builtin_ctzll(p ^ 1);
    ll q = p >> s,z = 2;
    for(; pow_mod(z, p >> 1, p) == 1 ; ++z);
    ll c = pow_mod(z, q, p), r = pow_mod(n, (q + 1) >> 1, p), t = pow_mod(n, q, p), tmp;
    for(int m = s, i; t != 1; ) {
        for(i = 0, tmp = t; tmp != 1; ++i) tmp = tmp * tmp % p;
        for(; i < --m; ) c = c * c % p;
        r = r * c % p; c = c * c % p; t = t * c % p;
    }
    return r;
}
