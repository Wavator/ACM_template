void FWT(int a[],int n)
{
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++)
            {
                int x=a[i+j],y=a[i+j+d];
                //xor:
                a[i+j]=(x+y)%mod,a[i+j+d]=(x-y+mod)%mod;
                //and:a[i+j]=x+y;    
                //or:a[i+j+d]=x+y;    
            }
}
const int REV = inv(2);
void UFWT(int a[],int n)
{
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++)
            {
                int x=a[i+j],y=a[i+j+d];
                //xor:
                a[i+j]=1LL*(x+y)*REV%mod,a[i+j+d]=(1LL*(x-y)*REV%mod+mod)%mod;
                //and:a[i+j]=x-y;    
                //or:a[i+j+d]=y-x;    
            }
}
void solve(int a[],int b[],int n)
{
    FWT(a,n);
    FWT(b,n);
    for(int i=0;i<n;i++) a[i]=1LL*a[i]*b[i]%mod;
    UFWT(a,n);
}
