const int oo = 0x3f3f3f3f;
class Dinic {
public:
    static const int N = 210 * 2;
    struct edge {
        int to, cap, flow;
        edge(int to, int cap): to(to), cap(cap), flow(0){}
    };
    int n, s, t;
    vector<edge> e;
    vector<int> G[N];
    bool vis[N];
    int d[N];
    int cur[N];
    inline void add_edge(int u, int v, int c) {
        G[u].push_back(SZ(e));
        e.push_back(edge(v, c));
        G[v].push_back(SZ(e));
        e.push_back(edge(u, 0));
    }
    inline bool bfs() {
        memset(vis, 0, n + 1);
        static int q[N];
        int head = 0, tail = 0;
        q[tail++] = s;
        d[s] = 0, vis[s] = true;
        for (; tail ^ head;) {
            int u = q[head++];
            for (const int &x: G[u]) {
                edge & now = e[x];
                if (!vis[now.to] && now.cap > now.flow) {
                    vis[now.to] = true;
                    d[now.to] = d[u] + 1;
                    q[tail++] = now.to;
                }
            }
        }
        return vis[t];
    }
    int dfs(int x,int a) {
        if (x == t || a == 0)return a;
        int flow = 0, f;
        for (int &i = cur[x]; i < G[x].size(); i++) {
            edge &now = e[G[x][i]];
            if (d[x] + 1 == d[now.to] && (f = dfs(now.to, min(a, now.cap - now.flow))) > 0) {
                now.flow += f;
                e[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }
    int get_max_flow() {
        int flow = 0;
        for (;bfs();) {
            memset(cur, 0, sizeof(cur[0]) * (n + 1));
            flow += dfs(s, oo);
        }
        return flow;
    }
    void init(int s, int t, int n) {
        this->n = n;
        this->s = s;
        this->t = t;
        for (int i = 0; i <= n; ++i) {
            G[i].clear();
        }
        e.clear();
    }
}dc;
