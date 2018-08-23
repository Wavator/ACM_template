#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
vector<int> g[N],g2[N];
int depth = 0,bn = 0,b[N << 1];
int f[N << 1],dfn[N],dis[N],fs[N];
ll ans[N];

void dfs(int u,int fa) {
    int tmp = ++depth;
    b[++bn] = tmp;
    f[tmp] = u;
    dfn[u] = bn;
    for (auto v:g[u]) {
        if (v == fa) continue;
        dis[v] = dis[u] + 1;
        dfs(v,u);
        b[++bn] = tmp;
    }
}

int st[N << 1][20];
int lg[N << 1];
void st_init() {
    for (int i = 2; i < N * 2; ++i) lg[i] = lg[i >> 1] + 1;
    for (int i = bn; i >= 1; --i) {
        st[i][0] = b[i];
        for (int j = 1; i + (1 << j) - 1 <= bn; ++j)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
}
inline int rmq(int l, int r) {
    int k = lg[r - l + 1];
    return min(st[l][k], st[r - (1 << k) + 1][k]);
}

inline int lca(int a,int b) {
    if(a == b) return a;
    if (dfn[a] > dfn[b]) swap(a,b);
    int k = rmq(dfn[a],dfn[b]);
    return f[k];
}

bool cmp(const int &i, const int &j) {
    return dfn[i] < dfn[j];
}
//vec 为需要构建虚树的点集,构造出的虚树树根为0
//原树不包含点0
void build_tree(vector<int> &vec) {
    int sz = 0,k = (int)vec.size();
    sort(vec.begin(),vec.end(),cmp);
    fs[sz] = 0;
    g2[0].clear();
    for (int i = 0; i < k; ++i) {
        int u = vec[i], ll = lca(u, fs[sz]);
        g2[u].clear();
        if (ll == fs[sz]) fs[++sz] = u;
        else {
            while (sz >= 1 && dis[fs[sz - 1]] >= dis[ll]) {
                g2[fs[sz - 1]].push_back(fs[sz]);
                sz--;
            }
            if (fs[sz] != ll) {
                g2[ll].clear();
                g2[ll].push_back(fs[sz--]);
                fs[++sz] = ll;
            }
            fs[++sz] = u;
        }
    }
    for (int i = 0; i < sz; ++i) g2[fs[i]].push_back(fs[i + 1]);
}

int main() {
    dis[1] = 1;
    dfs(1,0);
    st_init();
    build_tree(vec);
    return 0;
}
