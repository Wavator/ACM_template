namespace simpson {
    db a, b;
    inline db F(db x) {
        return sqrt(fabs(a*a-x*x))*b/a;
    }

    inline db simpson(db a, db b) {
        db c = a + (b - a) / 2.;
        return (F(a) + 4 * F(c) + F(b)) * (b - a) / 6;
    }

    inline db asr(db a, db b, db eps, db A) {
        db c = a + (b - a) / 2;
        db l = simpson(a, c), r = simpson(c, b);
        return fabs(l + r - A) <= 15 * eps ? l + r + (l + r - A) / 15. : asr(a, c, eps / 2, l) + asr(c, b, eps / 2, r);
    }

    inline db asr(db a, db b, db eps) {
        return asr(a, b, eps, simpson(a, b));
    }

    inline db cal(db l, db r)
    {
        return asr(l,r,eps);
    }

}
