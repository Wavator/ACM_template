#include<bits/stdc++.h>
using namespace std;
typedef long double db;
const int N = 1001;
const db eps = 1e-9;
int n, fn, pfn, cfn, pre;
db a[N], f[N], cf[N], pf[N];
db getv(int x) {
    db sum=0;
    for(int i=0;i<=fn&&x-i>=0;i++)sum+=a[x-i]*f[i];
    return sum;
}
inline db stand(db x){return fabs(x) < eps? 0: x;}
int main(){
    f[0] = pre = -1;
    string ans;
    ostringstream os(ans);
    while(cin >> a[n]) {
        n++;
        db curv = getv(n - 1);
        if(fabs(curv) < eps)
            continue;
        cout << n << ": " << a[n - 1] << '\n';
        for(int i = 0; i <= fn; i++)
            f[i] /= curv;
        cfn = fn;
        for(int i = 0; i <= fn; i++)
            cf[i] = f[i];
        if(pre == -1) {
            fn = n;
            for (int i = 1;i <= fn; i++)
                f[i]=0;
        }
        else {
            for(int i = fn + 1; i <= pfn + n - pre; i++)
                f[i]=0;
            fn = pfn + n - pre;
            for(int i = 0; i <= pfn; i++)
                f[i + n - pre] -= pf[i];
        }
        pfn = cfn;
        for(int i=0;i<=pfn;i++)
            pf[i]=cf[i];
        pre = n;
        os << "fn=";
        for(int i=1;i <= fn; i++) {
            os << stand(-f[i]/f[0])<<"fn-"<<i;
            if(i < fn) os<<" + ";
        }
        os << endl;
    }
    cout << endl;
    cout << "gg:\n";
    cout << os.str();
    return 0;
}