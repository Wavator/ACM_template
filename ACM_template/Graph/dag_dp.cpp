const int N = 100005;
vector<int> G[N];
int dfn[N], lower_link[N], scc_no[N], scc_cnt, clk, scc_sz[N];
stack<int> stk;
void dfs(int u){
    dfn[u] = lower_link[u] = ++clk;
    stk.push(u);
    for (const auto &v: G[u]){
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
            scc_sz[scc_cnt]++;
            if (x == u)
                break;
        }
    }
}

void find_scc(int n){
    clk = scc_cnt = 0;
    fill(scc_no + 1, scc_no + n + 1, 0);
    fill(dfn + 1, dfn + n + 1, 0);
    fill(scc_sz + 1, scc_sz + n + 1, 0);
    for(; !stk.empty(); stk.pop());
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            dfs(i);
}
int mod;
vector <int> dag[N];

int ind[N], dp[N], tdp[N], preDP[N];

void reBuild(int n) {
    for (int i = 1; i <= scc_cnt; ++i) {
        dp[i] = tdp[i] = ind[i] = preDP[i] = 0;
        dag[i].clear();
    }
    for (int i = 1; i <= n; ++i) {
        for (const auto&v: G[i]) {
            if (scc_no[i] != scc_no[v]) {
                dag[scc_no[i]].push_back(scc_no[v]);
                ind[scc_no[v]]++;
            }
        }
    }
}

void DP(int n) {// n = scc_cnt
    static int que[N];
    int head = 0, tail = 0;
    for (int i = 1; i <= n; ++i) {
        if (ind[i] == 0)
            que[tail++] = i;
        dp[i] = scc_sz[i];
        tdp[i] = 1;
    }
    for (; head != tail; ) {
        int u = que[head++];
        for (const auto&v: dag[u]) {
            ind[v]--;
            if (ind[v] == 0)
                que[tail++] = v;
            if (preDP[v] == u)
                continue;
            if (dp[u] + scc_sz[v] > dp[v]) {
                dp[v] = dp[u] + scc_sz[v];
                tdp[v] = tdp[u];
            } else if (dp[u] + scc_sz[v] == dp[v]) {
                tdp[v] += tdp[u];
                if (tdp[v] >= mod)
                    tdp[v] -= mod;
            }
            preDP[v] = u;
        }
    }
    int ans_sz = 0, ans_count = 0;
    for (int i = 1; i <= n; ++i) {
        if (ans_sz < dp[i]) {
            ans_sz = dp[i];
            ans_count = tdp[i];
        } else if (ans_sz == dp[i]) {
            ans_count += tdp[i];
            if (ans_count >= mod)
                ans_count -= mod;
        }
    }
    printf("%d\n%d\n", ans_sz, ans_count);
}
