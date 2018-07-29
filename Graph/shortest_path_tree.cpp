class shortest_path_tree {
private:
    int n, m, k;
    vector < vector<pii> >e;
    vector < int> d;
    vector < vector< int > > pre;
    vector < vector<char> > ans;
    vector < char > curr;
    void read() {
        for (int i = 0, u, v; i < m; ++i){
            scanf("%d%d",&u,&v);
            --u,--v;
            e[u].push_back({v, i});
            e[v].push_back({u, i});
        }
    }
    void bfs() {
        d[0] = 0;
        queue<int> q;
        for (q.push(0); !q.empty(); q.pop()) {
            int u = q.front();
            for (const auto &p: e[u]) {
                int v = p.first;
                if (d[v] == -1) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
    }
    void get_pre() {
        for(int u = 1; u < n; ++u) {
            for(const auto &t:e[u]) {
                int v = t .first;
                if(d[v]+1==d[u])
                    pre[u].push_back(t.second);
            }
        }
    }
    void dfs(int u) {
        if (SZ(ans) >= k) return;
        if (u >= n) {
            ans.push_back(curr);
        }
        else
            for (const auto &v: pre[u]) {
                curr[v] = '1';
                dfs(u + 1);
                curr[v] = '0';
            }
    }
    void print() {
        ios::sync_with_stdio(false);
        cout.tie(nullptr);
        cout << ans.size() << '\n';
        for(const auto &s: ans) cout << s.data(), cout << '\n';
    }
public:
    shortest_path_tree(int n, int m, int k): n(n), m(m), k(k), e(n, vector<pii>()), d(n, -1), pre(n, vector<int>()), curr(m, '0'){}
    void solve() {
        read();
        bfs();
        get_pre();
        dfs(1);
        print();
    }
};
