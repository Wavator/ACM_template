namespace Manacher {

    vector<int> a;

    int manacher(const string &s, int len) {
        a.resize((unsigned int)len);
        a[0]=0;
        int ans = 0, j;
        for(int i=0;i<len;) {
            while(i-a[i]>0&&s[i+a[i]+1]==s[i-a[i]-1])
                a[i]++;
            if(ans<a[i])
                ans=a[i];
            j = i+1;
            while(j<=i+a[i] && i-a[i]!=i+i-j-a[i+i-j]){
                a[j]=min(a[i+i-j],i+a[i]-j);
                j++;
            }
            a[j]=max(i+a[i]-j,0);
            i=j;
        }
        return ans;
    }

    int getMax(const char * s) {
        auto len = strlen(s);
        string str;
        str.resize(len<<1|1);
        for(int i=0;i<len;++i) {
            str[i<<1]='$';
            str[i<<1|1]=s[i];
        }
        str[len<<1]='$';
        return manacher(str,2*len+1);
    }

    int getMax(const string &s) {
        auto len = s.size();
        string str;
        str.resize(len<<1|1);
        for(int i=0;i<len;++i){
            str[i<<1]='$';
            str[i<<1|1]=s[i];
        }
        str[len<<1]='$';
        return manacher(str,len<<1|1);
    }

    vector<int> getMatch(const char * s) {
        getMax(s);
        return a;
    }

    vector<int> getMatch(const string &s) {
        getMax(s);
        return a;
    }

}
