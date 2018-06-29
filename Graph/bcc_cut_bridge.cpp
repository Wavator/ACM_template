class bcc_bridges: public Graph {
public:
    vector<pair<int, int> > briges;
    int dfn[N],low[N];
    int clk;
    void dfs(int u, int fa) {
        dfn[u]=low[u]=++clk;
        int v;
        for (edge * t = li[u]; t; t = t->next) {
            v = t->y;
            if (!dfn[v]) {
                dfs(v,u);
                low[u]=min(low[u],low[v]);
                if(low[v] > dfn[u])
                    briges.emplace_back(u, v); // u <-> v is a bridge
            }
            else if(dfn[v] < dfn[u] && v != fa)
                low[u]=min(low[u],dfn[v]);
        }
    }
    void find_bridge(int n) {
        clk = 0;
        fill(dfn + 1, dfn + n + 1, 0);
        fill(low, low + n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            if (!dfn[i])
                dfs(i, 0);
        }
    }
};