
struct query {
    int l, r, id;
};

const int N = 50010, M = 50010;

query q[M];

int pos[N];
int a[N];

int cnt[N];

ll ans[N];
ll now;
inline ll sqr(ll x) {
    return x*x;
}
inline void add(int x) {
    x = a[x];
    now -= sqr(cnt[x]);
    now += sqr((++cnt[x]));
}

inline void del(int x) {
    x = a[x];
    now -= sqr(cnt[x]);
    now += sqr((--cnt[x]));
}

int main() {
#ifdef Wavator
    freopen("test.in", "r", stdin);
#endif
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    int blk = int(sqrt(n));
    while (blk * blk < n)
        blk++;
    for (int i = 1; i <= n; ++i) {
        pos[i] = (i-1) / blk + 1;
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    sort(q+1,q+m+1,[&](const query &a, const query&b){
        return pos[a.l]==pos[b.l]?a.r<b.r:pos[a.l]<pos[b.l];
    });
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        int L = q[i].l, R = q[i].r;
        if(r < R){
            for(r++;r<=R;add(r++));
            --r;
        }
        if(r>R)
            for(; r>R; del(r--));
        if(l<L)for(;l < L;del(l++));
        if(l>L){
            for(l--; l >= L;add(l--));
            l++;
        }
        ans[q[i].id]=now;
    }
    for (int i = 1; i <= m; ++i) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}
