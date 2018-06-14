int fa[N][17], dep[N];
int LCA(int a,int b){
    if (dep[a] > dep[b])
        swap(a,b);
    for (int i = dep[b] - dep[a], j = 0; i > 0;i >>= 1, j++)
        if (i & 1)
            b = fa[b][j];
    if (a == b)
        return a;
    int k;
    for (k=0;(1<<k)<=dep[a];k++);
    for (;k>=0;k--)
        if ((1<<k)<=dep[a]&&fa[a][k]!=fa[b][k])
            a=fa[a][k],b=fa[b][k];
    return fa[a][0];
}
