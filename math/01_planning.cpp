int n, k;

int s[N], c[N];
db f[N];
int main() {
    scanf("%d%d", &n, &k);
    rep(i,0,n)scanf("%d",s+i);
    rep(i,0,n)scanf("%d",c+i);
    db l=0,r=*max_element(c,c+n);
    while(fabs(r-l)>eps){
        db mid=(l+r)/2.;
        rep(i,0,n)f[i]=1.*c[i]-mid*s[i];
        sort(f,f+n,greater<db>());
        db s=0;
        rep(i,0,k)s+=f[i]; // remain k elements to make sigma(c[i])/sigma(s[i]) maximize.
        if(s>0)l=mid;
        else r=mid;
    }
    return !printf("%.10f\n",l);
}
