#include <bits/stdc++.h>
using namespace std;
template <typename A, typename B> inline ostream& operator << (ostream&os, const pair<A, B> &v) {
    return os << v.first << ' ' << v.second;
}
template <typename T> inline ostream& operator << (ostream&os, const vector<T> &v) {
    for (auto it = v.begin(); it != v.end(); os << (*it++)) if (it != v.cbegin()) os << ' ';
    return os;
}
#ifdef Wavator
#define debug(...) cerr << #__VA_ARGS__ << "[", _debug(__VA_ARGS__),
#else
#define debug(...) 98
#define cerr if (false) cout
#endif
void _debug(){}
template <typename H, typename...T>
void _debug(H head, T...tail) {
    cerr << head; sizeof...(tail)? cerr << ' ': cerr << "]" << flush; 
    _debug(tail...);
}
#define rep(i, a, b) for (int (i) = (a); (i) < (b); ++(i))
#define per(i, a, b) for (int (i) = (b) - 1; (i) >= (a); --(i))
#define REP(i, a, b) for (int (i) = (a); (i) <= (b); ++(i))
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define SZ(x) ((int)(x).size())
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int oo = 0x3f3f3f3f;
const ll mod = (ll)1e9 + 7;
