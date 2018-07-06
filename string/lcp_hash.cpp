class LCP_Hash {
public:
    static const ull base = 19260817;
    static const int N = 40005;
    ull H[N], hash_pow[N], hash_val[N];
    int rank[N];
    int pos, n, m;
    inline bool contains_length_l(int L) {
        pos = -1;
        int c = 0;
        for (int i = 0; i < n - L + 1; ++i) {
            rank[i] = i;
            hash_val[i] = H[i] - H[i + L] * hash_pow[L];
        }
        sort(rank, rank+n-L+1, [&](const int &a, const int &b){
            return hash_val[a] < hash_val[b] || (hash_val[a] == hash_val[b] && a < b);
        });
        for (int i = 0; i < n - L + 1; ++i) {
            if (!i || hash_val[rank[i]] != hash_val[rank[i - 1]]) {
                c = 0;
            }
            if (++c >= m && rank[i] > pos)
                pos = rank[i];
        }
        return pos >= 0;
    }

    void init(const char * s) {
        n = (int)strlen(s);
        H[n] = 0;
        for (int i = n - 1; ~i; --i) {
            H[i] = H[i + 1] * base + (s[i] - 'a');
        }
        hash_pow[0] = 1;
        for (int i = 1; i <= n; ++i)
            hash_pow[i] = hash_pow[i - 1] * base;
    }

    //pair<int,int> lcp;
    
    bool gao(int m) {
        this->m = m;
        int ans;
        if (!contains_length_l(1))
            return false;
        ans=pos;
        int l = 1, r = n + 1;
        while (r > l + 1) {
            static int mid;
            mid = l + r >> 1;
            if (contains_length_l(mid)) {
                l = mid;
                ans = pos;
            } else
                r = mid;
        }
        //contains_length_l(l);
        printf("%d %d\n", l, ans);
        return true;
    }

};