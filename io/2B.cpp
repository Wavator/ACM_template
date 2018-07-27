namespace io {
    const int LEN=(1<<21)+1; char ibuf[LEN],*iS,*iT,obuf[LEN],*oS=obuf,*oT=obuf+LEN-1,c,st[55];int f,tp;
#define gc() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,LEN,stdin),(iS==iT?EOF:*iS++)):*iS++)
    inline void flush() {fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void pc(char x) { *oS++=x; if (oS==oT) flush(); }
    template<class I> inline void sc(I&x) {
        for (f=1,c=gc();c<'0'||c>'9';c=gc()) if (c=='-') f=-1;
        for (x=0;c<='9'&&c>='0';c=gc()) x=x*10+(c&15); x*=f;
    }
    template<class T> inline bool read(T&x){
        for (f=1,c=gc();c<'0'||c>'9';c=gc()){ if(c==-1)return 0;if(c=='-') f=-1; }
        for(x=c-48;;x=x*10+(c&15)){ if(!isdigit(c=gc()))break;}x*=f; return 1;
    }
    template<class I> inline void pr(I x) {
        if (!x) pc('0');
        if (x<0) pc('-'),x=-x;
        while (x) st[++tp]=x%10+'0',x/=10;
        while (tp) pc(st[tp--]);
    }
    template <typename T> inline void pl(T x){ pr(x);pc(10); }
    inline void pl(){ pc(10); }
    inline void ps(){ pc(30); }
    template <typename T> inline void ps(T x){ pr(x);pc(30); }
    inline void gs(char*s, int&l) {
        for (c=gc();c<'a'||c>'z';c=gc()); for (l=0;c<='z'&&c>='a';c=gc()) s[l++]=c; s[l]=0;
    }
    template <typename A, typename B> inline void sc(A&x,B&y){sc(x),sc(y);};
    template <typename A, typename B> inline bool read(A&x,B&y){return read(x)&&read(y);};
    inline void ps(const char*s) { for (int i=0;s[i];++i) pc(s[i]); }
    struct IOFLUSHER{ ~IOFLUSHER() { flush(); } } _ioflusher_;
}
using io::pc;
using io::sc;
using io::gs;
using io::ps;
using io::pr;
using io::pl;
using io::ps;
using io::read;
