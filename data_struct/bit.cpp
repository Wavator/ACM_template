template <typename T>
class fenwick {
public:
    vector<T> fenw;
    int n;
    fenwick(int _n=0) : n(_n) {
        fenw.resize(n+1);
    }

    void init(int n) {
        this->n=n;
        fenw.clear();
        fenw.resize(n+1);
    }

    inline void add(int pos,const T&val){
        for(; pos <= n; pos += pos&-pos)
            fenw[pos] += val;
    }

    inline T query(int pos){
        T res{};
        for(; pos; pos -= pos&-pos)
            res += fenw[pos];
        return res;
    }

    inline T query(int L, int R) {
        return query(R) - query(L - 1);
    }

};
