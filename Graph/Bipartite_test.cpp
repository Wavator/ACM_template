const int N = 100005;
vector<int> G[N];
int c[N];
bool dfs(int u, int co) {
    c[u] = co;
    for (auto &e: G[u]) {
        if (!c[e] && !dfs(e, -co))
            return false;
        if (c[u] == c[e])
            return false;
    }
    return true;
}
bool check(int n) {
    memset(c, 0, sizeof(c));
    for (int i = 1; i <= n; ++i)
        if (c[i] == 0 && !dfs(i, 1))
            return false;
    return true;
}
