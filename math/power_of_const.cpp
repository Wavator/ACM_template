namespace const_power {
    const int block = 100000;
    ll power_head[block + 2], init_power[block + 2];
    ll val;
    void init(ll x) {
        val = x;
        init_power[0] = 1;
        for (int i = 1; i <= block; ++i)
            init_power[i] = init_power[i - 1] * val % mod;
        power_head[0] = 1;
        for (int i = 1; i <= block; ++i)
            power_head[i] = power_head[i - 1] * init_power[block] % mod;
    }
    inline ll power(ll x) {
        x %= (mod - 1);
        return power_head[x / block] * init_power[x % block] % mod;
    }
}