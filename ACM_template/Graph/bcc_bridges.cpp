vector <int> e[N], tree[N];
inline void add_edge(int u, int v) {
    e[u].push_back(v);
    e[v].push_back(u);
}

int clk, dfn[N], low[N], Father[N], Stack[N], top, bcc_cnt, block[N];

void Tarjan(int u,int fa) {
    dfn[u] = low[u] = ++clk;
    Father[u] = fa;
    Stack[top++] = u;
    int k = 0;
    for(int &v: e[u]) {
        if(v == fa && !k) {
            k ++;
            continue;
        }
        if(!low[v]) {
            Tarjan(v, u);
            low[u] = min(low[u], low[v]);
        }
        else
            low[u] = min(low[u], dfn[v]);
    }

    if(dfn[u] == low[u])
    {
        bcc_cnt++;
        for(;;)
        {
            int v = Stack[--top];
            block[v] = bcc_cnt;
            if (v == u)
                break;
        }

    }
}

void find_bcc(int n) {
    for(int i = 1; i <= n; i++) {
        if(dfn[i] == 0)
            Tarjan(i, i);
    }
}

void re_build(vector<int> e[], int n) { // rebuild a tree.
    for(int i = 1; i <= n; i++) {
        int v = Father[i];
        if(block[i] != block[v]) {
            e[block[i]].push_back(block[v]);
            e[block[v]].push_back(block[i]);
        }
    }
}
