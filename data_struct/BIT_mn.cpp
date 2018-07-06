template<typename T>
class BITmn
{
public:
    const T INF = INT_MAX;
    int n;
    vector<T> a;
    void init(unsigned n){
        a.assign(n+1,INF);
    }
    BITmn(int n):n(n){init((unsigned)n);}
    void add(int pos, const T &val) {
        for (; pos <= n; pos += pos & -pos)
            a[pos] = min(a[pos], val);
    }
    T query(int pos) {
        T res=INF;
        for(;pos;pos-=pos&-pos){
            res=min(res,a[pos]);
        }
        return res;
    }
};