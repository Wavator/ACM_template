namespace Kuhn_Munkres  {
    const int N = 201;
    const ll INF = 0x3f3f3f3f3f3f3f3fLL;
    int n;
    ll w[N][N], sx[N], sy[N], slack[N];
    int match[N], pre[N];
    bool vis[N];
    void augment(int rt) {
        int cur = 0;
        match[0] = rt;
        memset(vis, 0, (n + 1) * sizeof(bool));
        memset(slack, 0x3f, (n + 1) * sizeof(ll));
        do {
            int nxt = -1, u = match[cur];
            ll dt = INF;
            vis[cur] = 1;
            for (int v = 1; v <= n; ++v) {
                if (vis[v])
                    continue;
                ll tmp = sx[u] + sy[v] - w[u][v];
                if (slack[v] > tmp) {
                    slack[v] = tmp;
                    pre[v] = cur;
                }
                if (slack[v] < dt) {
                    dt = slack[v];
                    nxt = v;
                }
            }
            for (int v = 0; v <= n; ++v)
                if (vis[v]) {
                    sx[match[v]] -= dt;
                    sy[v] += dt;
                } else {
                    slack[v] -= dt;
                }
            cur = nxt;
        } while (match[cur]);
        for (int v = cur; v; v = pre[v])
            match[v] = match[pre[v]];
    }

    ll solve() {
        for (int i = 1; i <= n; ++i) {
            ll dt = 0;
            for (int j = 1; j <= n; ++j)
                dt = max(dt, w[i][j]);
            sx[i] = dt;
            sy[i] = match[i] = 0;
        }
        for (int i = 1; i <= n; ++i)
            augment(i);
        ll cost = 0;
        for (int i = 1; i <= n; ++i)
            cost += sx[i] + sy[i];
        return cost;
    }

    void init(ll a[N][N], int _n)
    {
        n = _n;
        memcpy(w, a, sizeof(w));
    }

}
