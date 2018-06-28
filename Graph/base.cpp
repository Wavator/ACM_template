struct Graph {
    static const int N = 100005, M = N << 1;
    struct edge {
        int y;
        edge * next;
    } e[M], *li[N];
    int etop;
    void init() {
        memset(li, 0, sizeof(li));
        etop = 0;
    }
    inline void add_edge(int u, int v) {
        e[etop].y = v;
        e[etop].next = li[u];
        li[u] = &e[etop++];
    }
    inline void add_edges(int u, int v) {
        add_edge(u, v);
        add_edge(v, u);
    }

};