constexpr ll mod = (ll)1e9 + 7;
ll pow_mod(ll a, ll b) {
    ll res = 1;
    for (a %= mod; b; b >>= 1, a = a * a % mod) {
        if (b & 1) {
            res = res * a % mod;
        }
    }
    return res;
}
struct mat {
    static const int siz = 10;
    ll a[siz][siz];
    int n, m;

    mat(int _n, int _m) {
        n = _n, m = _m;
        for (int i = 0; i < n; i++)
            fill(a[i], a[i] + m, 0);
    }

    ll *operator[](const int x) {
        return a[x];
    }

    mat operator+(const mat &b) const {
        mat ret(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                ret[i][j] = a[i][j] + b.a[i][j];
                if (ret[i][j] >= mod) {
                    ret[i][j] -= mod;
                }
            }
        }
        return ret;
    }

    mat operator-(const mat&b) const {
        mat ret(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                ret[i][j] = a[i][j] - b.a[i][j];
                if (ret[i][j] < 0) {
                    ret[i][j] += mod;
                }
            }
        }
        return ret;
    }
    
    mat operator*(const mat &b) const {
        mat ret(n, b.m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < b.m; j++)
                for (int k = 0; k < m; k++) {
                    ll t = (ll) a[i][k] * b.a[k][j];
                    if (t >= mod)
                        t %= mod;
                    ret[i][j] += t;
                    if (ret[i][j] >= mod)
                        ret[i][j] -= mod;
                }
        return ret;
    }

    mat operator^(long long k) const {
        mat ret(n, m), b = *this;
        for (int i = 0; i < n; ++i)ret[i][i] = 1;
        for (; k; k >>= 1, b = b * b) {
            if (k & 1)
                ret = ret * b;
        }
        return ret;
    }

    ll delta() const {
        ll res = 1;
        for (ll i = 0; i < n; i++) {
            for (ll j = i; j < n; j++)
                if (a[j][i] != 0) {
                    for (ll k = i; k < n; k++)
                        swap(a[i][k], a[j][k]);
                    if (i != j)
                        res = (-res + mod) % mod;
                    break;
                }
            if (a[i][i] == 0) {
                res = 0;//不存在
                break;
            }
            for (ll j = i + 1; j < n; j++) {
                ll mut = (a[j][i] * pow_mod(a[i][i], mod - 2)) % mod;
                for (ll k = i; k < n; k++)
                    a[j][k] = (a[j][k] - (a[i][k] * mut) % mod + mod) % mod;
            }
            res = (res * a[i][i]) % mod;
        }
        return res;
    }

    void get_matrix_tree(int n, int g[siz][siz]) {
        *this = mat(n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][i] += g[i][j];
                a[i][j] -= g[i][j];
            }
        }
    }

};
mat Strassen(mat A, mat B) {
    if (A.n == 1) return A * B;
    mat C(A.n, B.m);
    int mid = A.n >> 1;
    mat A11(mid, mid);
    mat A12(mid, mid);
    mat A21(mid, mid);
    mat A22(mid, mid);
    mat B11(mid, mid);
    mat B12(mid, mid);
    mat B21(mid, mid);
    mat B22(mid, mid);
    mat P1(mid, mid);
    mat P2(mid, mid);
    mat P3(mid, mid);
    mat P4(mid, mid);
    mat P5(mid, mid);
    mat P6(mid, mid);
    mat P7(mid, mid);
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            A11[i][j] = A[i][j];
            B11[i][j] = B[i][j];
        }
    }
    for (int i = mid; i < A.n; i++) {
        for (int j = 0; j < mid; j++) {
            A12[i - mid][j] = A[i][j];
            B12[i - mid][j] = B[i][j];
        }
    }
    for (int i = 0; i < mid; i++) {
        for (int j = mid; j < A.n; j++) {
            A21[i][j - mid] = A[i][j];
            B21[i][j - mid] = B[i][j];
        }
    }
    for (int i = mid; i < A.n; i++) {
        for (int j = mid; j < A.n; j++) {
            A22[i - mid][j - mid] = A[i][j];
            B22[i - mid][j - mid] = B[i][j];
        }
    }
    P1 = Strassen(A11, B12 - B22);
    P2 = Strassen(A11 + A12, B22);
    P3 = Strassen(A21 + A22, B11);
    P4 = Strassen(A22, B21 - B11);
    P5 = Strassen(A11 + A22, B11 + B22);
    P6 = Strassen(A12 - A22, B21 + B22);
    P7 = Strassen(A11 - A21, B11 + B12);
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
        }
    }
    for (int i = mid; i < A.n; i++) {
        for (int j = 0; j < mid; j++) {
            C[i][j] = P1[i - mid][j] + P2[i - mid][j];
        }
    }
    for (int i = 0; i < mid; i++) {
        for (int j = mid; j < A.n; j++) {
            C[i][j] = P3[i][j - mid] + P4[i][j - mid];
        }
    }
    for (int i = mid; i < A.n; i++) {
        for (int j = mid; j < A.n; j++) {
            C[i][j] = P1[i - mid][j - mid] + P5[i - mid][j - mid] - P3[i - mid][j - mid] - P7[i - mid][j - mid];
        }
    }
    return C;
}
