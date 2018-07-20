class PolyInter
{
public:
    void init(const std::vector<int>& v, int m = (int)1e9+7) {
        mod = m, deg = v.size(), val = buf = v;
        inv.resize(std::max(2, deg));
        inv[1] = 1;
        for (int i = 2; i < deg; ++ i) {
            inv[i] = 1LL * (mod- mod / i) * inv[mod % i] % mod;
        }
    }
    int eval(long long n) {
        long long b = 1;
        for (int i = 1; i < deg; ++ i) {
            b = b * minus(n - i + 1) % mod * inv[i] % mod;
            buf[i] = b * val[i] % mod;
        }
        b = 1;
        int result = buf[deg - 1];
        for (int i = deg - 2; i >= 0; -- i) {
            b = (mod - b) * inv[deg - 1 - i] % mod * minus(n - i - 1) % mod;
            result += buf[i] * b % mod;
            if (result >= mod) {
                result -= mod;
            }
        }
        return result;
    }

private:
    inline int minus(long long x) const {
        x %= mod;
        return x < 0 ? x + mod : x;
    }
    int mod, deg;
    std::vector<int> inv, val, buf;
};
