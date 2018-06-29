#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
class Graph {
public:
    static const int N = ::N, M = 1000001;
    typedef long long T;
    struct edge {
        int y;
        T w;
        edge * next;
    };
    edge e[M], *li[N];
    int etop;
    void init() {
        memset(li, 0, sizeof(li));
        etop = 0;
    }
    inline void add_edge(int u, int v, const T &w = 0) {
        e[etop].y = v;
        e[etop].next = li[u];
        e[etop].w = w;
        li[u] = &e[etop++];
    }
    inline void add_edges(int u, int v, const T &w = 0) {
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
};

class scc_dag : public Graph{
public:
    int ind[N], sz[N];
};

class scc_graph: public Graph {
public:
    int dfn[N], lower_link[N], scc_no[N], scc_cnt, clk, stk[N], top, sz[N];
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
                sz[scc_cnt]++;
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

    void rebuild(scc_dag &o, int n) {
        int u, v, j;
        edge * t;
        for (int i = 1; i <= n; ++i) {
            for (t = li[i]; t; t = t->next) {
                j = t->y;
                u = scc_no[i], v = scc_no[j];
                if (u != v) {
                    o.add_edge(u, v);
                    o.ind[v]++;
                }
            }
        }
        memcpy(o.sz, sz, sizeof(o.sz));
    }
}scc;
int mod;
class dp_dag: public scc_dag {
public:
    int dp[N], tdp[N], preDP[N], que[N];
    void DP(int n) {// n = scc_cnt
        int head = 0, tail = 0;
        for (int i = 1; i <= n; ++i) {
            if (ind[i] == 0)
                que[tail++] = i;
            dp[i] = sz[i];
            tdp[i] = 1;
        }
        for (int u, v; head != tail; ) {
            u = que[head++];
            for (edge * t = li[u]; t; t = t->next) {
                ind[v = t->y]--;
                if (ind[v] == 0)
                    que[tail++] = v;
                if (preDP[v] == u)
                    continue;
                if (dp[u] + sz[v] > dp[v]) {
                    dp[v] = dp[u] + sz[v];
                    tdp[v] = tdp[u];
                } else if (dp[u] + sz[v] == dp[v]) {
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
}solver;

int main () {
    int n, m;
    scanf("%d%d%d", &n, &m, &mod);
    for (int u, v; m--; ) {
        scanf("%d%d", &u, &v);
        scc.add_edge(u, v);
    }
    scc.find_scc(n);
    scc.rebuild(solver, n);
    solver.DP(scc.scc_cnt);
    return 0;
}