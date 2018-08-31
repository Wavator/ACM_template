struct Comb {
    vector<int> fact, finv;
    int n;
    inline int inv(int a) {
        a %= mod;
        if (a < 0) a += mod;
        int b = mod, u = 0, v = 1;
        for (; a;) {
            int t = b / a;
            b -= t * a;
            swap(a, b);
            u -= t * v;
            swap(u, v);
        }
        if (b != 1)
            return -1;
        if (u < 0) u += mod;
        return u;
    }
    Comb(int n=1000000): n(n), fact(n + 2), finv(n + 2){
        fact[0]=1;
        for(int i=1;i<=n;++i){
            fact[i]=(int)((ll)fact[i-1]*i%mod);
        }
        finv[n] = inv(fact[n]);
        per(i,0,n){
            finv[i]=(ll)finv[i+1]*(i+1)%mod;
#ifdef Wavator
            assert(1ll*fact[i]*finv[i]%mod==1);
#endif
        }
    }
    inline int C(int n, int m) const{
        if (n < m) return 0;
        return (int)(((ll)fact[n] * finv[m] % mod) * finv[n - m] % mod);
    }
    inline int lucas(int n, int m) const{
        if(n < m) return 0;
        if(!m || n == m) return 1;
        return ((ll)lucas(n / mod,m / mod)*C(n % mod, m % mod));
    }
}comb;

struct combsqr {
    vector<vector<int>> C;
    int n;
    combsqr(int n = 3000):n(n), C(n+1, vector<int>(n+1,0)) {
        C[0][0] = 1;
        for(int i=1;i<=n;++i) {
            C[i][0]=C[i][i]=1;
            for(int j=1;j<i;++j) {
                C[i][j]=C[i-1][j-1]+C[i-1][j];
                if (C[i][j] >= mod) {
                    C[i][j] -= mod;
                }
            }
        }
    }
    int operator()(int n, int m) const {
        return n < m? 0: C[n][m];
    }
}comber;
