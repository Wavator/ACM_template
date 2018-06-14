char O[1<<20],*SS=O,*TT=O;
#define gc (SS == TT && (TT = (SS = O) + fread(O, 1, 1 << 20, stdin), SS == TT)? -1: *SS++)

template <typename T> inline bool read(T &x) {
    bool f = false;
    char c;
    for (c = gc; !isdigit(c); c = gc) {
        if (c == EOF)
            return false;
        if (c == '-')
            f = true;
    }
    for (x = 0; isdigit(c); c = gc) {
        x = x * 10 + c - 48;
    }
    if (f) {
        x = -x;
    }
}

#undef gc
