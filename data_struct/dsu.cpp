template <size_t N>
class DSU {
public:
    int p[N], r[N];
    void init(int n) {
        for(int i = 0; i <= n; i++) {
            p[i] = i;
            r[i] = 0;
        }
    }
    
    int find(int x) {
        return p[x] == x? x: p[x] = find(p[x]);
    }
    
    bool unite(int x,int y) {
        x = find(x);
        y = find(y);
        if(x == y) {
            return false;
        }
        if(r[x] < r[y]) {
            p[x] = y;
        }
        else {
            p[y] = x;
            if(r[x]==r[y]) {
                r[x]++;
            }
        }
        return true;
    }
    
    bool same(int x,int y) {
        return find(x) == find(y);
    }
};
