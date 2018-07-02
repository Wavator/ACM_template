typedef long long ll;
namespace comb {
    vector<ll> f, inv;
    const ll mod=1000000009;
    void init(int n = 100005) {
        f.resize(n+1);
        inv.resize(n+1);
        f[0]=1;
        for(ll i=1;i<=n;++i)
            f[i]=f[i-1]*i%mod;
        inv[0]=inv[1]=1;
        for(ll i=2;i<=n;++i){
            inv[i]=(mod-(mod/i)*(inv[mod%i])%mod)%mod;
        }
    }
    inline ll C(ll n, ll m) {
        return (f[n] * inv[m] % mod) * inv[n - m];
    }
}