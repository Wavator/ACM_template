class Graph {
public:
    static const int N = ::N, M = N << 1;
    typedef long long T;
    struct edge {
        int y;
        T w;
        edge * next;
    }e[M], *li[N];
    int etop;
    void init() {
        memset(li, 0, sizeof(li));
        etop = 0;
    }
    inline void add_edge(int u, int v, const T &w = 0) {
        e[etop].y = v;
        e[etop].next = li[u];
        e[etop].w = w;
        li[u] = &e[etop++];
    }
    inline void add_edges(int u, int v, const T &w = 0) {
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    
};