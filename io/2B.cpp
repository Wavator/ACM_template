inline char gc() {
    static char buf[1<<20], *head = buf, *tail = buf;
    return (head == tail && (tail = (head = buf) + fread_unlocked(buf, 1, 1 << 20, stdin), head == tail)? -1: *head++);
}
template <typename T> inline bool read(T &x) {
    static bool f;
    static char c;
    for (c = gc(), f = false; !isdigit(c); c = gc()) {
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
    static bool f;
    for(f = false; (c = gc()) != '-' && !isdigit(c);)
        if (c == EOF) return false;
    if (c == '-')
        x = 0, f = true;
    else
        x = c & 15;
    for (;isdigit(c = gc());)
        x = x * 10 + (c & 15);
    if (c == '.') {
        double base = 1.0;
        for (;isdigit(c = gc());)
            x += (c & 15) * (base /= 10);
    }
    if (f)
        x = -x;
    return true;
}
inline bool read(char s[]) {
    static int ptr;
    static char ch;
    for (ch = gc(), ptr = 0; ch != ' ' && ch != '\n'; ch = gc()) {
        if (ch == EOF)
            return false;
        s[ptr++] = ch;
    }
    s[ptr] = 0;
    return true;
}