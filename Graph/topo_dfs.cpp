    int topo[N], topo_ed[N];

    int topo_cnt;

    bool topo_dfs(int u) {
        topo_ed[u] = -1;
        edge * t;
        int v;
        for (t = li[u]; t; t = t->next) {
            if (topo_ed[v = t->y] == -1)
                return false;
            if (topo_ed[v] == 0)
                if (!topo_dfs(v))
                    return false;
        }
        topo_ed[u] = 1;
        topo[--topo_cnt] = u;
        return true;
    }

    bool topo_sort(int n) {
        fill(topo_ed + 1, topo_ed + n + 1, 0);
        topo_cnt = n;
        for (int i = 1; i <= n; ++i)
            if (!topo_ed[i] && !topo_dfs(i))
                return false;
        return true;
    }