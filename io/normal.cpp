template <typename T>
inline bool read(T&x) {
    static int c;
    static int f;
    for (f = 1, c = getchar(); !isdigit(c); c = getchar()) {
        if (c == -1) return false;
        if (c == 45) f = -1;
    }
    for (x = c - 48; isdigit(c = getchar()); x = (x << 1) + (x << 3) + (c ^ 48));
    return x *= f, true;
}

template <typename T>
inline void get_str(char * s, int &l) {
    static char c;
    for(l=0,c=getchar();c<'a'||c>'z';c=getchar());
    for (l=0;c<='z'&&c>='a';c=getchar()) s[l++]=c; s[l]=0;
}

template <typename T>
inline void print(T x) {
    static short arr[22];
    static int c;
    if(x==0){
        putchar('0');
        return;
    }
    if(x<0)putchar('-'),x=-x;
    for(c=0;x;x/=10)arr[c++]=x%10;
    for(;c;putchar(48+arr[--c]));

}
template <typename T>
inline void println(T x) {
    print(x);putchar(10);
}
