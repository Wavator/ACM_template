#pragma optimize("-O3")
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define rep(i,a,n) for(int i=(a);i<(n);++i)
#define per(i,a,n) for(int i=(n)-1;i>=(a);--i)
#define all(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define fi first
#define se second
#ifdef Wavator
#define debug(fmt, ...) fprintf(stderr, "%s: %s = " fmt "\n", __func__, #__VA_ARGS__, __VA_ARGS__), fflush(stderr)
#else
#define debug(...) 99
#endif
typedef long long ll;
typedef double db;
typedef long double ld;
typedef vector<int> vi;
typedef pair<int, int> pii;
const ll mod = (ll)1e9+7;
ll pow_mod(ll a,ll b=mod-2){
    assert(b>=0);ll res=1;for(a%=mod;b;b>>=1,a=a*a%mod)if(b&1)res=res*a%mod;
    return res;
}

int main() {
#ifdef Wavator
    freopen("test.in","r",stdin);
#endif

    return 0;
}
