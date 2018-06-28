#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define per(i, a, b) for (int i = (b - 1); i >= a; --i)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define SZ(x) (int)(x).size()
typedef long long ll;
typedef double db;
typedef vector<int> vi;

const ll mod = (ll)1e9 + 7;
ll pow_mod(ll a, ll b) {
    assert(b >= 0);
    ll res = 1;
    for (a %= mod; b; b >>= 1, a = a * a % mod) {
        if (b & 1) {
            res = res * a % mod;
        }
    }
    return res;
}
namespace poly_sum { //rep/per is 0 based
    const int D = 3010;
    ll f[D], g[D], p1[D], p2[D];
    ll calcn(int d, ll* a, ll n) { // d is the term number you have, n is the number of terms you want to calculate. return the ploy's sum.
        if (n <= d)
            return a[n];
        p1[0] = p2[0] = 1;
        rep(i, 0, d + 1) {
            ll t = (n - i + mod) % mod;
            p1[i + 1] = p1[i] * t % mod;
        }
        rep(i, 0, d + 1) {
            ll t = (n - d + i + mod) % mod;
            p2[i + 1] = p2[i] * t % mod;
        }
        ll ans = 0;
        rep(i, 0, d + 1) {
            ll t = g[i] * g[d-i] % mod * p1[i] % mod * p2[d - i] % mod * a[i] % mod;
            if ((d - i) & 1) ans = (ans - t + mod) % mod;
            else ans = (ans + t) % mod;
        }
        return ans;
    }
    void init(int M) {
        f[0] = f[1] = g[0] = g[1]=1;
        rep(i, 2, M + 5) f[i] = f[i - 1] * i % mod;
        g[M + 4] = pow_mod(f[M + 4], mod - 2);
        per(i, 1, M + 4) g[i] = g[i + 1] * (i + 1) % mod;
    }
}
