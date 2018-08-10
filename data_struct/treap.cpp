template <size_t N>
struct treap {
    static const int INF = 0x3f3f3f3f;
    int root,treapcnt,key[N],priority[N],childs[N][2],cnt[N],size[N];
    treap()
    {
        root=0;
        treapcnt=1;
        priority[0]=INF;
        size[0]=0;
    }


    void update(int x)
    {
        size[x]=size[childs[x][0]]+cnt[x]+size[childs[x][1]];
    }

    void rotate(int &x,int t)
    {
        int y=childs[x][t];
        childs[x][t]=childs[y][1-t];
        childs[y][1-t]=x;
        update(x);
        update(y);
        x=y;
    }

    void _insert(int &x,int k)
    {
        if(x)
        {
            if(key[x]==k)
            {
                cnt[x]++;
            }
            else
            {
                int t=key[x]<k;
                _insert(childs[x][t],k);
                if(priority[childs[x][t]]<priority[x])
                {
                    rotate(x,t);
                }
            }
        }
        else
        {
            x=treapcnt++;
            key[x]=k;
            cnt[x]=1;
            priority[x]=rand();
            childs[x][0]=childs[x][1]=0;
        }
        update(x);
    }

    void _erase(int &x,int k)
    {
        if(key[x]==k)
        {
            if(cnt[x]>1)
            {
                cnt[x]--;
            }
            else
            {
                if(childs[x][0]==0&&childs[x][1]==0)
                {
                    x=0;
                    return;
                }
                int t=priority[childs[x][0]]>priority[childs[x][1]];
                rotate(x,t);
                _erase(x,k);
            }
        }
        else
        {
            _erase(childs[x][key[x]<k],k);
        }
        update(x);
    }

    int _getKth(int &x,int k)
    {
        if(k<=size[childs[x][0]])
        {
            return _getKth(childs[x][0],k);
        }
        k-=size[childs[x][0]]+cnt[x];
        if(k<=0)
        {
            return key[x];
        }
        return _getKth(childs[x][1],k);
    }

    void insert(int k)
    {
        _insert(root,k);
    }

    void erase(int k)
    {
        _erase(root,k);
    }

    int getKth(int k)
    {
        return _getKth(root,k);
    }
};
