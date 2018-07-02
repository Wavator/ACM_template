#include <bits/stdc++.h>
using namespace std;
set<int> s;
inline long long count(int n = 11) {
    for(int a=0;a<=n;a++)
        for(int b=0;a+b<=n;b++)
            for(int c=0;a+b+c<=n;c++) {
                int d=n-a-b-c;
                s.insert(a+5*b+10*c+50*d);
            }
    return (long long)(s.size());
}

int main() {
    int x;
    cin >> x;
    for (int i = 1; i <= x; ++i) {
        cout << count(i) << endl;
    }
    return 0;
}