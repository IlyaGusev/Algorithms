#ifndef GVECTOR_H_INCLUDED
#define GVECTOR_H_INCLUDED
#include "geometry.h"
class Vector{
private:
    double _x;
    double _y;
    double _z;
public:
    Vector() : _x(0), _y(0), _z(0) {}
    Vector(Point const & first, Point const & second) :
    _x(second.x()-first.x()), _y(second.y()-first.y()), _z(0) {}
    Vector(double __x, double __y) :
    _x(__x), _y(__y), _z(0) {}

    double length() const{ return sqrt(_x*_x + _y*_y + _z*_z); }
    double x() const{ return _x; }
    double y() const{ return _y; }
    double z() const{ return _z; }

    friend double getDotProduct(Vector const &, Vector const &);
    friend double getCos(Vector const &, Vector const &);
    friend Vector getCrossProduct(Vector const &, Vector const &);
    friend double getTriangleSquare(Vector const &, Vector const &);
    friend bool isLeftOrientation(Vector const &, Vector const &);
    friend bool isRightOrientation(Vector const &, Vector const &);
    friend bool isCollinear(Vector const &, Vector const &);

};
double getDotProduct(Vector const & first, Vector const & second){
    return first._x*second._x + first._y*second._y + first._z*second._z;
}
double getCos(Vector const & first, Vector const & second){
    return getDotProduct(first, second)/(first.length()*second.length());
}
double getSin (Vector const & first, Vector const & second){
    return getCrossProduct(first, second).length()/(first.length()*second.length());
}
Vector getCrossProduct(Vector const & first, Vector const & second){
    Vector res;
    res._x=first._y*second._z - first._z*second._y;
    res._y=first._x*second._z - first._z*second._x;
    res._z=first._x*second._y - first._y*second._x;
    return res;
}
bool isLeftOrientation(Vector const & first, Vector const & second){
    if (getCrossProduct(first, second)._z>0)
        return 1;
    else return 0;
}
bool isRightOrientation(Vector const & first, Vector const & second){
    if (getCrossProduct(first, second)._z<0)
        return 1;
    else return 0;
}
bool isCollinear(Vector const & first, Vector const & second){
    if (getCrossProduct(first, second)._z==0)
        return 1;
    else return 0;
}
double getTriangleSquare(Vector const & first, Vector const & second){
    return (getCrossProduct(first, second).length()/2);
}
#endif // GVECTOR_H_INCLUDED
