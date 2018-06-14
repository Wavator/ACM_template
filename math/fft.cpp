namespace fft {
    typedef double db;

    struct cp {
        db x, y;
        cp() { x = y = 0; }
        cp(db x, db y) : x(x), y(y) {}
    };

    inline cp operator+(cp a, cp b) { return cp(a.x + b.x, a.y + b.y); }
    inline cp operator-(cp a, cp b) { return cp(a.x - b.x, a.y - b.y); }
    inline cp operator*(cp a, cp b) { return cp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
    inline cp conj(cp a) { return cp(a.x, -a.y); }

    int base = 1;
    vector<cp> roots = {{0, 0}, {1, 0}};
    vector<int> rev = {0, 1};

    const db PI = acosl(-1.0);

    void ensure_base(int nbase) {
        if (nbase <= base) {
            return;
        }
        rev.resize(static_cast<unsigned long>(1 << nbase));
        for (int i = 0; i < (1 << nbase); i++) {
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
        }
        roots.resize(static_cast<unsigned long>(1 << nbase));
        while (base < nbase) {
            db angle = 2 * PI / (1 << (base + 1));
            for (int i = 1 << (base - 1); i < (1 << base); i++) {
                roots[i << 1] = roots[i];
                db angle_i = angle * (2 * i + 1 - (1 << base));
                roots[(i << 1) + 1] = cp(cos(angle_i), sin(angle_i));
            }
            base++;
        }
    }

    void fft(vector<cp> &a, int n = -1) {
        if (n == -1) {
            n = a.size();
        }
        assert((n & (n - 1)) == 0);
        int zeros = __builtin_ctz(n);
        ensure_base(zeros);
        int shift = base - zeros;
        for (int i = 0; i < n; i++) {
            if (i < (rev[i] >> shift)) {
                swap(a[i], a[rev[i] >> shift]);
            }
        }
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    cp z = a[i + j + k] * roots[j + k];
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] = a[i + j] + z;
                }
            }
        }
    }

    vector<cp> fa, fb;

    vector<int> multiply(vector<int> &a, vector<int> &b) {
        int need = a.size() + b.size() - 1;
        int nbase = 0;
        while ((1 << nbase) < need) nbase++;
        ensure_base(nbase);
        int sz = 1 << nbase;
        if (sz > (int) fa.size())
            fa.resize(static_cast<unsigned long>(sz));
        for (int i = 0; i < sz; i++) {
            int x = (i < (int) a.size() ? a[i] : 0);
            int y = (i < (int) b.size() ? b[i] : 0);
            fa[i] = cp(x, y);
        }
        fft(fa, sz);
        cp r(0, -0.25 / sz);
        for (int i = 0; i <= (sz >> 1); i++) {
            int j = (sz - i) & (sz - 1);
            cp z = (fa[j] * fa[j] - conj(fa[i] * fa[i])) * r;
            if (i != j) {
                fa[j] = (fa[i] * fa[i] - conj(fa[j] * fa[j])) * r;
            }
            fa[i] = z;
        }
        fft(fa, sz);
        vector<int> res(static_cast<unsigned long>(need));
        for (int i = 0; i < need; i++) {
            res[i] = fa[i].x + 0.5;
        }
        return res;
    }

    vector<int> multiply_mod(vector<int> &a, vector<int> &b, int m, int eq = 0) {
        int need = a.size() + b.size() - 1;
        int nbase = 0;
        while ((1 << nbase) < need) nbase++;
        ensure_base(nbase);
        int sz = 1 << nbase;
        if (sz > (int) fa.size()) {
            fa.resize(static_cast<unsigned long>(sz));
        }
        for (int i = 0; i < (int) a.size(); i++) {
            int x = (a[i] % m + m) % m;
            fa[i] = cp(x & ((1 << 15) - 1), x >> 15);
        }
        fill(fa.begin() + a.size(), fa.begin() + sz, cp {0, 0});
        fft(fa, sz);
        if (sz > (int) fb.size()) {
            fb.resize(static_cast<unsigned long>(sz));
        }
        if (eq) {
            copy(fa.begin(), fa.begin() + sz, fb.begin());
        } else {
            for (int i = 0; i < (int) b.size(); i++) {
                int x = (b[i] % m + m) % m;
                fb[i] = cp(x & ((1 << 15) - 1), x >> 15);
            }
            fill(fb.begin() + b.size(), fb.begin() + sz, cp {0, 0});
            fft(fb, sz);
        }
        db ratio = 0.25 / sz;
        cp r2(0, -1);
        cp r3(ratio, 0);
        cp r4(0, -ratio);
        cp r5(0, 1);
        for (int i = 0; i <= (sz >> 1); i++) {
            int j = (sz - i) & (sz - 1);
            cp a1 = (fa[i] + conj(fa[j]));
            cp a2 = (fa[i] - conj(fa[j])) * r2;
            cp b1 = (fb[i] + conj(fb[j])) * r3;
            cp b2 = (fb[i] - conj(fb[j])) * r4;
            if (i != j) {
                cp c1 = (fa[j] + conj(fa[i]));
                cp c2 = (fa[j] - conj(fa[i])) * r2;
                cp d1 = (fb[j] + conj(fb[i])) * r3;
                cp d2 = (fb[j] - conj(fb[i])) * r4;
                fa[i] = c1 * d1 + c2 * d2 * r5;
                fb[i] = c1 * d2 + c2 * d1;
            }
            fa[j] = a1 * b1 + a2 * b2 * r5;
            fb[j] = a1 * b2 + a2 * b1;
        }
        fft(fa, sz);
        fft(fb, sz);
        vector<int> res(static_cast<unsigned long>(need));
        for (int i = 0; i < need; i++) {
            long long aa = fa[i].x + 0.5;
            long long bb = fb[i].x + 0.5;
            long long cc = fa[i].y + 0.5;
            res[i] = (aa + ((bb % m) << 15) + ((cc % m) << 30)) % m;
        }
        return res;
    }

    vector<int> square_mod(vector<int> &a, int m) {
        return multiply_mod(a, a, m, 1);
    }
};
