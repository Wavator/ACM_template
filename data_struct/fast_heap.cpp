template <size_t N, typename T = int, class Compare = less<T> >
class Heap
{
public:
    T a[N];
    int size;
    void init() {
        size = 0;
    }
    void build(T * b, int sz) {
        this->size = sz;
        memcpy(a,b,sizeof(a[0])*(sz+1));
        for(sz >>= 1; sz; --sz)
            down(sz);
    }
    void shift(int x)
    {
        for(;;)
        {
            int y = x >> 1;
            if(compare(a[y], a[x]))
                break;
            swap(a[y], a[x]);
            x = y;
        }
    }
    void down(int x)
    {
        for(;;)
        {
            int ls = x << 1, rs = x << 1 | 1, rt = x;
            if(ls <= size && compare(a[ls], a[rt]))
                rt = ls;
            if(rs <= size && compare(a[rs], a[rt]))
                rt = rs;
            if (rt == x)
                break;
            swap(a[rt], a[x]);
            x = rt;
        }
    }
    void insert(int x) {
        a[++size] = x;
        shift(size);
    }
    void erase() {
        swap(a[1], a[size]);
        a[size--] = 0;
        down(1);
    }
    T top() const{
        return a[1];
    }
    Compare compare;
};
