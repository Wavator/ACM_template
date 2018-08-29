namespace mo
{
    struct query {
        int l, r, id;
    };
    const int N = 50010, M = 50010;
    query q[M];
    int pos[N];
    int a[N];
    int ans[N],now;
    
    inline void add(int x) {

    }

    inline void del(int x) {

    }

    int n, Q;

    void main() {
        int blk = int(sqrt(n));
        while (blk * blk < n) blk++;
        for (int i = 1; i <= n; ++i) {
            pos[i] = (i - 1) / blk + 1;
        }
        sort(q+1,q+Q+1,[&](const query &a, const query&b){
            return pos[a.l]==pos[b.l]?a.r<b.r:pos[a.l]<pos[b.l];
        });
        int l = 1, r = 0;
        for (int i = 1; i <= Q; ++i) {
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
        for(int i=1;i<=Q;++i)printf("%d\n",ans[i]);
    }
}
