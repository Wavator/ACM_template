template <typename T>
class Descartes_treap {
public:
    int stk[N], ls[N], rs[N], vis[N], n, rt;
    pair<T, int> a[N];

    inline void init_big_treap(int _, const T * in) {
        n = _;
        rt = 0;
        for (int i = 1; i <= n; ++i) ls[i] = 0, rs[i] = 0, vis[i] = 0;
        for (int i = 1; i <= n; ++i) a[i].fi = -in[i], a[i].se = i;
    }

    inline void init_small_treap(int _, const T * in) {
        n = _;
        rt = 0;
        for (int i = 1; i <= n; ++i) ls[i] = 0, rs[i] = 0, vis[i] = 0;
        for (int i = 1; i <= n; ++i) a[i].fi = in[i], a[i].se = i;
    }

    inline void build() {
        int top = 0;
        for (int i = 1; i <= n; ++i) {
            int k = top;
            while (k > 0 && a[stk[k - 1]] > a[i]) --k;
            if (k) rs[stk[k - 1]] = i;
            if (k < top) ls[i] = stk[k];
            stk[k++] = i;
            top = k;
        }
        for (int i = 0; i <= n; ++i) vis[ls[i]] = vis[rs[i]] = 1;
        for (int i = 0; i <= n; ++i) if (vis[i] == 0) rt = i;
    }

    int dfs(int u) {
        int sz = 1;
        if (ls[u]) sz += dfs(ls[u]);
        if (rs[u]) sz += dfs(rs[u]);
        //(ans *= inv[sz]) %= mod;
        return sz;
    }
    void print(int u) {
        if (ls[u]) print(ls[u]);
        cerr << a[u].first << ' ';
        if (rs[u]) print(rs[u]);
    }
};
