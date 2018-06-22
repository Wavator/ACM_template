#include <bits/stdc++.h>
using namespace std;
string to_string(string s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string) s);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

void my_debug() { cerr << endl; }

template <typename Head, typename... Tail>
void my_debug(Head H, Tail... T) {
    cerr << " " << to_string(H);
    my_debug(T...);
}

#ifdef Wavator
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", my_debug(__VA_ARGS__);
#else
#define debug(...) 42;
#define cerr if (false) cout
#endif

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> pii;

void R(){};

template <typename Head, typename... Tail>
void R(Head &H, Tail&...T) {
    cin >> H;
    R(T...);
}
template <class T>
inline ostream& operator << (ostream &os, const vector<T> &o) {
    auto it = o.begin();
    os << *it;
    for(++it;it!=o.end();++it)
        os << ' ' << *it;
    return os;
}

template <class A, class B> ostream& operator << (ostream& out, const pair<A, B> &a) {
    return out << a.first << ' ' << a.second;
}


void W() {cout << endl;}
template <typename T, typename...U>
void W(const T &head, const U&...tail) {
    cout << head << ' ';
    W(tail...);
}

template <typename T>
inline bool ckmax(T &x, const T &y) {
    return x < y? x = y, true: false;
}

template <typename T>
inline bool ckmin(T &x, const T &y) {
    return x > y? x = y, true: false;
}
mt19937 rnd((ull)time(0));
void solve();

int main() {
#ifdef Wavator
    freopen("test.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
#define my_sort_unique(c) (sort(c.begin(), c.end()), c.resize(distance(c.begin(), unique(c.begin(), c.end()))))
#define my_unique(a) a.resize(distance(a.begin(), unique(a.begin(), a.end())))
#define all(x) (x).begin(), (x).end()
#define pb push_back

const db eps = 1e-9, PI = acos(-1);
const ll mod = 1e9 + 7, LL_INF = 0x3f3f3f3f3f3f3f3f;
const int INT_INF = 0x3f3f3f3f;

void solve() {

    return;
}
