#include <bits/stdc++.h>
using namespace std;
template <typename A, typename B> inline ostream& operator<<(ostream&os, const pair<A, B> &v) {return os << v.first << ' ' << v.second;}
template <typename A> inline ostream& operator<<(ostream&os, const vector<A> &v){
    auto it = v.begin(); os << *it;for (++it; it != v.end(); os << ' ' << *it++); return os;
}
#ifdef Wavator
#define de(...) cerr << #__VA_ARGS__ << " =", debug(__VA_ARGS__)
#else
#define de(...) 42
#define cerr if (false) cout
#endif
void debug(){cerr<<endl;}
template <typename H, typename...T> inline void debug(H head, T... tail){
    cerr << ' ' << head;
    debug(tail...);
}
#define rep(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define per(i, a, b) for (int i = (b) - 1, i##_end_ = (a); i >= i##_end_; --i)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const db eps = 1e-9, PI = acos(-1);
const ll mod = (ll)1e9 + 7;
const int oo = 0x3f3f3f3f;
mt19937 rnd((ull)time(0));
ll pow_mod(ll a, ll b) {
    assert(b >= 0); ll res = 1;
    for (a %= mod; b; b >>= 1, a = a * a % mod) if (b & 1)res = res * a % mod;
    return res;
}
/////////////////////////////////////////////////////////////////////////
template <typename T> inline bool rd(T &x) {
    static char c;
    bool f = false;
    for (c = getchar(); !isdigit(c); c = getchar()) {
        if (c == EOF)
            return false;
        if (c == 45) {
            f = true;
        }
    }
    for (x = 0; isdigit(c); c = getchar())
        x = x * 10 + c - 48;
    if (f)
        x = -x;
    return true;
}

int main() {
    
    return 0;
}
