#include <bits/stdc++.h>
#define eps 1e-9
using namespace std;
#define xx first
#define yy second
typedef pair<double,double> point;
double dis(point p,point q)
{
    return sqrt((p.xx-q.xx)*(p.xx-q.xx)+(p.yy-q.yy)*(p.yy-q.yy));
}

pair<point,point> circleCircleIntersectionPoint(point p, double r, point q, double s)//input 2 circle cener and redius
{
    if(s>r)swap(r,s),swap(p,q);
    double m=dis(p,q);
    if(m+eps >= r+s || m+s <= r)return { {-1,-1}, {-1,-1} };///Special case when circle did not intersect
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
int main()
{
    point p,q;
    double r,s;
    cin >> p.xx >> p.yy >> r >> q.xx >> q.yy >> s;
    pair<point,point>pr = circleCircleIntersectionPoint(p,r,q,s);
    cout << fixed << setprecision(2) << pr.xx.xx << " " <<pr.xx.yy << endl;
    cout << fixed << setprecision(2) << pr.yy.xx << " " <<pr.yy.yy << endl;
    return 0;
}
