const int N = 10002;
int n, a[N], b[N], c[N];
inline db cal(db x) {
    db res = a[0]*x*x+b[0]*x+c[0];
    rep(i,1,n)res=max(res,a[i]*x*x+b[i]*x+c[i]);
    return res;
}
void solve() {
    scanf("%d",&n);
    rep(i,0,n)scanf("%d%d%d",a+i,b+i,c+i);
    db l=0.,r=1000.;
    rep(loop,0,100){
        db m1=l+(r-l)/3.;
        db m2=r-(r-l)/3.;
        if(cal(m1)<cal(m2))r=m2;
        else l=m1;
    }
    printf("%.4f\n",cal(l));
}
