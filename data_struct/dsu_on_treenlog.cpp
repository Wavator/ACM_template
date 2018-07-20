const int N = 100005;

struct edge {
    int y;
    edge * next;
};

edge * li[N];

inline void add_edge(int u, int v) {
    static edge e[N << 1];
    static edge * top = e;
    li[u] = &(*top++ = (edge){v, li[u]});
    li[v] = &(*top++ = (edge){u, li[v]});
}

int sz[N], son[N];

void pre_dfs(int u, int fa) {
    sz[u] = 1;
    int v;
    for (edge * t = li[u]; t; t = t->next){
        v = t->y;
        if (v != fa) {
            pre_dfs(v, u);
            sz[u] += sz[v];
            if (sz[son[u]] < sz[v]) son[u] = v;
        }
    }
}

int c[N];

//bool is_big[N];

struct my_map {

    int cnt[N];
    set<int> s;

    int mx;

    ll res;

    inline void insert(int u) {
        cnt[c[u]]++;
        if (cnt[c[u]] > mx) {
            s.clear();
            mx = cnt[c[u]];
            res = c[u];
        } else if (mx == cnt[c[u]] && !s.count(c[u])) {
            s.insert(c[u]);
            res += c[u];
        }
    }

    void dfs(int u, int fa) {
        int v;
        cnt[c[u]]--;
        for (edge * t = li[u]; t; t = t->next) {
            v = t->y;
            if (v != fa)dfs(v, u);
        }
    }

    inline void del(int u, int fa) {
        res = 0; mx = 0;
        s.clear();
        dfs(u, fa);
    }

    inline ll query() {
        return res;
    }

};

my_map mp;

ll ans[N];

void insert(int u, int fa) {
    mp.insert(u);
    int v;
    for (edge * t = li[u]; t; t = t->next) {
        v = t->y;
        if (v != fa) insert(v, u);
    }
}

void dfs(int u, int fa) {
    edge * t;
    int v;
    for (t = li[u]; t; t = t->next) {
        v = t->y;
        if (v != fa && v != son[u]) {
            dfs(v, u);
            mp.del(v, u);
        }
    }

    if (son[u]) dfs(son[u], u);

    for (t = li[u]; t; t = t->next) {
        v = t->y;
        if (v != fa && v != son[u]) {
            insert(v, u);
        }
    }

    mp.insert(u);

    ans[u] = mp.query();

}
