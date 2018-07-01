class segTree {
public:
    typedef long long T;
    T s[N << 2];
    typedef function<inline T (const T&, const T&)> fun;
    fun modi = [&](const T &i, const T &j){
        return i + j;
    };
    fun f = [&](const T &i, const T &j) {
        return i + j;
    };
    void changemodi(const fun &Modi) {
        modi = Modi;
    }
    void changeup(const fun &F) {
        f = F;
    }
    inline void push_up(int rt) {
        s[rt] = f(s[rt << 1], s[rt << 1 | 1]);
    }
    int n;
    void init(int n){this->n = n;}
    void build(int l, int r, int rt, T * x) {
        if (l == r) {
            s[rt] = s[l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,rt<<1,x);
        build(mid+1,r,rt<<1|1,x);
        push_up(rt);
    }
    void build(T * x){build(1, n, 1, x);}
    void change(int pos, T val, int l, int r, int rt) {
        if (l == r) {
            s[rt] = modi(s[rt], val);
            return;
        }
        int mid = l + r >> 1;
        if (pos <= mid)
            change(pos, val, l, mid, rt << 1);
        else
            change(pos, val, mid + 1, r, rt << 1 | 1);
        push_up(rt);
    }
    T query(int L, int R, int l, int r, int rt) {
        if (l >= L && r <= R)
            return s[rt];
        int mid = l + r >> 1;
        if (L > mid)
            return query(L, R, mid + 1, r, rt << 1 | 1);
        else if (R <= mid)
            return query(L, R, l, mid, rt << 1);
        return f(query(L, R, l, mid, rt << 1), query(L, R, mid + 1, r, rt << 1 | 1));
    }

    inline T query(int L, int R) {
        return query(L, R, 1, n, 1);
    }
};