template <typename T>
class KMP
{
public:
    vector<int> get_next(const T &a) {
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
    int kmp_single(const T &a, const T &b) { // a is pattern
        int n = a.size();
        vector<int> nxt = get_next(a);
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
                return i - n + 1; // in 0 base
        }
        return -1;
    }

    vector<int> kmp(const T &a, const T &b) { // a is pattern
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
                p.push_back(i - n + 1); // in 0 base
        }
        return p;
    }

    int kmp_times(const T &a, const T &b) {
        int n = a.size();
        vector<int> nxt = get_next(a);
        int match = 0;
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
                match++;
        }
        return match;
    }

    int kmp_and_del(const T &a, const T &b) {
        int n = a.size();
        vector<int> nxt = get_next(a);
        int match = 0;
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
            if(j == n) {
                match++;
                j=0;
            }
        }
        return match;
    }

};
