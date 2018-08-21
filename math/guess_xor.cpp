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
