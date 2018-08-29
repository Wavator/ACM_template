constexpr int mod = (int)1e9 + 7;
int dim;
inline int add(int x, int y) {
    x += y;
    return x >= mod? x - mod: x;
}
inline int sub(int x, int y) {
    x -= y;
    return x < 0? x + mod: x;
}
inline int mul(long long x, int y) {
    x *= y;
    return (int)(x < mod? x: x - x / mod * mod);
}
inline int inv(int a) {
    a %= mod;
    if (a < 0) a += mod;
    int b = mod, u = 0, v = 1;
    for(;a ;) {
        int t = b / a;
        b -= t * a;swap(a, b);
        u -= t * v;swap(u, v);
    }
    if (b != 1)
        return -1;
    if (u < 0) u += mod;
    return u;
}

void orfft(vi &x, bool inverse = false) {
    for (int len = 1; len < dim; len <<= 1) {
        for (int j = 0; j < dim; j += (len << 1)) {
            for (int k = 0; k < len; ++k) {
                x[j + k + len] = inverse?
                        sub(x[j+k],x[j+k+len]):
                               add(x[j + k], x[j + k + len]);
            }
        }
    }
}

vi ormul(vi &a, vi &b) {
    vi c(dim, 0);
    orfft(a);
    orfft(b);
    for (int i = 0; i < dim; ++i) {
        c[i] = mul(a[i], b[i]);
    }
    orfft(c, true);
    return c;
}

void xorfft(vi &data, bool inverse = false) {
    for (int len = 1; len < dim; len <<= 1) {
        for (int i = 0; i < dim; i += (len << 1)) {
            for (int j = 0; j < len; j++) {
                int a = data[i + j];
                int b = data[i + j + len];
                data[i + j] = add(a, b);
                data[i + j + len] = sub(a, b);
            }
        }
    }
    if (inverse) {
        int invP = inv(dim);
        for (int &x: data) {
            x = mul(x, invP);
        }
    }
}

void andfft(vi &data, bool inverse = 0) {
    for (int len = 1; len < dim; len <<= 1) {
        for (int i = 0; i < dim; i += (len << 1)) {
            for (int j = 0; j < len; j++) {
                int a = data[i + j];
                int b = data[i + j + len];
                if (!inverse) {
                    data[i + j] = b;
                    data[i + len + j] = add(a, b);
                } else {
                    data[i + j] = sub(b, a);
                    data[i + j + len] = a;
                }
            }
        }
    }
}

vi xormul(vi &a, vi &b) {
    vi c(dim, 0);
    xorfft(a);
    xorfft(b);
    for (int i = 0; i < dim; i++) {
        c[i] = mul(a[i], b[i]);
    }
    xorfft(c, true);
    return c;
}

vi andmul(vi &a, vi &b) {
    vi c(dim, 0);
    andfft(a);
    andfft(b);
    for (int i = 0; i < dim; i++) {
        c[i] = mul(a[i], b[i]);
    }
    andfft(c, true);
    return c;
}

vi subsetmul(vi &a) {
    vi c(dim, 0);
    for (int superset = 0; superset < dim; superset++) {
        int i = superset;
        for (;; i = (i - 1) & superset) {
            c[superset] = add(c[superset], mul(a[i], a[superset ^ i]));
            if (i == 0) {
                break;
            }
        }
    }
    return c;
}
