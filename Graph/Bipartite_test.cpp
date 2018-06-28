    int color[N];
    bool dfs(int u, int co) {
        color[u] = co;
        edge * t;
        int v;
        for (t = li[u]; t; t = t->next) {
            v = t->y;
            if (!color[v] && !dfs(v, -co))
                return false;
            if (color[u] == color[v])
                return false;
        }
        return true;
    }
    bool check(int n) {
        memset(color, 0, sizeof(int)*(n+1));
        for (int i = 1; i <= n; ++i)
            if (color[i] == 0 && !dfs(i, 1))
                return false;
        return true;
    }