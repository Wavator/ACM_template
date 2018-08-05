namespace Quick_in {
    const int LEN=(1<<21)+1; char ibuf[LEN],*iH,*iT;int f,c;
#define gc() (iH==iT?(iT=(iH=ibuf)+fread(ibuf,1,LEN,stdin),(iH==iT?EOF:*iH++)):*iH++)
    inline char nc(){
        while((c=gc())<=32)if(c==-1)return -1;
        return (char)c;
    }
    template<class T> inline void sc(T&x) {
        for (f=1,c=gc();c<'0'||c>'9';c=gc()) if (c=='-') f=-1;
        for (x=0;c<='9'&&c>='0';c=gc()) x=x*10+(c&15); x*=f;
    }
    template<class T> inline bool read(T&x) {
        for (f=1,c=gc();c<'0'||c>'9';c=gc()){ if(c==-1)return 0;if(c=='-') f=-1; }
        for(x=c-48;;x=x*10+(c&15)){ if(!isdigit(c=gc()))break;}x*=f; return 1;
    }
    inline int gline(char*s) {
        int l=-1;
        for (c=gc();c<=32;c=gc())if(c==-1)return c;
        for (;c>32||c==' ';c=gc()){
            s[++l]=c;
        }
        s[l+1]=0;
        return l;
    }
    inline int gs(char *s) {
        int l=-1;
        for (c=gc();c<=32;c=gc())if(c==-1)return c;
        for (;c>32;c=gc()){
            s[++l]=c;
        }
        s[l+1]=0;
        return l;
    }
    template <typename A, typename B> inline void sc(A&x,B&y){sc(x),sc(y);};
    template <typename A, typename B> inline bool read(A&x,B&y){return read(x)&&read(y);};
}
namespace Quick_out {
    static const int BUFFER_MAX_SIZE = 1<<18;
    char buf[BUFFER_MAX_SIZE], *ph = buf, *pt = buf + BUFFER_MAX_SIZE;
    char tmp[100];
    const double dx[15] = {5e-1,5e-2,5e-3,5e-4,5e-5,5e-6,5e-7,5e-8,5e-9,5e-10,5e-11,5e-12,5e-13,5e-14,5e-15};
    inline void my_flush() {
        fwrite(buf, sizeof(char), ph - buf, stdout);
        ph = buf;
    }
    inline void pc(char c) {
        *(ph++) = c;
        if (ph == pt) my_flush();
    }
    inline void ps(const char *s) {
        for (int i = 0; s[i]; ++i) pc(s[i]);
    }
    inline void ps(const string&s) {
        ps(s.c_str());
    }
    template<class T>
    inline void pi(T x, char ec = '\n') {
        if (x < 0) pc('-'), x = -x;
        int len = 0;
        if (!x) tmp[len++] = '0';
        for(;x;) tmp[len++] = x % 10 + '0', x /= 10;
        for(;len;)  pc(tmp[--len]);
        pc(ec);
    }
    inline void pd(double x, int fix = 8, char bc = '\n') {
        x += dx[fix];
        if (x < 0) pc('-'), x = -x;
        pi((long long)x, '.');
        x -= (long long)x;
        for(;fix--;) {
            x *= 10;
            pc('0' + (int)x);
            x -= (int)x;
        }
        pc(bc);
    }
    struct Quick_{~Quick_(){my_flush();}}oooOoooOO;
}
using Quick_in::sc;
using Quick_in::read;
using Quick_in::gline;
using Quick_in::gs;
using Quick_in::nc;
using Quick_out::pi;
using Quick_out::pc;
using Quick_out::ps;
using Quick_out::pd;
