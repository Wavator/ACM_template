class Mo
{
public:
    struct query {
        int l, r, id, lb;
        bool operator<(const query &o) const {
            return lb==o.lb?(((lb)&1)?r<o.r:r>o.r): lb<o.lb;
        }
    }q[M];
    int a[N];
    int ans[N];
    int n, Q, blk;
    inline void add(int x)
    {
        x=a[x];
    }
    inline void del(int x)
    {
        x = a[x];
    }
    void init()
    {
        blk = (int)sqrt(n);
        // read a, base 1
        // read Q, base 1
        for(int i=1;i<=Q;++i){
            sc(q[i].l,q[i].r);
            q[i].id=i;
            q[i].lb=q[i].l/blk;
        }
        sort(q + 1, q + Q + 1);

    }
    int now;
    void solve()
    {
        sort(q + 1, q + Q + 1);
        int l = 1, r = 0;
        for (int i = 1; i <= Q; ++i)
        {
            int L = q[i].l, R = q[i].r;
            if(r < R)
            {
                for(r++;r<=R;add(r++));
                --r;
            }
            if(r>R)
            {
                for(; r>R; del(r--));
            }
            if(l<L)
            {
                for(;l < L;del(l++));
            }
            if(l>L)
            {
                for(l--; l >= L;add(l--));
                l++;
            }
            ans[q[i].id]=now;
        }
    }
};
