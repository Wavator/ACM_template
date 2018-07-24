const int N = 250010, LOG = 20;

struct edge {
    int v;
    ll w;
    edge(int v = 0, int w = 0): v(v), w(w){}
};

vector<edge> e[N];
vi g[N];

int pos[N], fa[N][LOG], dep[N];
int clk;
ll min_dis[N];
void pre_dfs(int u) {
    pos[u] = ++clk;
    for(int i = 1; i < LOG; i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    edge v;
    for (int i = 0; i < SZ(e[u]); ++i) {
        v = e[u][i];
        if (v.v != fa[u][0]) {
            min_dis[v.v] = min(min_dis[u], (ll) v.w);
            dep[v.v] = dep[u] + 1;
            fa[v.v][0] = u;
            pre_dfs(v.v);
        }
    }
}

void init_vtree() {
    min_dis[1] = 1ll<<60;
    pre_dfs(1);
}

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

ll dp(int u) {
    if (!SZ(g[u])) return min_dis[u];
    ll res = 0;
    for (int i = 0; i < SZ(g[u]); ++i) res += dp(g[u][i]);
    g[u].clear();
    return min(res, min_dis[u]);
}

inline void insert_vtree(int u, int v) {
    if(u^v)g[u].push_back(v);
}
void build_vtree(int * h, int K, int root=1) {
    sort(h+1,h+K+1,[&](const int &x, const int &y) {
        return pos[x] < pos[y];
    });
    int tot=0;
    h[++tot]=h[1];
    for(int i=2;i<=K;i++)
        if(LCA(h[tot],h[i])!=h[tot])h[++tot]=h[i];
    static int st[N];
    int top = 0;
    st[++top]=root;
    for(int i=1;i<=tot;i++) {
        int now=h[i],f=LCA(now,st[top]);
        for(;;) {
            if(dep[f]>=dep[st[top-1]]) {
                insert_vtree(f,st[top--]);
                if(st[top]!=f)st[++top]=f;
                break;
            }
            insert_vtree(st[top-1],st[top]);top--;
        }
        if(st[top]!=now)st[++top]=now;
    }
    while(--top)insert_vtree(st[top],st[top+1]);
}
