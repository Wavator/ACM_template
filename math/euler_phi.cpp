int euler_phi(int n) {
    int m = (int)sqrt(n + 0.5);
    int res = n;
    for (int i = 2; i <= m; ++i) if (n % i == 0) {
        for(res = res / i * (i - 1); n % i == 0; n/= i);
    }
    if(n > 1) res = res / n * (n - 1);
    return res;
}
const int N = 100002;
int phi[N];
void gen_phi(int n) {
    phi[1] = 1;
    for(int i=2;i<=n;++i)if(!phi[i]){
        for(int j=i;j<=n;j+=i){
            if(!phi[j])phi[j]=j;
            phi[j]=phi[j]/i*(i-1);
        }
    }
}
