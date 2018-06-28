const int N = 100005;
vector<int> G[N];
    int dfn[N], lower_link[N], scc_no[N], scc_cnt, clk, stk[N], top;
    void dfs(int u){
        dfn[u] = lower_link[u] = ++clk;
        stk[top++] = u;
        int v;
        edge * t;
        for (t = li[u]; t; t = t->next){
            v = t->y;
            if (!dfn[v]) {
                dfs(v);
                lower_link[u] = min(lower_link[u], lower_link[v]);
            }
            else if (!scc_no[v])
                lower_link[u] = min(lower_link[u], dfn[v]);
        }
        if (lower_link[u] == dfn[u]){
            scc_cnt++;
            for (;;){
                scc_no[v = stk[--top]] = scc_cnt;
                if (v == u)
                    break;
            }
        }
    }

    void find_scc(int n){
        clk = scc_cnt = top = 0;
        fill(scc_no + 1, scc_no + n + 1, 0);
        fill(dfn + 1, dfn + n + 1, 0);
        for (int i = 1; i <= n; i++)
            if (!dfn[i])
                dfs(i);
    }