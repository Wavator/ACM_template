int dep[N], son[N], sz[N];

void pre_dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    sz[u] = 1;
    int v;
    for (edge * t = li[u]; t; t = t->next) {
        v = t->y;
        if (v != fa) {
            pre_dfs(v, u);
            sz[u] += sz[v];
            if (sz[v] > sz[son[u]]) son[u] = v;
        }
    }
}

struct my_map {

    map<int, int> mp;
    int mx;
    void init() {
        mp.clear();
        mx = 0;
    }
    inline void add(int x) {
        mp[dep[x]]++;
        if (mp[dep[x]] > mp[dep[mx]]) mx = x;
        else if (mp[dep[x]] == mp[dep[mx]] && dep[mx] > dep[x]) mx = x;
    }

    inline int query() {
        return dep[mx];
    }

    void print(bool f = false) {
#ifdef Wavator
        debug("mx: %d", mx);
        if (f) {
            for (const auto& p: mp) {
                debug("dep, count: %d %d", p.first, p.second);
            }
        }
#endif
    }

};

my_map mp;

void merge(int x, int fa) {
    mp.add(x);
    for (edge * t = li[x]; t; t = t->next) {
        if (t->y != fa) merge(t->y, x);
    }
}
int ans[N];
void dfs(int u, int fa) {
    edge * t;
    int v;
    for (t = li[u]; t; t = t->next) {
        v = t->y;
        if (v != fa && v != son[u]) {
            dfs(v, u);
            mp.init();
        }
    }

    if (son[u]) dfs(son[u], u);

    for (t = li[u]; t; t = t->next) {
        v = t->y;
        if (v != fa && v != son[u]) {
            merge(v, u);
        }
    }

    mp.add(u);

    //mp.print();

    ans[u] = mp.query() - dep[u];

    //cerr << u << ' ' << mp.query() << ' ' << dep[u] << endl;
}

///////////////////////////////
struct my_map {
    map<int, int> mp;
    set<int> s;
    ll sum;
    int mx;
    void insert(int color) {
        mp[color]++;
        int x = mp[color], y = mp[mx];
        if (x > y) {
            s.clear();
            s.insert(color);
            sum = color;
            mx = color;
        } else if (x == y && !s.count(color)) {
            sum += color;
            s.insert(color);
        }
    }
    ll query() {
        return sum;
    }
    bool operator < (const my_map &o) const {
        return mp.size() < o.mp.size();
    }
    void operator += (const my_map &o) {
        int pre_mx = mp[mx];
        for (const auto &p: o.mp) {
            mp[p.first] += p.second;
            if (pre_mx < mp[p.first]) {
                mx = p.first;
                pre_mx = mp[p.first];
                s.clear();
                sum = p.first;
                s.insert(p.first);
            } else if (pre_mx == mp[p.first] && !s.count(p.first)) {
                sum += p.first;
                s.insert(p.first);
            }
        }
    }
};
my_map mps[N];
vector<int> e[N];
int c[N];
ll ans[N];
void dfs(int u, int fa) {
    mps[u].insert(c[u]);
    for (const auto &v: e[u]) {
        if (v != fa) {
            dfs(v, u);
            if (mps[u] < mps[v])
                swap(mps[u], mps[v]);
            mps[u] += mps[v];
        }
    }
    ans[u] = mps[u].query();
}
