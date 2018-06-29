class bcc_edge: public Graph {
public:
    int clk, dfn[N], low[N], Father[N], stk[N],top, bcc_cnt, bcc_no[N];
    void Tarjan(int u,int fa) {
        dfn[u] = low[u] = ++clk;
        Father[u] = fa;
        stk[top++] = u;
        int k = 0;
        int v;
        edge * t;
        for(t = li[u]; t; t = t->next) {
            v = t->y;
            if(v == fa && !k) {
                k++;
                continue;
            }
            if(!low[v]) {
                Tarjan(v, u);
                low[u] = min(low[u], low[v]);
            }
            else
                low[u] = min(low[u], dfn[v]);
        }
        if(dfn[u] == low[u]) {
            bcc_cnt++;
            for(;;) {
                v = stk[--top];
                bcc_no[v] = bcc_cnt;
                if (v == u)
                    break;
            }
        }
    }

    void find_bcc(int n) {
        for(int i = 1; i <= n; i++)
            if(dfn[i] == 0) Tarjan(i, i);
    }

    void re_build(Graph &o, int n) {
        for(int i = 1; i <= n; i++) {
            int v = Father[i];
            if(bcc_no[i] != bcc_no[v]) {
                o.add_edges(bcc_no[i], bcc_no[v]);
            }
        }
    }
};