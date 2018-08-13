namespace euler_sieve
{ // thanks @RoundGod
    const int N = 1000005;
    int prime[N];
    int phi[N];
    int miu[N];
    bool is_prime[N];
    int sieve(int n) {
        int p=0;
        fill(is_prime+2,is_prime+n+1,true);
        for(int i=2;i<=n;i++) {
            if(is_prime[i])
                prime[p++]=i;
            for(int j=0;j<p;j++) {
                if(prime[j]*i>n) break;
                is_prime[prime[j]*i]=false;
                if(i%prime[j]==0) break;
            }
        }
        return p;
    }
    void genphi(int n) {
        int p=0;
        memset(phi,0,sizeof(phi));
        phi[1]=1;
        for(int i=2;i<=n;i++) {
            if(is_prime[i]) {
                p++;
                phi[i]=i-1;
            }
            for(int j=0;j<p;j++) {
                if(prime[j]*i>n)
                    break;
                phi[i*prime[j]]=phi[i]*(i%prime[j]?prime[j]-1:prime[j]);
                if(i%prime[j]==0)
                    break;
            }
        }
    }
    void genmiu(int n) {
        int p=0;
        memset(miu,0,sizeof(miu));
        miu[1]=1;
        for(int i=2;i<=n;i++)
        {
            if(is_prime[i]) {
                p++;
                miu[i]=-1;
            }
            for(int j=0;j<p;j++)
            {
                if(prime[j]*i>n)
                    break;
                miu[i*prime[j]]=i%prime[j]?-miu[i]:0;
                if(i%prime[j]==0)
                    break;
            }
        }
    }
}
