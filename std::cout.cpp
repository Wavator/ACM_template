
//setbase - cout << setbase (16); cout << 100 << endl; Prints 64
//setfill -   cout << setfill ('x') << setw (5); cout << 77 << endl; prints xxx77
//setprecision - cout << setprecision (14) << f << endl; Prints x.xxxx
//cout.precision(x)  cout<<fixed<<val;  // prints x digits after decimal in val
template <typename A, typename B>
inline ostream& operator << (ostream &os, const pair<A, B> x) {
    os << x.first << ' ' << x.second;
    return os;
}

template <typename T>
inline ostream& operator << (ostream &os, const vector<T> x) {
    for (const T &o: x)
        os << o << ' ';
    return os;
}
