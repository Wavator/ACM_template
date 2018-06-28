    int ind[N];
    int topo[N];
    bool Topo(int n) {
        static int que[N];
        int head = 0, tail = 0;
        for (int i = 1; i <= n; ++i) {
            if (ind[i] == 0)
                que[tail++] = i;
        }
        edge * t;
        while (head != tail) {
            int u = topo[n--] = que[head++];
            int v;
            for (t = li[u]; t; t = t->next) {
                ind[v = t->y]--;
                if (ind[v] == 0)
                    que[tail++] = v;
            }
        }
        return n == 0;
    }