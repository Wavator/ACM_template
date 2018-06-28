    int Color[N];
    bool dfs(int u, int co) {
        Color[u] = co;
        int v;
        edge * t;
        for (t = li[u]; t; t = t->next) {
            v = t->y;
            if (!Color[v] && !dfs(v, -co))
                return false;
            if (Color[u] == Color[v])
                return false;
        }
        return true;
    }
    bool check(int n) {
        memset(Color, 0, sizeof(Color));
        for (int i = 1; i <= n; ++i)
            if (Color[i] == 0 && !dfs(i, 1))
                return false;
        return true;
    }