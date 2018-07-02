struct print_writer {
    static const int OUT_LEN = 1<<20;
    char obuf[OUT_LEN], *oh = obuf;
    inline void print(char c) {
        if (oh == obuf + OUT_LEN)
            fwrite(obuf, 1, OUT_LEN, stdout), oh = obuf;
        *oh++ = c;
    }
    template<class T>
    inline void print(T x) {
        static int buf[30], cnt;
        if (x == 0) {
            print('0');
        } else {
            if (x < 0) print('-'), x = -x;
            for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + 48;
            while (cnt) print((char)buf[cnt--]);
        }
    }
    ~print_writer() {
        fwrite(obuf, 1, oh - obuf, stdout);
    }
}out;
