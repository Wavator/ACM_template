class spfa: public Graph {
    T dist[N];
    const T INF = 0x3f3f3f3f3f3f3f3f;
    bool inque[N];
    queue<int> que;
    void spfa(int s, int n) {
        fill(dist, dist + n + 1, INF);
        fill(inque, inque + n + 1, false);
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
                        que.push(v);
                    }
                }
            }
            inque[u] = false;
        }
    }
};