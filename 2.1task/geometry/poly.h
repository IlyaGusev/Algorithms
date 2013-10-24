#ifndef POLY_H_INCLUDED
#define POLY_H_INCLUDED
#include "geometry.h"
using std::cin;
using std::pair;
using std::sort;
static double MAX_PRECISION=0.00000000001;

class Poly : public vector<Point>{
private:
    int trace(const Point &, const Point &, const Point &);
public:
    Poly();
    Poly(unsigned int);
    Poly(vector<Point> const&, const char*);

    bool isConvex();
    double getArea();

    friend std::istream& operator>>(std::istream&, Poly & a);
    friend std::ostream& operator<<(std::ostream&, Poly & a);

    int containsPoint(const Point &);
    vector<Segment> intersectSegment(Segment const&);
};
Poly::Poly(unsigned int n) : vector<Point>(n){}
Poly::Poly():vector<Point>(){}

typedef pair<Point, double> Pair_t;
struct pair_comp{
    bool operator()(Pair_t const& left, Pair_t const& right){
        return left.second<right.second;
    }
};
Poly::Poly(vector<Point> const& pv, char const* flag=char()) : vector<Point>(pv){
    if (flag=="ConvexHull"){
        if (!pv.empty()){
            vector<Point> res;
            vector< Pair_t > sorted(pv.size()-1);
            Point p0;
            p0=pv[0];
            for (int i=1; i<pv.size(); i++)
                if (pv[i].y()<p0.y() || (pv[i].y()==p0.y() && pv[i].x()<p0.x()))
                    p0=pv[i];
            int j=0;
            for (int i=0; i<pv.size(); i++)
                if (p0!=pv[i]){
                    sorted[j]=Pair_t(pv[i], getCos(Vector(p0,pv[i]), Vector(1,0)));
                    j++;
                }

            sort(sorted.begin(), sorted.end(), pair_comp());

            double max_length=Vector(p0, sorted.back().first).length();
            vector<Point> unique;
            Point current_point=sorted.back().first;
            for (int i=sorted.size()-2; i>=0; i--){
                if ((sorted[i+1].second-sorted[i].second)<MAX_PRECISION){
                    if (Vector(p0, sorted[i].first).length()>max_length){
                        max_length=Vector(p0, sorted[i].first).length();
                        current_point=sorted[i].first;
                    }
                }
                else{
                    unique.push_back(current_point);
                    current_point=sorted[i].first;
                    max_length=Vector(p0, sorted[i].first).length();
                }
            }
            unique.push_back(current_point);

            res.push_back(p0);
            res.push_back(unique.front());
            for (int i=1; i<unique.size(); i++){
                while (!isLeftOrientation(Vector(*(res.end()-2), res.back()), Vector(res.back(), unique[i])))
                    res.pop_back();
                res.push_back(unique[i]);
            }
            (*this)=res;
        }
    }
}
std::istream& operator>>(std::istream& s, Poly & a){
    int i=0;
    if (a.size()!=0){
        cout<<"Type coordinates of points:"<<endl;
        while(i!=a.size())
        {
            double __x, __y;
            s>>__x>>__y;
            if (i!=0)
                if (__x!=a[i-1].x() || __y!=a[i-1].y()){
                    a[i].x(__x);
                    a[i].y(__y);
                    i++;
                }
                else {
                    cout<<"Point repeating. Try again."<<endl;
                    continue;
                }
            else {
                a[i].x(__x);
                a[i].y(__y);
                ++i;
            }
        }
    }
    return s;
}
std::ostream& operator<<(std::ostream& s, Poly & a){
    for (int i=0; i<a.size(); i++)
        s<<a[i]<<endl;
    return s;
}
bool Poly::isConvex(){
    bool convex;
    if (size()>=3){
        convex=true;
        Vector v1=Vector((*this)[size()-1], (*this)[0]);
        Vector v2=Vector((*this)[0], (*this)[1]);
        double temp=getCrossProduct(v1, v2).z();
        bool sign;
        if (temp>=0) sign=1; else sign=0;
        int i=1;
        while(convex && i<size()-1){
            v1=Vector((*this)[i-1], (*this)[i]);
            v2=Vector((*this)[i], (*this)[i+1]);
            temp=getCrossProduct(v1, v2).z();
            if (temp>=0 && sign==0)
                convex=false;
            if (temp<0 && sign==1)
                convex=false;
            if (convex==true)
                ++i;
        }
    }
    else
        convex=true;
    return convex;
}
double Poly::getArea(){
    double area=0;
    double s=0;
    for (int i=0; i<size(); i++){
        if (i==0){
            s=(*this)[i].x()*((*this)[size()-1].y()-(*this)[i+1].y());
            area+=s;
        }
        else
            if (i==size()-1){
                s=(*this)[i].x()*((*this)[i-1].y()-(*this)[0].y());
                area+=s;
            }
            else {
                s=(*this)[i].x()*((*this)[i-1].y()-(*this)[i+1].y());
                area+=s;
            }
    }
    if (area>=0)
        return area/2;
    else
        return (-area/2);
}
vector<Segment> Poly::intersectSegment(Segment const& seg1){
    Segment seg2;
    vector<Segment> res;
    int res_cnt=0;
    for (int i=0; i<(*this).size(); i++){
        if (i==size()-1){
            Point f=(*this)[(*this).size()-1];
            Point s=(*this)[0];
            seg2[0]=f;
            seg2[1]=s;
        }
        else {
            Point f=(*this)[i];
            Point s=(*this)[i+1];
            seg2[0]=f;
            seg2[1]=s;
        }
        if (segment_intersect(seg1,seg2).size()!=0){
            res.resize(res.size()+1);
            res[res.size()-1]=segment_intersect(seg1,seg2);
        }
    }
    return res;
}

int Poly::trace(const Point & a, const Point & b, const Point & cp){
    double ax=a.x()-cp.x();
    double ay=a.y()-cp.y();
    double bx=b.x()-cp.x();
    double by=b.y()-cp.y();
    if (ay*by>0)
        return 1;
    int s;
    double temp=ax*by-ay*bx;
    if (temp>0)
        s=1;
    if (temp==0)
        s=0; //double
    if (temp<0)
        s=-1;
    if (s==0){
        if (ax*bx<=0)
            return 0;
        return 1;
    }
    if (ay<0)
        return -s;
    if (by<0)
        return s;
    return 1;
}

int Poly::containsPoint(const Point & cp){
    int res=1;
    for (int i=0; i<(*this).size(); i++)
        if (i+1!=(*this).size())
            res*=trace((*this)[i], (*this)[i+1], cp);
        else
            res*=trace((*this)[i], (*this)[0], cp);
    return res;
}


#endif // POLY_H_INCLUDED
