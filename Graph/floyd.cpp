const int N = 1001;

int dis[N][N], G[N][N];

void floyd_w(int n) {
    for (int t = 1; t <= n; t++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (dis[i][t] + dis[t][j] < dis[i][j])
                    dis[i][j] = dis[i][t] + dis[t][j];
}

void floyd(int n) {
    memset(dis, 0x3f3f3f3f, sizeof(dis));
    for (int i = 1; i <= n; ++i)
        dis[i][i] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (G[i][j])
                dis[i][j] = G[i][j];
    floyd_w(n);
}
