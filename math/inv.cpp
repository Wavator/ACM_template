void ext_gcd(ll a, ll b, ll &d, ll &x, ll &y) {
    if (b) {
        ext_gcd(b, a % b, d, y, x);
        y -= x * (a / b);
    } else {
        d = a, x = 1, y = 0;
    }
}
ll get_inv(ll a, ll mod = mod) {
    ll d, x, y;
    ext_gcd(a, mod, d, x, y);
    return d == 1? (x < 0? x + mod: x): -1;
}

inv[0]=inv[1]=1;
for(ll i=2;i<N;++i){
    inv[i]=(mod-(mod/i)*(inv[mod%i])%mod)%mod;
}
