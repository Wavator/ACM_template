template <size_t N>
class DSU_seq {
public:
    int p[N];
    int n;
    vector<int> seq[N];

    DSU_seq(int n=0) : n(n) {
        init(n);
    }

    void init(int n) {
        for (int i = 1; i <= n; ++i) {
            seq[i] = vector<int>{p[i] = i};
        }
    }

    int find(int x) {
        return (x == p[x] ? x : (p[x] = find(p[x])));
    }

    inline bool same(int x, int y){
        return find(x) == find(y);
    }

    inline bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            p[x] = y;
            seq[y].insert(seq[y].end(), seq[x].begin(), seq[x].end());
            return true;
        }
        return false;
    }
};
