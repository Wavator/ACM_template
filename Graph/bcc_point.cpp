
class bcc_point: public Graph {
    int low[N], bccno[N], clk, bcccnt, dfn[N], top;
    bool iscut[N];
    typedef pair<int, int> b;
    b stk[M];
    void dfs(int u, int fa) {
        low[u] = dfn[u] = ++clk;
        int k = 0, v;
        for (edge * t = li[u]; t; t = t->next) {
            v = t->y;
            b e = {u, v};
            if (!dfn[v]) {
                k++;
                stk[top++] = e;
                dfs(v, u);
                if (low[v] < low[u])
                    low[u] = low[v];
                if (low[v] >= dfn[u]) {
                    iscut[u] = true;
                    bcccnt++;
                    b x;
                    for(;;){
                        x = stk[--top];
                        bccno[x.first] = bcccnt;
                        bccno[x.second] = bcccnt;
                        if (x == e)
                            break;
                    }
                }
            } else if (v != fa) {
                stk[top++] = e;
                if (low[u] > dfn[v])
                    low[u] = dfn[v];
            }
        }
        if (fa == 0 && k == 1)
            iscut[u] = false;
    }
    void find_bcc(int n) {
        bcccnt = clk = top = 0;
        fill(low + 1, low + n + 1, 0);
        fill(bccno + 1, bccno + n + 1, 0);
        fill(dfn + 1, dfn + n + 1, 0);
        fill(iscut, iscut + n + 1, 0);
        for (int i = 1; i <= n; ++i)
            if (!dfn[i])
                dfs(i, 0);
    }
    void reBuild(Graph &o, int n) {
        //o.init();
        int i, j, u, v;
        edge * t;
        for (i = 1; i <= n; ++i) {
            u = bccno[i];
            for (t = li[i]; t; t =t ->next) {
                v = bccno[j = t->y];
                if (u != v)
                    o.add_edges(u, v);
            }
        }
    }
};