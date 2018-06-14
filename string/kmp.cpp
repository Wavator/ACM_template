vector<int> get_next(const string &a) {
    int n = a.size();
    vector<int> nxt(n + 1, 0);
    for(int i = 1; i < n; ++i) {
        for (int j = i; j; ){
            j = nxt[j];
            if(a[j] == a[i]) {
                nxt[i + 1] = j + 1;
                break;
            }
        }
    }
    return nxt;
}

vector<int> kmp(const string &a, const string &b) { // a is pattern
    int n = a.size();
    vector<int> nxt = get_next(a);
    vector<int> p;
    int m = b.size();
    for(int i = 0,j = 0; i < m; ++i) {
        if(j < n && b[i] == a[j])
            j++;
        else {
            while(j){
                j = nxt[j];
                if(b[i] == a[j]) {
                    j++;
                    break;
                }
            }
        }
        if(j == n)
            p.push_back(i - n + 1);
    }
    return p;
}
