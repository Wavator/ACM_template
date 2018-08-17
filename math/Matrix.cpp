struct Mat{
    static const int siz = 10;
    ll a[siz][siz];
    int n,m;
    Mat(int _n,int _m){
        n=_n,m=_m;
        for(int i=0;i<n;i++)
            fill(a[i],a[i]+m,0);
    }

    ll*operator[](const int x){
        return a[x];
    }

    Mat operator*(const Mat &b)const{
        Mat ret(n,b.m);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                for(int k=0;k<m;k++){
                    ll t = (ll)a[i][k] * b.a[k][j];
                    if (t >= mod)
                        t %= mod;
                    ret[i][j] += t;
                    if (ret[i][j] >= mod)
                        ret[i][j] -= mod;
                }
        return ret;
    }

    Mat operator^(long long k)const{
        Mat ret(n,m),b = *this;
        for(int i=0;i<n;++i)ret[i][i]=1;
        for(;k;k>>=1,b=b*b){
            if(k&1)
                ret=ret*b;
        }
        return ret;
    }

    ll delta() const {
        ll res = 1;
        for(ll i = 0; i < n; i++)
        {
            for(ll j = i; j < n; j++)
                if(a[j][i]!=0)
                {
                    for(ll k = i; k < n; k++)
                        swap(a[i][k],a[j][k]);
                    if(i != j)
                        res = (-res+mod) % mod;
                    break;
                }
            if(a[i][i] == 0)
            {
                res = 0;//不存在
                break;
            }
            for(ll j = i+1; j < n; j++)
            {
                ll mut = (a[j][i]*pow_mod(a[i][i],mod-2))%mod;
                for(ll k = i; k < n; k++)
                    a[j][k] = (a[j][k]-(a[i][k]*mut)%mod+mod)%mod;
            }
            res = (res * a[i][i])%mod;
        }
        return res;
    }

    void get_matrix_tree(int n, int g[siz][siz])
    {
        *this = Mat(n, n);
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                a[i][i]+=g[i][j];
                a[i][j]-=g[i][j];
            }
        }
    }

};
