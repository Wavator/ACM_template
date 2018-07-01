class DSU {
public:
    int fa[N],rk[N],tp ;
    pair<int*,int> st [500000<<1] ; // query_count
    inline int find(int x){
        for(;x^fa [x];)
            x=fa[x];
        return x;
    }
    void init(int n){
        tp=0;
        for(int i=1; i<=n; ++i)
            fa[i]=i,rk[i]=1 ;
    }
    inline int join(int u,int v) {
        int fu=find(u),fv=find(v);
        if(fu==fv)
            return 0;
        if(rk[fu]<rk[fv])
            swap(fu,fv);
        st[++tp]=make_pair(fa+fv,fa[fv]);
        fa[fv]=fu;
        st[++tp]=make_pair(rk+fu,rk [fu]);
        ++rk[fu];
        return 2;
    }
    inline bool same(int u,int v){
        return find(u)==find(v);
    }
    inline void rollback(){
        *st[tp].first= st[tp].second ;
        -- tp ;
    }
};