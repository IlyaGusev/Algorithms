#include "geometry.h"
using std::cout;
using std::endl;
class Point{
private:
    double _x,_y;
public:
    Point();
    Point(double, double);
    Point(Point const&);

    void x(double);
    void y(double);
    double x() const;
    double y() const;

    void operator= (Point);
    bool operator==(const Point & __p) const;
    bool operator!=(const Point & __p) const{ return !((*this)==__p); }

    friend std::ostream& operator<<(std::ostream&, const Point &);
    friend std::istream& operator>>(std::istream&, Point &);
};

Point::Point(): _x(0), _y(0) {};
Point::Point(double __x, double __y): _x(__x), _y(__y) {};
Point::Point(Point const & copy): _x(copy._x), _y(copy._y) {};
void Point::x(double __x){ _x=__x; }
void Point::y(double __y){ _y=__y; }
double Point::x() const{ return _x; }
double Point::y() const{ return _y; }
void Point::operator= (Point right){
    _x=right._x;
    _y=right._y;
}
bool Point::operator==(const Point & __p) const{ return (__p.x()==_x && __p.y()==_y); }
std::ostream& operator<< (std::ostream& s, const Point& out){
    s<<"("<<out._x<<", "<<out._y<<")";
    return s;
}
std::istream& operator>> (std::istream& s, Point& in){
    s>>in._x>>in._y;
    return s;
}
