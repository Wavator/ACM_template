class Graph {
public:
    static const int N = ::N, M = N << 1;
    typedef long long T;
    struct edge {
        int y;
        T w;
        edge * next;
    }e[M], *li[N];
    edge * etop;
    void init() {
        memset(li, 0, sizeof(li[0]) * (etop - e + 1));
        etop = e;
    }
    inline void add_edge(int u, int v, const T &w = 0) {
        li[u] = &(*etop++=(edge){v,w,li[u]});
    }
    inline void add_edges(int u, int v, const T &w = 0) {
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
};
