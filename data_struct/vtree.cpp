//虚树上包含所有关键点和关键点之间所有的lca，虚树的dfs序下(相邻两点的距离和+首尾两点距离)/2为关键点构成一棵树的最小花费
const int N = 100005;
vector<int> g[N];
namespace vtree {
    vector<int> vtree[N];
    int depth = 0, bn = 0, b[N << 1];
    int fuck[N << 1], dfn[N], dis[N], fs[N];
    
    void dfs(int u, int fa) {
        int tmp = ++depth;
        b[++bn] = tmp;
        fuck[tmp] = u;
        dfn[u] = bn;
        for (auto v:g[u]) {
            if (v == fa) continue;
            dis[v] = dis[u] + 1;
            dfs(v, u);
            b[++bn] = tmp;
        }
    }

    int st[N << 1][20];
    int Log_[N << 1];

    void st_init() {
        for (int i = 2; i < N * 2; ++i) Log_[i] = Log_[i >> 1] + 1;
        for (int i = bn; i >= 1; --i) {
            st[i][0] = b[i];
            for (int j = 1; i + (1 << j) - 1 <= bn; ++j)
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }

    inline int rmq(int l, int r) {
        int k = Log_[r - l + 1];
        return min(st[l][k], st[r - (1 << k) + 1][k]);
    }

    inline int lca(int a, int b) {
        if (a == b) return a;
        if (dfn[a] > dfn[b])
            swap(a, b);
        int k = rmq(dfn[a], dfn[b]);
        return fuck[k];
    }
//vec 为需要构建虚树的点集,构造出的虚树树根为0
//原树不包含点0
    vector<int> vec;
    void build_tree() {
        int sz = 0, k = (int) vec.size();
        sort(vec.begin(), vec.end(), [](const int x, const int y) -> bool {
            return dfn[x] < dfn[y];
        });
        fs[sz] = 0;
        vtree[0].clear();
        for (int i = 0; i < k; ++i) {
            int u = vec[i], vlca = lca(u, fs[sz]);
            vtree[u].clear();
            if (vlca == fs[sz]) fs[++sz] = u;
            else {
                while (sz >= 1 && dis[fs[sz - 1]] >= dis[vlca]) {
                    vtree[fs[sz - 1]].push_back(fs[sz]);
                    sz--;
                }
                if (fs[sz] != vlca) {
                    vtree[vlca].clear();
                    vtree[vlca].push_back(fs[sz--]);
                    fs[++sz] = vlca;
                }
                fs[++sz] = u;
            }
        }
        for (int i = 0; i < sz; ++i) vtree[fs[i]].push_back(fs[i + 1]);
        vec.clear();
    }
    
    void solve() {
        dis[1] = 1;
        dfs(1,0);
        st_init();
        build_tree();
    }
    
}
