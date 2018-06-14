const int N = 100005;
void Dijkstra(int s, int n, long long * dis, const vector<pair<int, long long> > e[]) {
    static bool vis[N];
    static const long long inf = 0x3f3f3f3f3f3f3f3fll;
    fill(dis + 1, dis + n + 1, inf);
    fill(vis + 1, vis + n + 1, false);
    priority_queue<pair<long long, int> > pq;
    pq.emplace(dis[s] = 0, s);
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        for (auto &p: e[u]) {
            long long c = p.second;
            int v = p.first;
            if (c + dis[u] < dis[v]) {
                dis[v] = dis[u] + c;
                pq.emplace(-dis[v], v);
            }
        }
    }
}
