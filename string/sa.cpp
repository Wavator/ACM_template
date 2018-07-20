class SA {
public:
    static const int N = 301000;
    int t1[N],t2[N],c[N],sa[N],rk[N],ht[N];
    char s[N];
    int len,m;

    SA(){}

    void init(const char * b, int n){
        len = n;
        //cerr << len << endl;
        rep(i, 0, n) s[i] = b[i];
    }

    void init(const char * b) {
        len = strlen(b);
        rep(i, 0, len) s[i] = b[i];
    }

    void init(const string &s) {
        int n = s.size();
        for (len = 0; len < n; ++len) this->s[len] = s[len];
    }

    void build() {
        int i, j, k, *x = t1, *y = t2;
        m = 256;
        memset(c, 0, m * sizeof(int));
        for(i = 0; i < len; ++i)
            ++c[x[i] = s[i]];
        for(i = 1; i < m; ++i)
            c[i] += c[i - 1];
        for(i = len - 1; i >= 0; --i)
            sa[--c[x[i]]] = i;
        for(k = 1; k <= len; k <<= 1, m = j) {
            j = 0;
            for(i = len - k; i < len; ++i)
                y[j++] = i;
            for(i = 0; i < len; ++i)
                if(sa[i] >= k)
                    y[j++] = sa[i] - k;
            memset(c, 0, m * sizeof(int));
            for(i = 0; i < len; ++i)
                ++c[x[y[i]]];
            for(i = 0; i < m; ++i)
                c[i] += c[i - 1];
            for(i = len - 1; i >= 0; --i)
                sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            j = 1;
            x[sa[0]] = 0;
            for(i = 1; i < len; ++i)
                x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? j - 1 : j++;
            x[len] = j;
            if(j >= len)
                break;
        }
        for(i = 0; i < len; ++i)
            rk[sa[i]] = i;
        for(i = k = 0; i < len; ++i) {
            if(k) --k;
            if(!rk[i]) {
                ht[rk[i]] = 0;
                continue;
            }
            for(j = sa[rk[i] - 1]; s[i + k] == s[j + k]; ++k);
            ht[rk[i]] = k;
        }
    }

//    inline int cmp(char * pt, int p) {
//        return strncmp(pt,s+sa[p],m);
//    }
//    inline int find(char* p) {
//        m = strlen(p);
//        if (cmp(p,0) < 0 || cmp(p,n-1) > 0)
//            return -1;
//        int l = 0, r = n - 1;
//        while (r >= l) {
//            static int mid;
//            mid = l + r >> 1;
//            int res = cmp(p,mid);
//            if (!res)
//                return mid;
//            if (res < 0)
//                r = mid - 1;
//            else
//                l = mid + 1;
//        }
//        return -1;
//    }



};
