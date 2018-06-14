const int N = 5002;
vector<int> e[N];
int ind[N];
int topo[N];
bool Topo(int n) {
    static int que[N];
    int head = 0, tail = 0;
    for (int i = 1; i <= n; ++i) {
        if (ind[i] == 0)
            que[tail++] = i;
    }
    while (head != tail) {
        int u = topo[n--] = que[head++];
        for (const auto &v: e[u]) {
            ind[v]--;
            if (ind[v] == 0)
                que[tail++] = v;
        }
    }
    return n == 0;
}
