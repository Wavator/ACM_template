typedef double db;
const db eps=1e-9;

inline int sgn(db a) {
    if(fabs(a)<eps)
        return 0;
    return (a < 0? -1: 1);
}
class point {
public:
    db x,y;

    void scan() {
        scanf("%lf%lf", &x, &y);
    }

    point (db x = 0,db y = 0):x(x),y(y) {}

    bool operator < (const point &b) const  {//less is more left, same then more down
        return (sgn(x - b.x) == 0? sgn(y - b.y) < 0: x < b.x);
    }

    point operator * (const db &o) const {
        return point(x*o,y*o);
    }

    point operator / (const db &o) const {
        assert(o!=0);
        return point(x/o,y/o);
    }

};

class vec{
public:
    db x, y;
    vec(db x = 0, db y = 0): x(x), y(y){}
    vec(point x, point y): x(x.x - y.x), y(x.y - y.y){}

    db angle(vec &A, vec &B) {
        return acos( (A ^ B ) / A.len() / B.len());
    }


    friend db operator ^ (const vec &a, const vec &b) { // dot
        return a.x * b.x + a.y * b.y;
    }

    friend db operator * (const vec &a, const vec &b) { // cross
        return a.x * b.y - a.y * b.x;
    }
    friend vec operator - (const vec &a, const vec &b) {
        return vec(a.x-b.x,a.y-b.y);
    }

    friend vec operator + (const vec &a, const vec &b) {
        return vec(a.x + b.x, a.y + b.y);
    }

    vec neg() {
        return vec(-x,-y);
    }

    db len2() {
        return x * x + y * y;
    }

    db len() {
        return sqrt(x * x + y * y);
    }

    vec rotate(double rad) {//向量A 逆时针旋转rad度
        return vec(x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad));
    }



};

class line {
public:
    point a, b;

    db k;

    line(point a = point(), point b = point()) : a(a), b(b){}

    int where(const point &o) { // -1 left, 0 on, 1 right
        vec lhs = vec(a , o), rhs = vec(b , o);
        return sgn(lhs * rhs);
    }

};
