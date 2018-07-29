
int sz[maxn], best[maxn], tot;

bool vis[maxn];

void get_root(int u, int fa, int &root) {
    sz[u] = 1;
    best[u] = 0;
    for (edge * t = li[u]; t; t = t->next) {
        int v = t->y;
        if (v != fa && !vis[v]) {
            get_root(v, u, root);
            sz[u] += sz[v];
            best[u] = max(best[u], sz[v]);
        }
    }
    best[u] = max(best[u], tot - best[u]);
    if (root == 0 || best[u] < best[root]) root = u;
}
