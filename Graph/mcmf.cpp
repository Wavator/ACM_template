const int oo = 0x3f3f3f3f;
class MCMF {
public:
    struct edge {
        int from, to, cap, flow, cost;
        edge(int from = 0, int to = 0, int cap = 0, int flow = 0, int cost = 0): from(from), to(to), cap(cap), flow(flow), cost(cost){}
    };

    static const int N = 2100;
    int n, s, t;
    vector<edge> edges;
    vi G[N];
    bool inq[N];
    int d[N], p[N], a[N];

    void init(int n) {
        this->n = n;
        REP(i, 0, n) G[i].clear();
        edges.clear();
    }
    inline void add_edge(int u, int v, int cap, int cost) { // cost
        G[u].push_back(SZ(edges));
        edges.emplace_back(u, v, cap, 0, cost);
        G[v].push_back(SZ(edges));
        edges.emplace_back(v, u, 0, 0, -cost);
    }
    inline bool bfs(int &flow, int &cost) {
        REP(i, 0, n) d[i] = oo, inq[i] = false;
        d[s] = 0;
        inq[s] = 1;
        p[s] = 0;
        a[s] = oo;
        static queue<int> q;
        for(;!q.empty();q.pop());
        for (q.push(s); !q.empty(); q.pop()) {
            static int u;
            u = q.front();
            inq[u] = 0;
            for (const int&i: G[u]) {
                edge & e = edges[i];
                if (e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = i;
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if (!inq[e.to]) {
                        q.push(e.to);
                        inq[e.to] = true;
                    }
                }
            }
        }
        if (d[t] == oo) return false;
        flow += a[t];
        cost += d[t] * a[t];
        for (int u = t; u != s; u = edges[p[u]].from) {
            edges[p[u]].flow += a[t];
            edges[p[u] ^ 1].flow -= a[t];
        }
        return true;
    }

    int get_min_cost_flow(int s, int t) {
        int flow = 0, cost = 0;
        for (this->s = s, this->t = t; bfs(flow, cost););
        return cost;
    }

};
