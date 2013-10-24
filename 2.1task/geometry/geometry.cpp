#include "geometry.h"
int main()
{
    /*Point a(1,1);
    Point b(-1,-1);
    Point c(1,0);
    Point d(5,0);
    vector<Point> pv;
    pv.push_back(a);
    pv.push_back(b);
    pv.push_back(c);
    pv.push_back(d);
    Poly p=Poly(pv);*/

    Point p1(-2,0);
    Point p2(0,0);
    Point p3(-1,2);
    Point p4(-1,3);
    Point p5(1,-2);
    Point p6(2,0);
    Point p7(2,2);
    Point p8(2,4);
    Point p9(5,1);
    Point p10(-3,3);
    vector<Point> pv;
    pv.push_back(p1);
    pv.push_back(p2);
    pv.push_back(p3);
    pv.push_back(p4);
    pv.push_back(p5);
    pv.push_back(p6);
    pv.push_back(p7);
    pv.push_back(p8);
    pv.push_back(p9);
    pv.push_back(p10);
    Poly p=Poly(pv, "ConvexHull");
    cout<<p<<p.isConvex()<<endl;

    vector<Segment> s;
    s.push_back(Segment(p1,p2));
    s.push_back(Segment(p3,p4));
    anySegmentsIntersect(s);

   /* Point p1(0,0);
    Point p2(2,2);
    Point p3(3,0);
    Point p4(4,2);
    Point p5(6,1);
    Point p6(4,0);
    Point p7(5,-3);
    Point p8(3,-1);
    Point p9(3,-3);
    vector<Point> pv;
    pv.push_back(p1);
    pv.push_back(p2);
    pv.push_back(p3);
    pv.push_back(p4);
    pv.push_back(p5);
    pv.push_back(p6);
    pv.push_back(p7);
    pv.push_back(p8);
    pv.push_back(p9);
    Poly p=Poly(pv);*/

    /*while(1){
        Point y;
        cin>>y;
        cout<<p.containsPoint(y)<<endl;
    }*/

    /*Point p1(0,0);
    Point p2(1,1);
    Point p3(2,2);
    Point p4(3,3);
    Point p5(0,5);
    vector<Point> pv;
    pv.push_back(p1);
    pv.push_back(p2);
    pv.push_back(p3);
    pv.push_back(p4);
    pv.push_back(p5);
    Poly p=Poly(pv, "ConvexHull");
    cout<<p<<p.isConvex();*/

    /*cout<<p.isConvex()<<" "<<p.getArea()<<endl;
    Segment e(-1,0,5, 1);
    vector<Segment> f=p.intersectSegment(e);
    for (int i=0; i<f.size(); i++)
        cout<<f[i]<<endl;
    Ellipse elp(0,0,2,1);
    vector<Segment> x=elp.intersectSegment(e);
    for (int i=0; i<x.size(); i++)
        cout<<(Point)x[i]<<endl;
    cout<<elp.getArea()<<endl;*/
}
