typedef double db;
const db eps=1e-9;

inline int sgn(db x) {
    if(fabs(x) < eps)
        return 0;
    return x < 0? -1: 1;
}

class Point {
public:
    db x, y;
    Point (db x = 0, db y = 0) : x(x), y(y) {}

    Point(Point a, Point b) : x(a.x - b.x), y(a.y - b.y){} // end, start

    void scan() {
        scanf("%lf%lf", &x, &y);
    }
    friend ostream& operator << ( ostream& s, const Point& p )  {
        s << "x: " << p.x << " y: " << p.y;
        return s;
    }
    Point operator + (const Point &a) const {
        return Point(x + a.x, y + a.y);
    }
    Point operator - (const Point &a) const {
        return Point(x - a.x, y - a.y);
    }
    Point operator * (const db &k) const {
        return Point(x * k, y * k);
    }
    Point operator / (const db &k) const { // make it shorter
        return *this * (1. / k);
    }
    db operator % (const Point &a) const { // dot
        return x * a.x + y * a.y;
    }
    db operator * (const Point &a) const { // cross product
        return x * a.y - y * a.x;
    }
    db sqlen() {
        return *this % *this;
    }
    db len() {
        return sqrt(sqlen());
    }
    Point norm() { // get norm
        return *this / len();
    }
    Point rot() { // rotate 90 anti
        return Point(-y, x);
    }
    Point rot(db angle) { // rotate anti clockwise
        return *this * cos(angle) + rot() * sin(angle);
    }
    bool operator < (const Point &b) const  {//less is more left, same then more down
        return (sgn(x - b.x) == 0? sgn(y - b.y) < 0: x < b.x);
    }
    bool operator == (const Point &a) const {
        return !( (*this < a) || (a < *this) );
    }
    db alpha() {
        return atan2(y, x);
    }
    db dis( Point o) {
        return (*this - o).len();
    }
    db sqrdis(Point o) {
        return (*this - o).sqlen();
    }
};

class Line {
public:
    Point p[2];
    friend ostream&operator<<(ostream &os, const Line &o) {
        cerr << "start: " << o.p[0] << " end: " << o.p[1];
        return os;
    }
    void scan() {
        p[0].scan();
        p[1].scan();
        q = Point(p[0], p[1]);
    }
    Point q; // when need vector
    Line(Point a = Point(), Point b = Point()){p[0]=a;p[1]=b;}
    int where(const Point &o) { // -1 left, 0 on, 1 right
        Point lhs = Point(p[0] , o), rhs = Point(p[1] , o);
        return sgn(lhs * rhs);
    }
    Point&operator[](const int &w)const{
        return p[w];
    }
};


class Circle {
public:
    Point o;
    db r;

    friend ostream&operator<<(ostream&os,const Circle &o) {
        os << "center: " << o.o << " radius: " << r;
        return os;
    }

    Circle(Point o = Point(), db r = 0.0): o(o), r(r) {}

    void scan() {
        o.scan();
        scanf("%lf", &r);
    }
    bool operator < (const Circle &a) const {
        if (sgn(r - a.r) == 0)
            return o < a.o;
        return sgn(r - a.r) < 0;
    }
    bool operator == (const Circle &a) const {
        return !( (*this < a) || (a < *this) );
    }

    friend pair<int, pair<Point, Point> > operator & (const Circle &A, const Circle &B) { // get insert vector(s), pair first means how many point insert.
        pair< int, pair <Point, Point> > res = {};
        Point O1 = A.o;
        Point O2 = B.o;
        db R1 = A.r;
        db R2 = B.r;
        db L = (O1 - O2).len();
        if (L < fabs(R2 - R1) || L > (R1 + R2))
            return res;
        db d = 0.5 * (L + (R1 * R1 - R2 * R2) / L);
        Point H = O1 + (O2 - O1).norm() * d;
        db len = sqrt(R1 * R1 - d * d);
        Point a = (O2-O1).rot().norm()*len;
        if ((H + a) == (H - a)) {
            res.first = 1;
            res.second.second = res.second.first = H + a;
        }
        res.first = 2;
        res.second.first = H - a;
        res.second.second = H + a;
        return res;
    }

};
