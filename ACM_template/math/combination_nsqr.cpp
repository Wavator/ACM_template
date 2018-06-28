long long C[2010][2010];
void combination_prepare(int n, const long long &mod) {
    C[0][0] = 1;
    for(int i=1;i<=n;++i) {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;++j)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
    }
}
