template <typename T>
class fenwick {
public:
    vector<T> fenw;
    int n;
    fenwick(int _n) : n(_n) {
        fenw.resize(static_cast<unsigned int>(_n));
    }
    void add(int x, const T &v) {
        for (; x < n; x |= (x + 1))
            fenw[x] += v;
    }

    T query(int x) {
        T v{};
        for (; x >= 0; x = (x & (x + 1)) - 1)
            v += fenw[x];
        return v;
    }
};
