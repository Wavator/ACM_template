const int N = 200005;

struct persistent_segment_tree { // static interval kth minimum value query

    const static int M = ::N * 20;

    int sum[M], ls[M], rs[M], root[N], tot;
    int n;
    void build(int sz) {
        memset(sum,0,sizeof(sum));
        tot=0;
        memset(ls,0,sizeof(ls));
        memset(rs,0,sizeof(rs));
        memset(root,0,sizeof(root));
        this->n=sz;
        build(root[0],1,sz);
    }

    void build(int &rt,int l,int r) {
        rt=++tot;
        sum[rt]=0;
        if(l==r)
            return;
        int mid=l+r>>1;
        build(rt,l,mid);
        build(rt,mid+1,r);
    }

    void change(int &rt,int pre,int l,int r,int val) {
        rt=++tot;
        ls[rt]=ls[pre];
        rs[rt]=rs[pre];
        sum[rt]=sum[pre]+1;
        if(l==r)
            return;
        int mid=l+r>>1;
        if(val<=mid)
            change(ls[rt],ls[rt],l,mid,val);
        else
            change(rs[rt],rs[rt],mid+1,r,val);
    }

    void change(int now,int pre,int val){
        change(root[now],root[pre],1,n,val);
    }


    int query(int L,int R,int l,int r,int val){
        if(l==r)
            return l;
        int mid=l+r>>1;
        int x=sum[ls[R]]-sum[ls[L]];
        if(x<val)
            return query(rs[L],rs[R],mid+1,r,val-x);
        else
            return query(ls[L],ls[R],l,mid,val);
    }

    int query(int l, int r, int k){
        return query(root[l-1],root[r],1,n,k);
    }

}tree;
int a[N], b[N];

int main() {
#ifdef Wavator
    freopen("test.in", "r", stdin);
#endif
    int n, q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    memcpy(b,a,sizeof(b));
    sort(b+1,b+n+1);
    int m=unique(b+1,b+n+1)-b-1;
    tree.build(m);
    for(int i=1;i<=n;++i){
        int p=lower_bound(b+1,b+m+1,a[i])-b;
        tree.change(i,i-1,p);
    }
    for(int l,r,k;q--;){
        scanf("%d%d%d",&l,&r,&k);
        printf("%d\n",b[tree.query(l,r,k)]);
    }
    return 0;
}
