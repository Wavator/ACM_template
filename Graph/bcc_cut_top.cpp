class bcc_cut_top: public Graph {
public:
    int clk, low[N], dfn[N];
    bool iscut[N];
    void dfs(int u, int fa) {
        dfn[u] = low[u] = ++clk;
        int k = 0, v;
        for (edge * t = li[u]; t; t = t->next) {
            v = t->y;
            if (!dfn[v]) {
                k++;
                dfs(v, u);
                if (low[u] >= low[v])
                    low[u] = low[v];
                if (low[v] >= dfn[u])
                    iscut[u] = true;
            } else if (v != fa && dfn[v] < low[u])
                low[u] = dfn[v];
        }
        if (fa == 0 && k == 1)
            iscut[u] = false;
    }
    void find_cut_top(int n) {
        clk = 0;
        fill(low + 1, low + n + 1, 0);
        fill(iscut + 1, iscut + n + 1, false);
        fill(dfn + 1, dfn + n + 1, 0);
        for (int i = 1; i <= n; ++i)
            if (!dfn[i])
                dfs(i, 0);
    }
    vector <int> get_tops(int n) {
        vector<int> res;
        for (int i = 1; i <= n; ++i)
            if (iscut[i])
                res.push_back(i);
        return res;
    }
};