class guess_xor
{
public:
    vector<vector<int> > matrix;
    vector<int>&operator[](const int id){
        return matrix[id];
    }
    void reset(unsigned n = 0, unsigned m = 0)
    {
        matrix.assign(n, vector<int>(m, 0));
    }
    int rank(int m, int n) const
    {
        guess_xor A = *this;
        int i = 0, j = 0;
        while(i < m && j < n)
        {
            int r = i;
            for(int k = i; k < m; k++)
            {
                if (A[k][j])
                {
                    r = k;
                    break;
                }
            }
            if(A[r][j])
            {
                if(r != i)
                {
                    for (int k = 0; k <= n; k++)
                    {
                        swap(A[r][k], A[i][k]);
                    }
                }
                for(int u = i+1; u < m; u++)
                {
                    if (A[u][j])
                    {
                        for (int k = i; k <= n; k++)
                        {
                            A[u][k] ^= A[i][k];
                        }
                    }
                }
                i++;
            }
            j++;
        }
        return i;
    }

} sol;
//normal:
const int MAXZ = 64;
typedef double db;
const db eps= 1e-8;
bool gauss(db a[][MAXZ],db b[],int n) {
    for (int k = 0, i, j, s; k < n; ++k) {
        for (s = k, i = k + 1; i < n; ++i) {
            if (fabs(a[i][k]) > fabs(a[s][k])) {
                s = i;
            }
        }
        if (fabs(a[s][k]) < eps)return false;
        if (s != k) {
            swap(b[s], b[k]);
            for (i = k; i < n; ++i) {
                swap(a[s][i], a[k][i]);
            }
        }
        for (j = k + 1; j < n; ++j) {
            db t = -a[j][k] / a[k][k];
            b[j] += b[k] * t;
            for (i = k + 1; i < n; ++i) {
                a[j][i] += t * a[k][i];
            }
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        b[i] /= a[i][i];
        for (int j = 0; j < i; ++j)b[j] -= a[j][i] * b[i];
    }
    return 1;
}
