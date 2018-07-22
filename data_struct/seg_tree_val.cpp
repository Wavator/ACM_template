template <typename T>
struct seg_tree_val {
    static const int N = 100005, LOG = 21;
    int ls[N*LOG], rs[N*LOG], tot;
    int root;
    T l[N*LOG], r[N*LOG];
    int sum[N*LOG];
    void change(int &rt, T L, T R, const T &pos) {
        if (!rt) {
            rt = ++tot;
            l[rt]=L;r[rt]=R;
        }
        sum[rt]++;
        if(L==R)return;
        T mid = L + R >> 1;
        if(pos<=mid)change(ls[rt],L,mid,pos);
        else change(rs[rt],mid+1,R,pos);
    }

    int ask(int x,T L,T R) {
        if(!x) return 0;
        if(r[x] < L || l[x] > R) return 0;
        if(L<=l[x] && r[x]<=R) return sum[x];
        return ask(ls[x],L,R)+ask(rs[x],L,R);
    }
};
