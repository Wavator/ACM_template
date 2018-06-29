class SPFA: public Graph {
    T dist[N];
    int cnt[N];
    const T INF = 0x3f3f3f3f3f3f3f3f;
    bool inque[N];
    queue<int> que;
    bool spfa(int s, int n) {
        fill(dist, dist + n + 1, INF);
        fill(inque, inque + n + 1, false);
        fill(cnt, cnt + n + 1, 0);
        dist[s] = 0;
        for (;!que.empty();que.pop());
        que.push(s);
        inque[s]=true;
        for (;!que.empty();) {
            int u=que.front();
            que.pop();
            int v;
            T w;
            for(edge * t = li[u]; t; t = t->next) {
                v = t->y;
                w = t->w;
                if(dist[u]+w<dist[v]) {
                    dist[v]=dist[u]+w;
                    if(!inque[v]) {
                        inque[v]=true;
                        if (++cnt[v] > n)
                            return true;
                        que.push(v);
                    }
                }
            }
            inque[u] = false;
        }
        return false;
    }
};