namespace comb
{
    const int N = ::N;
    ll fact[N], finv[N];
    void init()
    {
        fact[0]=1;
        rep(i,1,N)fact[i]=fact[i-1]*i%mod;
        finv[N-1]=pow_mod(fact[N-1],mod-2);
        per(i,0,N-1){
            finv[i]=finv[i+1]*(i+1)%mod;
            assert(fact[i]%finv[i]%mod==1);
        }
    }
    inline ll C(int n, int m)
    {
        return (fact[n] * finv[m] % mod) * finv[n - m] % mod;
    }
}
