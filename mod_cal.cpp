typedef long long ll;
const int mod = (int)1e9 + 7;
inline int add(int a, int b) {
    a += b;
    return a < mod? a: a - mod;
}
inline int sub(int a, int b) {
    a -= b;
    return a < 0? a + mod: a;
}
inline int mul(ll a, int b) {
    a *= b;
    return a < mod? a: a - a / mod * mod;
}
inline int pow_mod(int a, ll b) {
    int res = 1;
    for(; b; b>>=1,a=mul(a,a))if(b&1)res=mul(res,a);
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
