class AC_automata {
public:
    static const int N = 151 * 70, sigma_sz = 26;
    int ch[N][sigma_sz], val[N], f[N], last[N], sz;

    unsigned ch_sz;

    AC_automata(){ch_sz = sizeof(ch[0]);}

    void init() {
        sz = 1;
        memset(ch[0], 0, ch_sz);
        val[0]=0;
    }

    void insert(char* s, int v) {
        int n = strlen(s), u = 0;
        rep(i, 0, n) {
            int c = s[i] - 'a';
            if(!ch[u][c]) {
                ch[u][c] = sz;
                memset(ch[sz], 0, ch_sz);
                val[sz++] = 0;
            }
            u = ch[u][c];
        }
        val[u]=v;
    }

    void get_fail() {
        queue<int> q;
        last[0] = f[0]=0;
        rep(i, 0, sigma_sz) {
            int u = ch[0][i];
            if(u) {
                f[u] = last[u] = 0;
                q.push(u);
            }
        }
        for(;!q.empty(); q.pop()) {
            int r = q.front();
            rep(i, 0, sigma_sz) {
                int u = ch[r][i];
                if(u==0)continue;
                q.push(u);
                int v = f[r];
                for(;v && ch[v][i]==0; v = f[v]);
                f[u] = ch[v][i];
                last[u] =  val[f[u]]?f[u]:last[f[u]];
            }
        }
    }

    virtual void print(int i) { // give the index of vertexes which have the same suffix with i
        if(i) {
            printf("%d\n",i);
            print(last[i]);
        }
    }

    void find(char * s) {
        int n=strlen(s),j=0;
        rep(i, 0, n) {
            int id = s[i]-'a';
            for(;j && ch[j][id]==0; j=f[j]);
            j = ch[j][id];
            if(val[j]) print(j);
            else if(last[j]) print(last[j]);
        }
    }


};
