struct Mat{
    int a[3][3];
    int n,m;
    Mat(int _n,int _m){
        n=_n,m=_m;
        for(int i=0;i<n;i++)
            fill(a[i],a[i]+m,0);
    }
    Mat operator+(const Mat &b)const{
        Mat tmp(n,m);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++){
                tmp.a[i][j]=add(a[i][j],b.a[i][j]);
            }
        return tmp;
    }
    
    Mat operator-(const Mat &b)const{
        Mat tmp(n,m);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++){
                tmp.a[i][j]=sub(a[i][j],b.a[i][j]);
            }
        return tmp;
    }
    
    Mat operator*(const Mat &b)const{
        Mat ret(n,b.m);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                for(int k=0;k<m;k++){
                    ret.a[i][j]=add(ret.a[i][j], mul(a[i][k], b.a[k][j]));
                }
        return ret;
    }

    Mat operator^(long long k)const{
        Mat ret(n,m),b(n,m);
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++)
                b.a[i][j]=a[i][j];
            ret.a[i][i]=1;
        }
        for(;k;k>>=1,b=b*b){
            if(k&1)
                ret=ret*b;
        }
        return ret;
    }
};
