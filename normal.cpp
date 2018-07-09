#include <bits/stdc++.h>
using namespace std;
template <typename A, typename B>
inline ostream& operator << (ostream&os, const pair<A, B> &v) {
    return os << v.first << ' ' << v.second;
}
template <typename T>
inline ostream& operator << (ostream&os, const vector<T> &v) {
    auto it = v.begin(); os << *it; for (++it; it != v.end(); ++it) os << ' ' << *it;
    return os;
}
#ifdef Wavator
#define debug(...) cerr << #__VA_ARGS__ << " = \n[ ", _debug(__VA_ARGS__), cerr << "]" << endl;
#else
#define debug(...) 98;
#define cerr if (false) cout
#endif
void _debug(){}
template <typename H, typename...T>
void _debug(H head, T...tail) {
    cerr << head << " ";
    _debug(tail...);
}
#define rep(i, a, b) for (int (i) = (a); (i) < (b); ++(i))
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define SZ(x) ((int)(x).size())
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, pii> pip;
