class print_writer {
public:
    template<class T>
    inline void print(T x) {
        static int a[30], cnt;
        if (x == 0) {
            pc(48);
        } else {
            if (x < 0) pc(45), x = -x;
            for (cnt = 0; x; x /= 10) a[++cnt] = x % 10 + 48;
            for(;cnt;)
                pc((char)a[cnt--]);
        }
    }
    inline void print(const char * s) {
        static int i;
        for (i = 0; s[i]; ++i) pc(s[i]);
    }
    inline void print(char c) {
        pc(c);
    }
    inline void print(const string &s) {
        for (const auto&c : s) pc(c);
    }
    template <typename T> inline void println(const T&x) {
        print(x), pc(10);
    }
    template <typename T> inline void prints(const T &x) {
        print(x), pc(' ');
    }
    inline void flush() {
        fwrite(obuf, 1, OUT_LEN, stdout), oh = obuf;
        fflush(stdout);
    }
    ~print_writer() {
        fwrite(obuf, 1, oh - obuf, stdout);
    }
private:
    static const int OUT_LEN = 1<<20;
    char obuf[OUT_LEN], *oh = obuf;
    inline void pc(char c) {
        if (oh == obuf + OUT_LEN)
            fwrite(obuf, 1, OUT_LEN, stdout), oh = obuf;
        *oh++ = c;
    }

}out;
