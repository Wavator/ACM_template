int second_longest(int st, int n) {
    static int dis[2][N];
    dij(dis[0], st, n);
    dij(dis[1], n, n);
    int mx = dis[0][n];
    edge * t;
    int ans=0x3f3f3f3f;
    for (int u = 1,v,w,c; u <= n; ++u) {
        for(t=li[u];t;t=t->next){
            v=t->y;
            w=t->w;
            c=dis[0][u]+dis[1][v]+w;
            if(c>mx&&c<ans)ans=c;
        }
    }
    return ans;
}
