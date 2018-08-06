template <typename T>
inline T gcd(T a, T b) {
    if(!a || !b)
        return a + b;
    T c = 1;
    for (;a - b;) {
        if (a & 1) {
            if (b & 1) {
                if (a > b)
                    a = (a - b) >> 1;
                else
                    b = (b - a) >> 1;
            }
            else
                b >>= 1;
        }else {
            if (b & 1)
                a >>= 1;
            else{
                c <<= 1;
                a >>= 1;
                b >>= 1;
            }
        }
    }
    return a * c;
}
