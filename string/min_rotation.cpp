//vector<int> res  s[i..i+res[i]-1]=s[0...res[i]-1]

vector<int> get_min_rotation(string s, int n) {
    n <<= 1;
    vector<int> res((unsigned) n);
    s += s;
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i > r) {
            l = r = i;
            while (r < n && s[r - l] == s[r]) r++;
            res[i] = r - l, r--;
        } else {
            int k = i - l;
            if (res[k] < r - i + 1) res[i] = res[k];
            else {
                l = i;
                while (r < n && s[r - l] == s[r]) r++;
                res[i] = r - l;
                r--;
            }
        }
    }
    return res;
}
