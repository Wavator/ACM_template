class print_writer {
public:
    template<class T>
    inline void p(T x) {
        static int a[30], cnt;
        if (x==0)pc(48);
        else {
            if(x<0)pc(45),x=-x;
            for(cnt=0;x;x/=10)a[++cnt]=x%10+48;
            for(;cnt;) pc(a[cnt--]);
        }
    }
    template <typename T>inline void p(T*b, const T*e){ if(e-b>0)for (p(*b++);b!=e;b++)p(' '),p(*b);}
    inline void p(const char * s){static int i;for (i=0;s[i];++i)pc(s[i]);}
    inline void p(char c){pc(c);}
    inline void p(const string &s){for (const auto&c:s)pc(c);}
    template <typename T> inline void pl(const T&x){p(x),pc(10);}
    template <typename T> inline void ps(const T &x){p(x), pc(' ');}
    inline void flush(){fwrite(_, 1, O, stdout), oh = _;fflush(stdout);}
    inline void pc(char c){if (oh == _ + O)fwrite(_, 1, O, stdout), oh = _;*oh++ = c;}
    ~print_writer(){fwrite(_, 1, oh - _, stdout);}
    static const int O = 1<<20;
    char _[O], *oh = _;
}o;
