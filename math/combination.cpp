namespace comb {
    const int N = 100005;
    int fact[N], finv[N];
    void init() {
        fact[0]=1;
        rep(i,1,N)fact[i]=mul(fact[i-1],i);
        finv[N-1]=pow_mod(fact[N-1],mod-2);
        per(i,0,N-1){
            finv[i]=mul(finv[i+1],i+1);
#ifdef Wavator
            assert(fact[i]*finv[i]%mod==1);
#endif
        }
    }
    inline int C(int n, int m) {
        if (n < m) return 0;
        return mul(fact[n], mul(finv[m], finv[n - m]));
    }
    inline int lucas(int n, int m) {
        if(n < m) return 0;
        if(!m || n == m) return 1;
        return mul(lucas(n / mod,m / mod),C(n % mod, m % mod));
    }
}
