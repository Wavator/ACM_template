template <typename type>
class mat {
public:
    static const long long mod = 0x989687;
    int n;
    vector<vector<type > > a;
    mat(int n = 0, type dig = 0) : n(n) {
        a = vector<vector<type> >(n, vector<type>(n, 0));
        for (int i = 0; i < n; ++i)
            a[i][i] = dig;
    }

    vector<type>&operator[](const int m){
        return a[m];
    }

    mat operator * (mat &b) const {
        mat<type> res(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    res[i][j] += a[i][k] * b[k][j] % mod, res[i][j] %= mod;
        return res;
    }

    void operator *= (mat &b) {
        *this = (*this) * b;
    }

    void operator ^= (long long t) {
        *this = *this ^ t;
    }
    mat operator^(long long t) const {
        mat<type> res(n);
        for(int i = 0; i < n; ++i)
            res[i][i] = 1;
        auto a = *this;
        for(; t; t >>= 1, a = a * a)
            if (t & 1)
                res = res * a;
        return res;
    }
};
