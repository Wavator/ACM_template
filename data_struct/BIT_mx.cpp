template<typename T>
class BITmx
{
public:
    const T INF_neg = T{};
    int n;
    vector<T> a;
    void init(unsigned n){
        a.assign(n+1,INF_neg);
    }
    BITmx(int n):n(n){init((unsigned)n);}
    void add(int pos, const T &val) {
        for (; pos <= n; pos += pos & -pos)
            a[pos] = max(a[pos], val);
    }
    T query(int pos) {
        T res=INF_neg;
        for(;pos;pos-=pos&-pos){
            res=max(res,a[pos]);
        }
        return res;
    }
};