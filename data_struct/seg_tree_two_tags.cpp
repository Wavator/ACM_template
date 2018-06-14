struct seg_tree {
    typedef long long ll;
    const ll mod = 1000000007;
    struct Seg {
        int l, r;
        ll sum;
        inline int mid() {
            return (l + r) >> 1;
        }
        inline int range() {
            return r - l + 1;
        }

        ll add, mul = 1;
    };
    Seg tree[N << 2];
    inline void push_up(int rt) {
        tree[rt].sum = (tree[rt << 1].sum + tree[rt << 1 | 1].sum) % mod;
    }
    void build(int l, int r, int rt) {
        tree[rt].l = l;
        tree[rt].r = r;
        if (l == r) {
            scanf("%lld", &tree[rt].sum);
            tree[rt].sum %= mod;
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, rt << 1);
        build(mid + 1, r, rt << 1 | 1);
        push_up(rt);
    }

    void push_down(int rt) {
        int mid = tree[rt].mid();
        int le = mid - tree[rt].l + 1;
        int ri = tree[rt].r - mid;
        (tree[rt << 1].mul *= tree[rt].mul) %= mod;
        (tree[rt << 1 | 1].mul *= tree[rt].mul) %= mod;
        ((tree[rt << 1].add *= tree[rt].mul) += tree[rt].add) %= mod;
        ((tree[rt << 1 | 1].add *= tree[rt].mul) += tree[rt].add) %= mod;
        ((tree[rt << 1].sum *= tree[rt].mul) += (1ll * le * tree[rt].add)) %= mod;
        ((tree[rt << 1 | 1].sum *= tree[rt].mul) += (1ll * ri * tree[rt].add)) %= mod;
        tree[rt].mul = 1;
        tree[rt].add = 0;
    }

    void add(int L, int R, int rt, ll val) {
        if (tree[rt].l >= L && tree[rt].r <= R) {
            (tree[rt].sum += 1ll * tree[rt].range() * val) %= mod;
            (tree[rt].add += val) %= mod;
            return;
        }
        push_down(rt);
        int mid = tree[rt].mid();
        if (L <= mid)
            add(L, R, rt << 1, val);
        if (R > mid)
            add(L, R, rt << 1 | 1, val);
        push_up(rt);
    }

    void mul(int L, int R, int rt, ll val) {
        if (tree[rt].l >= L && tree[rt].r <= R) {
            tree[rt].sum *= val;
            tree[rt].sum %= mod;
            tree[rt].mul *= val;
            tree[rt].mul %= mod;
            (tree[rt].add *= val) %= mod;
            return;
        }
        push_down(rt);
        int mid = tree[rt].mid();
        if (L <= mid)
            mul(L, R, rt << 1, val);
        if (R > mid)
            mul(L, R, rt << 1 | 1, val);
        push_up(rt);
    }

    ll query(int L, int R, int rt) {
        if (tree[rt].l >= L && tree[rt].r <= R) {
            return tree[rt].sum;
        }
        push_down(rt);
        int mid = tree[rt].mid();
        ll ans = 0;
        if (L <= mid)
            ans += query(L, R, rt << 1);
        if (R > mid)
            ans += query(L, R, rt << 1 | 1);
        ans %= mod;
        return ans;
    }
};
