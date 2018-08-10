const int mod = (int) 1e9 + 7;

inline int add(int a, int b) {
    a += b;
    return a < mod? a: a + mod;
}

inline int sub(int a, int b) {
    a -= b;
    return a < 0? a + mod: a;
}

inline int mul(int a, int b) {
#if !defined(_WIN32) || defined(_WIN64)
    long long res = (long long) a * b;
    return (int)(res >= mod? res % mod: res);
#endif
    unsigned long long x = (long long) a * b;
    unsigned xh = (unsigned) (x >> 32), xl = (unsigned) x, d, m;
    asm(
    "divl %4; \n\t"
    : "=a" (d), "=d" (m)
    : "d" (xh), "a" (xl), "r" (mod)
    );
    return m;
}

inline int pow_mod(int a, long long b) {
    int res = 1;
    for (; b; b >>=1, a = mul(a, a)) if (b & 1) {
        res = mul(res, a);
    }
    return res;
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
