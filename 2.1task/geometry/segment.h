#ifndef SEGMENT_H_INCLUDED
#define SEGMENT_H_INCLUDED
#include "geometry.h"
using std::pair;
using my::vector;
class Segment : public vector<Point>{
public:
    Segment();
    Segment(int);
    Segment(Point&, Point&);
    Segment(double, double, double, double);

    double getK() const;
    double getM() const;
    double getLength() const;

    friend std::ostream& operator<<(std::ostream&, Segment);

    operator Point() const;

    Segment getCrossPoint (double __x) const;
    friend Segment segment_intersect(Segment const&, Segment const&);

    bool operator>(const Segment& rhs){

    }
};

Segment::Segment() : vector<Point>(2){}
Segment::Segment(Point& f, Point& s) : vector<Point>(){
    push_back(f);
    push_back(s);
}
Segment::Segment(double x1, double y1, double x2, double y2) : vector<Point>(){
    Point f(x1,y1);
    Point s(x2,y2);
    push_back(f);
    push_back(s);
}
Segment::Segment(int i) : vector<Point>(2){
    if (i==0){
        (*this).resize(0);
        (*this).shrink_to_fit();
    }
}
double Segment::getK() const{ return ((*this)[0].y()-(*this)[1].y())/((*this)[0].x()-(*this)[1].x()); }
double Segment::getM() const{ return ((*this)[0].y()-getK()*(*this)[0].x()); }
double Segment::getLength() const { return sqrt((*this)[0].x()*(*this)[1].x()+((*this)[0].y()*(*this)[1].y())); }
Segment::operator Point() const{ return (*this)[0]; }

Segment Segment::getCrossPoint (double __x) const{
    vector<Point> pv(1);
    pv[0].x(__x);
    pv[0].y((*this).getK()*__x+(*this).getM());
    Segment seg_res;
    seg_res[0]=pv[0];
    seg_res[1]=pv[0];
    return seg_res;
}
Segment getNullSegment(){
    Segment seg_res=Segment(0);
    return seg_res;
}
Segment segment_intersect(Segment const& seg1, Segment const& seg2){
    if (seg1.getK()==seg2.getK()){
        if(seg1.getM()==seg2.getM()){
            double tempxl;
            double tempxr;
            if (seg1[0].x()<=seg1[1].x()){
                tempxl=seg1[0].x();
                tempxr=seg1[1].x();
            }
            else {
                tempxl=seg1[1].x();
                tempxr=seg1[0].x();
            }
            if (seg2[0].x()<=seg2[1].x()){
                if (seg2[0].x()>tempxr || seg2[1].x()<tempxl){
                    Segment seg_res=Segment(0);
                    return seg_res;
                }
                if (tempxl>seg2[0].x()) tempxl=seg2[0].x();
                if (tempxr<seg2[1].x()) tempxr=seg2[1].x();
            }
            else {
                if (seg2[1].x()>tempxr || seg2[0].x()<tempxl)
                    return getNullSegment();
                if (tempxl>seg2[1].x()) tempxl=seg2[1].x();
                if (tempxr<seg2[0].x()) tempxr=seg2[0].x();
            }
            vector<Point> pv(2);
            pv[0].x(tempxl);
            pv[1].x(tempxr);
            pv[0].y(tempxl*seg1.getK()+seg1.getM());
            pv[1].y(tempxr*seg1.getK()+seg1.getM());
            Segment seg_res;
            seg_res[0]=pv[0];
            seg_res[1]=pv[1];
            return seg_res;
        }
        else
            return getNullSegment();
    }
    else {
        double checkx;
        checkx=(seg2.getM()-seg1.getM())/(seg1.getK()-seg2.getK());
        if (seg1[0].x()<=seg1[1].x())
            if (checkx>=seg1[0].x() && checkx<=seg1[1].x()){
                if (seg2[0].x()<=seg2[1].x())
                    if (checkx>=seg2[0].x() && checkx<=seg2[1].x())
                        return seg1.getCrossPoint(checkx);
                    else
                        return getNullSegment();
                else {
                    if (checkx<=seg2[0].x() && checkx>=seg2[1].x())
                        return seg1.getCrossPoint(checkx);
                    else
                        return getNullSegment();
                }
            }
            else {
                return getNullSegment();
            }
        else {
            if (checkx<=seg1[0].x() && checkx>=seg1[1].x()){
                if (seg2[0].x()<=seg2[1].x())
                    if (checkx>=seg2[0].x() && checkx<=seg2[1].x())
                        return seg1.getCrossPoint(checkx);
                    else
                        return getNullSegment();
                else {
                    if (checkx<=seg2[0].x() && checkx>=seg2[1].x())
                        return seg1.getCrossPoint(checkx);
                    else
                        return getNullSegment();
                }
            }
            else {
                return getNullSegment();
            }
        }
    }
}
std::ostream& operator<< (std::ostream& s, Segment out){
    s<<"["<<out[0]<<" ; "<<out[1]<<"]";
    return s;
}

typedef pair<Point, Segment> Pair_type;
struct segment_comp{
    bool operator()(Pair_type const& left, Pair_type const& right){
        if (left.first.x()<right.first.x())
            return 1;
        else if (left.first.x()==right.first.x())
        {
            if (left.first==left.second[0] && right.first==right.second[1])
                return 1;
            if (left.first.y()<right.first.y())
                return 1;
        }
        return 0;
    }
};
/*bool anySegmentsIntersect(vector<Segment> s){
    RBtree<Segment> T;

    vector< Pair_type > points;
    for (int i=0; i<s.size(); i++){
        points.push_back(Pair_type(s[i][0], s[i]));
        points.push_back(Pair_type(s[i][1], s[i]));
    }
    sort(points.begin(), points.end(), segment_comp());

    for (int i=0; i<points.size(); i++){
        if (points[i].first==points[i].second[0]){
            T.insert(points[i].second);
        }
    }
}*/
#endif // SEGMENT_H_INCLUDED
