const int LEN = 500005;
char a[LEN], b[LEN];


int main() {
    while (scanf("%s%s", a, b) != EOF) {
        int len1 = strlen(a), len2 = strlen(b);
        vector<int> x(len1), y(len2);
        for (int i = 0; i < len1; ++i)
            x[i] = a[len1 - i - 1] - '0';
        for (int i = 0; i < len2; ++i)
            y[i] = b[len2 - i - 1] - '0';
        auto res = fft::multiply(x,y);
        int len=res.size();
        res.push_back(0);
        int i;
        for(i = 0; i < len || res[i] >= 10; i++) {
            res[i + 1] += res[i] / 10;
            res[i] %= 10;
        }
        len = i;
        while (res[len] <= 0 && len > 0) len--;
        for (; ~len; --len)
            putchar(48 + res[len]);
        putchar(10);
    }
    return 0;
}
