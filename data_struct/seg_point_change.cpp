
template <typename type>
class segTree {
public:
    function<type(type, type)> f = [&](const type &a, const type &b) {
        return a + b;
    };

    segTree(function<type(type, type)> f):f(f){}
    
    segTree(){}
    
    vector<type> a;
    int n;
    void init(int n) {
        this->n = n;
        a.resize(static_cast<unsigned int>(n << 2 | 1));
    }
    inline void push_up(int rt) {
        a[rt] = f(a[rt << 1], a[rt << 1 | 1]);
    }
    void build(int l, int r, int rt, type * in) {
        if (l == r) {
            a[rt] = in[l];
            return;
        }
        int mid = l + r >> 1;
        build(l, mid, rt << 1, in);
        build(mid + 1, r, rt << 1 | 1, in);
        push_up(rt);
    }

    void build(type*in){
        build(1, n, 1, in);
    }

    void change(int pos, type x, int l, int r, int rt, const function<type(type, type)> &ff = f) {
        if (l == r) {
            a[rt] = ff(a[rt], x);
            return;
        }
        int mid = l + r >> 1;
        if (pos <= mid)
            change(pos, x, l, mid, rt << 1, ff);
        else
            change(pos, x, mid + 1, r, rt << 1 | 1, ff);
        push_up(rt);
    }

    inline void change(int pos, type x, const function<type(type, type)> ff = f) {
        change(pos, x, 1, n, 1, ff);
    }

    type query(int L, int R, int l, int r, int rt) {
        if (l >= L && r <= R)
            return a[rt];
        int mid = l + r >> 1;
        if (L > mid)
            return query(L, R, mid + 1, r, rt << 1 | 1);
        else if (R <= mid)
            return query(L, R, l, mid, rt << 1);
        return f(query(L, R, l, mid, rt << 1), query(L, R, mid + 1, r, rt << 1 | 1));
    }

    inline type query(int L, int R) {
        return query(L, R, 1, n, 1);
    }

};


