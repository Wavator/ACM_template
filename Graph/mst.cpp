bool mst(Graph &o, const vector<pair<int, pair<int, int> > > &e, int n) {
    sort(e.begin(), e.end());
    static DSU dsu;
    dsu.init(n);
    int need = n - 1;
    for (auto &b: e) {
        int u = b.second.first, v = b.second.second;
        auto &T = b.first;
        if (dsu.unite(u, v)) {
            need--;
            o.add_edges(u, v, T);
            if (need == 0)
                return true;
        }
    }
    return false;
}

bool mst(const vector<pair<int, pair<int, int> > > &e, int n, long long &ans) {
    sort(e.begin(), e.end());
    static DSU dsu;
    dsu.init(n);
    int need = n - 1;
    ans = 0;
    for (auto &b: e) {
        int u = b.second.first, v = b.second.second;
        auto &T = b.first;
        if (dsu.unite(u, v)) {
            need--;
            ans += T;
            if (need == 0)
                return true;
        }
    }
    return false;
}