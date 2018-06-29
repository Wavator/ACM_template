class lca_tree : public Graph {
public:
    static const int LOG = log2(N) + 1;
    int fa[N][LOG], dep[N];
    inline int LCA(int a,int b){
        if (dep[a] > dep[b])
            swap(a,b);
        for (int i = dep[b] - dep[a], j = 0; i > 0;i >>= 1, j++)
            if (i & 1)
                b = fa[b][j];
        if (a == b)
            return a;
        int k;
        for (k = 0; (1 << k) <= dep[a]; k++);
        for (; ~k; k--)
            if ((1 << k) <= dep[a] && fa[a][k] != fa[b][k])
                a = fa[a][k], b = fa[b][k];
        return fa[a][0];
    }
    void dfs(int u, int f) {
        for (int i = 1; i < LOG; ++i)
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
        int v;
        for (edge * t = li[u]; t; t = t->next) {
            v = t->y;
            if (v != f)
                dfs(v, u);
        }
    }
    void lca_prepare() {
        memset(fa, 0, sizeof(fa));
        dep[1] = 0;
        dfs(1, 0);
    }
};