#ifndef ELLIPSE_H_INCLUDED
#define ELLIPSE_H_INCLUDED
class Ellipse
{
private:
    double _x, _y, _a, _b;
public:
    Ellipse();
    Ellipse(double, double, double, double);

    double x() const {return _x;}
    double y() const {return _y;}
    double a() const {return _a;}
    double b() const {return _b;}
    void x(double __x){ _x=__x; }
    void y(double __y){ _y=__y; }
    void a(double __a){ _a=__a; }
    void b(double __b){ _b=__b; }

    double getArea(){ return (M_PI*_a*_b); }

    vector<Segment> intersectSegment(Segment const&);
};
Ellipse::Ellipse() : _x(0), _y(0), _a(0), _b(0){};
Ellipse::Ellipse(double __x, double __y, double __a, double(__b)) :
_x(__x), _y(__y), _a(__a), _b(__b){};

vector<double> solve_quad_eq(double k2, double k1, double k0){
    if (k2==0){
        vector<double> dv;
        dv.push_back(-k0/k1);
        return dv;
    }
    else {
        vector<double> dv;
        dv.push_back((-k1+sqrt(k1*k1-4*k2*k0))/(2*k2));
        dv.push_back((-k1-sqrt(k1*k1-4*k2*k0))/(2*k2));
        return dv;
    }
}
vector<Segment> Ellipse::intersectSegment(Segment const& seg){
    double k2,k1,k0;
    k2=_b*_b+_a*_a*(seg.getK()*seg.getK());
    k1=2*_a*_a*seg.getK()*(seg.getM()-_y)-2*_b*_b*_x;
    k0=_b*_b*_x*_x+_a*_a*(seg.getM()-_y)*(seg.getM()-_y)-_a*_a*_b*_b;
    vector<double> x_solve=solve_quad_eq(k2,k1,k0);
    vector<Segment> res;
    double tempxl;
    double tempxr;
    if (seg[0].x()<=seg[1].x()){
        tempxl=seg[0].x();
        tempxr=seg[1].x();
    }
    else {
        tempxl=seg[1].x();
        tempxr=seg[0].x();
    }
    for (int i=0; i<x_solve.size(); i++){
        if (x_solve[i]>=tempxl && x_solve[i]<=tempxr){
            Point a(Point(x_solve[i], seg.getK()*x_solve[i]+seg.getM()));
            res.push_back(Segment(a,a));
        }
    }
    return res;
}


#endif // ELLIPSE_H_INCLUDED
