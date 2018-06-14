const int N = 100005;

vector <int> e[N];

int topo[N], topo_ed[N];

int topo_cnt;

bool topo_dfs(int u) {
    topo_ed[u] = -1;
    for (auto &v: e[u]) {
        if (topo_ed[v] == -1)
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
