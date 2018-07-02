#include<bits/stdc++.h>
using namespace std;
typedef double db;
const int N = 1001;
const db eps = 1e-8;
int n,fn,pfn,cfn,pre;
db a[N];
db f[N],cf[N],pf[N];
db getv(int x) {
    db sum=0;
    for(int i=0;i<=fn&&x-i>=0;i++)sum+=a[x-i]*f[i];
    return sum;
}
db stand(db x){return fabs(x)<eps?0:x;}
int main() {
    f[0]=-1;pre=-1;
    ostringstream os;
    while(cin >> a[n]) {
        cout << n + 1 << ' ' << a[n] << endl;
        n++;
        db curv = getv(n-1);
        if(fabs(curv) < eps)
            continue;
        for(int i=0;i<=fn;i++)f[i]/=curv;
        cfn = fn;
        for(int i=0;i<=fn;i++)cf[i]=f[i];
        if(pre==-1) {
            fn=n;
            for(int i=1;i<=fn;i++)f[i]=0;
        }
        else {
            for(int i=fn+1;i<=pfn+n-pre;i++)f[i]=0;
            fn=pfn+n-pre;
            for(int i=0;i<=pfn;i++)f[i+n-pre]-=pf[i];
        }
        pfn=cfn;
        for(int i=0;i<=pfn;i++)pf[i]=cf[i];
        pre=n;
        os<<"fn=";
        for(int i=1;i<=fn;i++) {
            os<<stand(-f[i]/f[0])<<"fn-"<<i;
            if(i < fn)
                os<<" + ";
        }
        os<<endl;
    }
    cout << "my ans:\n";
    cout << os.str() << endl;
    return 0;
}