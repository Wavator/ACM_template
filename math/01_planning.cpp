template <size_t N, typename T, typename Z = double>
struct zero_one_plan
{
    Z f[N];
    Z solve(T *c, T *s, int n, int k) { // max-> sigma(c[i])/sigma(s[i])
        Z l=0,r=*max_element(c,c+n);
        while(fabs(r-l)>eps){
            Z mid=(l+r)/2.;
            rep(i,0,n)f[i]=1.*c[i]-mid*s[i];
            nth_element(f,f+k,f+n,greater<Z>());
            Z sm=0;
            rep(i,0,k)sm+=f[i];
            if(sm>-eps)l=mid;
            else r=mid;
        }
        return l;
    }
};
