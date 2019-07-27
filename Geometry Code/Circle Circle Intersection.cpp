#include <bits/stdc++.h>
using namespace std;
#define xx first
#define yy second
typedef pair<double,double> point;
double dis(point p,point q)
{
    return sqrt((p.xx-q.xx)*(p.xx-q.xx)+(p.yy-q.yy)*(p.yy-q.yy));
}
double twoCricleIntersectionArea(double r,double R,double d)//d is the distance between two center
{
    if(R < r)swap(R,r);
    if(d>R+r)return 0;//Outside
    if(d + r <= R)return acos(-1.0)*r*r;//inside
    return 	r*r*acos((d*d + r*r - R*R)/(2*d*r))+
            R*R*acos((d*d + R*R - r*r)/(2*d*R))+
            0.5*sqrt((-d+r+R)*(d+r-R)*(d-r+R)*(d+r+R));
}
pair<point,point> circleCircleIntersectionPoint(point p, double r, point q, double s)//input 2 circle cener and redius
{
    if(s>r)
        swap(r,s),swap(p,q);
    double m=dis(p,q);///assert(m+eps < r+s and m+s > r);
    double n=(r*r-s*s+m*m)/(2.0*m);
    double h=sqrt(r*r-n*n);
    point t,u,v;
    t.xx=p.xx+(n*(q.xx-p.xx))/m;
    t.yy=p.yy+(n*(q.yy-p.yy))/m;
    u.xx=t.xx+(h*(q.yy-p.yy))/m;
    u.yy=t.yy-(h*(q.xx-p.xx))/m;
    v.xx=t.xx-(h*(q.yy-p.yy))/m;
    v.yy=t.yy+(h*(q.xx-p.xx))/m;
    return {u,v};
}
