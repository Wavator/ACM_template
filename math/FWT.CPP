constexpr int mod = (int)1e9 + 7, REV = (mod + 1) >> 1;
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
void FWTxor(int a[],int n) {
    for (int d = 1; d < n; d <<= 1) {
        for (int m = d << 1, i = 0; i < n; i += m) {
            for (int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j] = add(x, y);
                a[i + j + d] = sub(x, y);
            }
        }
    }
}

void UFWTxor(int a[],int n) {
    for (int d = 1; d < n; d <<= 1) {
        for (int m = d << 1, i = 0; i < n; i += m) {
            for (int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j] = mul(add(x, y), REV);
                a[i + j + d] = mul(sub(x, y), REV);
            }
        }
    }
}

void FWTand(int a[], int n) {
    for (int d = 1; d < n; d <<= 1) {
        for (int m = d << 1, i = 0; i < n; i += m) {
            for (int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j] = add(x, y);
            }
        }
    }
}

void UFWTand(int a[], int n) {
    for (int d = 1; d < n; d <<= 1) {
        for (int m = d << 1, i = 0; i < n; i += m) {
            for (int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j] = sub(x, y);
            }
        }
    }
}

void FWTor(int a[], int n) {
    for (int d = 1; d < n; d <<= 1) {
        for (int m = d << 1, i = 0; i < n; i += m) {
            for (int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j + d] = add(x, y);
            }
        }
    }
}

void UFWTor(int a[], int n) {
    for (int d = 1; d < n; d <<= 1) {
        for (int m = d << 1, i = 0; i < n; i += m) {
            for (int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j + d] = sub(y, x);
            }
        }
    }
}

void solve(int a[],int b[],int n)
{
    FWT(a,n);
    FWT(b,n);
    for(int i=0;i<n;i++) a[i]=1LL*a[i]*b[i]%mod;
    UFWT(a,n);
}
