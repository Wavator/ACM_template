class Dij: public Graph {
public:
    T dis[N];
    bool vis[N];
    //vector<int> pre[N];
    priority_queue<pair<T, int> > q;
    static const T inf = 0x3f3f3f3f3f3f3f3f;
    void dij (int st, int n) {
        for (int i = 0; i <= n; ++i) {
            dis[i] = inf;
            vis[i] = false;
        }
        q.emplace(dis[st] = 0, st);
        for (;!q.empty();) {
            int u = q.top().second;
            q.pop();
            if (vis[u])
                continue;
            vis[u] = true;
            int v;
            for (edge * t = li[u]; t; t = t->next) {
                v = t->y;
                T c = t->w;
                if (dis[v] > dis[u] + c) {
                    dis[v] = dis[u] + c;
                    q.emplace(-dis[v], v);
                    //pre[v].clear(); pre[v].push_back(u);
                }// else if (dis[v] == dis[u] + c) pre[v].push_back(u);
            }
        }
    }
};