const int N = 1000005;
bool is_prime[N];
int prime[N];

int sieve(int n) {
    int p = 0;
    fill(is_prime + 2, is_prime + n + 1, true);
    for(int i = 2; i <= n; i++) {
        if(is_prime[i])
            prime[p++] = i;
        for(int j = 0; j < p; j++) {
            if(prime[j] * i > n)
                break;
            is_prime[prime[j] * i] = false;
            if(i % prime[j] == 0)
                break;
        }
    }
    return p;
}

int fac[100][2]; // fac[i][0], i-th prime factor, fac[i][1] p^x
int get_factors(int x) {
    int cnt = 0;
    for (int i = 0; prime[i] <= x / prime[i]; i++) {
        fac[cnt][1] = 0;
        if (x % prime[i] == 0) {
            fac[cnt][0] = prime[i];
            while (x % prime[i] == 0)
                fac[cnt][1]++, x /= prime[i];
            cnt++;
        }
    }
    if (x != 1) {
        fac[cnt][0] = x, fac[cnt++][1] = 1;
    }
    return cnt;
}

vector<int> factorize(int x)
{
    vector<int> res;
    for (int i = 0; prime[i] <= x / prime[i]; ++i) {
        if (x % prime[i] == 0) {
            for (res.push_back(prime[i]); x % prime[i] == 0; x /= prime[i]);
        }
    }
    if (x != 1) {
        res.push_back(x);
    }
    return res;
}
