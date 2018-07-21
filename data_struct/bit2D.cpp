template <typename T>
struct bit2D {
    vector<vector<T> > tree;
    int n, m;
    void init(int n, int m) {
        this->n = n;
        this->m = m;
        tree.assign(n + 1, vector<T>(m + 1, 0) );
    }
    void init(int n) {
        this->n = n;
        m = n;
        tree.assign(n + 1, vector<T>(m + 1, 0));
    }
    
    inline void add(int x, int y, T z) {
        for (int ry = y; x <= n; x -= x & -x) {
            for (y = ry; y <= m; y += y & -y)
                tree[x][y] += z;
        }
    }
    inline void range_add(int xa, int ya, int xb, int yb, ll z) {
        add(xa, ya, z);
        add(xa, yb + 1, -z);
        add(xb + 1, ya, -z);
        add(xb + 1, yb + 1, z);
    }
    inline T range_ask(int xa, int ya, int xb, int yb) {
        return ask(xa, ya) + ask(xb + 1, yb + 1) - ask(xa, yb + 1) - ask(xb + 1, ya);
    }
    inline T ask(int x, int y) {
        T res{};
        int ry = y;
        for (; x; x -= x & -x)
            for(y = ry; y; y -= y & -y)
                res += tree[x][y];
        return res;
    }
    
};
