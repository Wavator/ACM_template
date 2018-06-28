inline char gc() {
    static char O[1<<20], *SS = O, *TT = O;
    return (SS == TT && (TT = (SS = O) + fread(O, 1, 1 << 20, stdin), SS == TT)? -1: *SS++);
}
template <typename T> inline bool read(T &x) {
    bool f = false;
    char c;
    for (c = gc(); !isdigit(c); c = gc()) {
        if (c == EOF)
            return false;
        else if (c == 45)
            f = true;
    }
    for (x = 0; isdigit(c); c = gc())
        x = x * 10 + c - 48;
    if (f)
        x = -x;
    return true;
}
inline bool read(double &x) {
    static char c;
    for(;(c = gc()) != '-' && !isdigit(c);)
        if (c == EOF) return false;
    bool f = false;
    if (c == '-')
        x = 0, f = true;
    else
        x = c & 15;
    for (;isdigit(c = gc());)
        x = x * 10 + (c & 15);
    if (c == '.') {
        double base = 1.0;
        while (isdigit(c = gc()))
            x += (c & 15) * (base /= 10);
    }
    if (f)
        x = -x;
    return true;
}
inline bool read(char s[]) {
    int ptr = 0;
    static char ch;
    for (ch = gc(); ch != ' ' && ch != '\n'; ch = gc()) {
        if (ch == EOF)
            return false;
        s[ptr++] = ch;
    }
    s[ptr] = '\0';
    return true;
}
