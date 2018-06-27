int count_radius(const vector<int> e[]) {
    static int dep[N];
    int mx, pos;
    function<void(int, int)> dfs = [&](int u, int fa){
        if(dep[u] > mx) {
            mx = dep[u];
            pos = u;
        }
        for(const int &v: e[u])
        {
            if (v != fa)
            {
                dep[v] = dep[u] + 1;
                dfs(v, u);
            }
        }
    };
    mx=pos=-1;
    memset(dep, 0, sizeof(dep));
    dfs(1, 0);
    memset(dep,0,sizeof(dep));
    dfs(pos, 0);
    return mx;
}
