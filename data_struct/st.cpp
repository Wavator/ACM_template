template <typename type>
class ST {
    static const int N = 100005;
    type st[N][32];
    type st_pre[N];
    
    function<type(type, type)> f;
    
    void init(int n, const type * arr) {
        st_pre[1] = 0;
        for (int i = 2; i <= n; i++) {
            st_pre[i] = st_pre[i - 1];
            if ((1 << st_pre[i] + 1) == i) ++st_pre[i];
        }
        for (int i = n - 1; i >= 0; --i) {
            st[i][0] = arr[i];
            for (int j = 1; (i + (1 << j) - 1) < n; ++j)
                st[i][j] = f(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
        }
    }
    
    type query(int l, int r) {
        type len = r - l + 1, k = st_pre[len];
        return f(st[l][k], st[r - (1 << k) + 1][k]);
    }
    
    
    void init_f(bool mx) {
        function<type(type, type)> maxf = [&](const type &x, const type &y) {
            return max(x, y);
        };
        function<type(type, type)> minf = [&](const type &x, const type &y) {
            return min(x, y);
        };
        if (mx)
            f = maxf;
        else
            f = minf;
    }
    
};
