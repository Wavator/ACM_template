class LCP: public SA {
public:
    int pos;
    int check(int Len) {
        int cnt = 1,flag = 0, tmp = 0;
        for(int i = 1; i <= n; i++) {
            if(h[i] >= Len) {
                cnt++;
                tmp = max(tmp,(max(sa[i - 1], sa[i])));
                if(cnt>=m) {
                    if(!flag)
                        pos = tmp;
                    else
                        pos = max(pos,tmp);
                    flag=1;
                }
            }
            else cnt=1, tmp=0;
        }
        return flag;
    }
    bool lcp(int m) {
        if (m == 1)
            return printf("%d 0\n", n), true;
        this->m = m;
        pos = 0;
        int l=1, r = n;
        while(l <= r) {
            int mid=l+r>>1;
            if(check(mid))
                l = mid+1;
            else r = mid-1;
        }
        if(l==1)
            return false;
        else
            return printf("%d %d\n",l-1,pos), true;
    }
};