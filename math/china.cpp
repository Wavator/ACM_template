ll china(int n, int*a, int*m) // x=a[i](mod m[i])
{
    ll M = 1, d, y, x = 0, w;
    rep(i,0,n)M*=m[i];
    rep(i,0,n){
        w=M/m[i];
        ext_gcd(m[i],w,d,d,y);
        x=(x+y*w*a[i])%mod;
    }
    return (x+mod)%mod;
}
