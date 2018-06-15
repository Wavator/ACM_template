namespace combination {
    typedef long long ll;
    ll mod = 1e9+7;
    vector<ll> fact, inv;
    ll powMod(ll a, ll b) {
        ll res = 1;
        for (a%=mod; b; b >>= 1, a = a * a % mod)
            if (b & 1)
                res = res * a % mod;
        return res;
    }
    void init(int n, ll p = 1e9+7) {
        combination::mod = p;
        fact.resize(n+1);
        inv.resize(n+1);
        fact[0]=fact[1]=1;
        for(ll i=2;i<=n;++i)
            fact[i]=fact[i-1]*i%mod;
        inv[n]=powMod(fact[n],mod-2);
        for(int i=n-1;~i;--i)
            inv[i]=inv[i+1]*(i+1)%mod;
    }
    inline ll C(int n, int m) {
        assert(n >= 0 && m >= 0);
        return ((fact[n] * inv[m] % mod) * inv[n - m]) % mod;
    }
}
