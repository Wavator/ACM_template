template<typename T>
class BITsum
{
public:
    int n;
    vector<T> a;
    BITsum(unsigned n = 100000):n(n){
        a.assign(n+1, {});
    }
    void init(unsigned n) {
        this->n=n;
        a.assign(n+1,{});
    }
    void add(int pos, const T &val) {
        for(;pos<=n;pos+=pos&-pos)
            a[pos]=a[pos]+val;
    }
    T query(int pos){
        T res{};
        for(;pos;pos-=pos&-pos)
            res += a[pos];
        return res;
    }
    T query(int a, int b){
        return query(b)-query(a-1);
    }
};