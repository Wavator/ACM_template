const int N = 100005;
vector<int> e[N];
int dfn[N], lower_link[N], scc_no[N], scc_cnt, clk;
stack<int> stk;
void dfs(int u){
    dfn[u] = lower_link[u] = ++clk;
    stk.push(u);
    for (auto &v: e[u]){
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
            int x = stk.top();
            stk.pop();
            scc_no[x] = scc_cnt;
            if (x == u)
                break;
        }
    }
}

void find_scc(int n){
    clk = scc_cnt = 0;
    fill(scc_no + 1, scc_no + n + 1, 0);
    fill(dfn + 1, dfn + n + 1, 0);
    while (!stk.empty())
        stk.pop();
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            dfs(i);
}
