const int N = 100005;
vector<int> e[N];
int c[N];
bool dfs(int u, int co) {
    c[u] = co;
    for (auto &v: e[u]) {
        if (!c[v] && !dfs(v, -co))
            return false;
        if (c[u] == c[v])
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
