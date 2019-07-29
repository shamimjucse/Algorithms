/**
 *  Author       :  Md Shamim Imtiaz
 *  Cover        :  Triangle cirle intersection , polygon circle intersection
 *  Problem Name :  Radiation from Fukushima, Light OJ - 1358, UVa 11978
 *  Algorithm    :  ALGEBRAIC sum of triangle & circle's intersection, Binary Search.
 *  Complexity   :  O(BS*n)
 */
#include<bits/stdc++.h>
#define EPS 1e-9
#define sqr(x) ((x)*(x))
using namespace std;

/**--------------------------------------------------------------**/

double pi = 2.*acos(0.);
int    dcmp(double x)   {if(fabs(x)<EPS) return 0;else return x<0 ? -1 : 1;}
double mysqrt(double x) {if(x < 0.0) return 0;return sqrt(x);}
double myasin(double x) {if(x < -1.0) return -pi/2;if(x > 1.)return pi/2;return asin(x);}
double myacos(double x) {if(x < -1.0) return -pi;if(x > 1.)return 0;return acos(x);}

/**--------------------------------------------------------------**/

struct V ///Point
{
    double x,y;
    V(){x=0.0;y=0.0;}
    V(double _x, double _y):x(_x),y(_y){}
    void read() {scanf("%lf %lf",&x,&y);}
    bool operator < (const V &a)const {return dcmp(x-a.x)<0 || (dcmp(x-a.x)==0 && dcmp(y-a.y)<0);}
};

/**--------------------------------------------------------------**/

double dot(V a, V b)    {return a.x*b.x + a.y*b.y;}
double cross(V a, V b)  {return a.x*b.y - a.y*b.x;}
double length(V a)      {return sqr(a.x)+sqr(a.y);}
double mag(V a)         {return mysqrt(length(a));}
V      norm(V a)        {double d = mag(a); a.x/=d; a.y/=d;return a;}
V      unit(V a)        {return norm(a);}
double angle(V a, V b)  {return myacos(dot(unit(a),unit(b)));}

/**--------------------------------------------------------------**/

V operator + (V a, V b)         {return V(a.x+b.x, a.y+b.y);}
V operator - (V a)              {return V (-a.x, -a.y);}
V operator - (V a, V b)         {return V(a.x-b.x, a.y-b.y);}
V operator * (V a, double b)    {return V(a.x*b, a.y*b);}
V operator * (double b, V a)    {return V(a.x*b, a.y*b);}
V operator / (V a, double b)    {return V(a.x/b, a.y/b);}
double operator * (V a,V b)     {return cross(a, b);}
bool operator == (V a, V b)     {return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;}
V Rotate(V a, double rad)       {return V(a.x*cos(rad)-a.y*sin(rad), a.x*sin(rad)+a.y*cos(rad));}

/**--------------------------------------------------------------**/

double triangleCircleCommonArea(V A, V B, double r)///Triangle represent by two vector (V A, V B), correspond to the origin
{
    double a = mag(A);
    double b = mag(B);

    ///both inside
    if(a <= r && b <= r)return 0.5*(A*B);

    /// solving vector equation: (A + (B-A)t).(A + (B-A)t) = r*r
    double c2 = length(B-A);
    double c1 = dot(A,B-A);
    double c0 = length(A) - r*r;
    double D = c1*c1 - c2*c0;

    //assert(fabs(c2) > EPS); //should be POSITIVE

    vector<double> vt; vt.clear();
    vt.push_back(0); vt.push_back(1);

    if(D >= 0.0)
    {
        double t = (-c1 - mysqrt(D)) / c2;
        if(0<=t && t<=1)vt.push_back(t);

        t = (-c1 + mysqrt(D)) / c2;
        if(0<=t && t<=1)vt.push_back(t);
    }
    sort(vt.begin(), vt.end());//sort 'vt's

    ///no intersection, both outside
    if(vt.size()==2)return 0.5*angle(A,B)*r*r;

    ///full intersection, both outside
    if(vt.size()==4)
    {
        V A1 = A + (B-A)*vt[1];
        V B1 = A + (B-A)*vt[2];
        return 0.5*angle(A1,A)*r*r + 0.5*A1*B1 + 0.5*angle(B1,B)*r*r;
    }

    ///size == 3
    ///A inside, B outside
    if(a <= r)  // A
    {
        V B1 = A + (B-A)*vt[1];
        return 0.5*A*B1 + 0.5*angle(B1,B)*r*r;
    }

    ///B inside, A outside
    if(b <= r)  // B
    {
        V A1 = A + (B-A)*vt[1];
        return 0.5*angle(A1,A)*r*r + 0.5*A1*B;
    }
    //assert(0);//should never come here!
    return 0;
}

double triangleCircleAlgebraicCommonArea(V A, V B, double r) ///positive if CCW, negative if CW (two vector defines a triangle)
{
    double fcall;
    if(A*B < 0)
    {
        fcall = triangleCircleCommonArea(B, A, r);
        //assert(fcall >= -EPS);
        return -fcall;
    }
    else
    {
        fcall = triangleCircleCommonArea(A, B, r);
        //assert(fcall >= -EPS);
        return fcall;
    }
}

double polygonCircleIntersection(vector<V> &p, V certer, double redius)
{
    if(redius < EPS) return 0;
    double ret = 0;
    int i,j,n=(int)p.size();
    for(i=0;i<n;i++)
    {
        j=(i+1)%n;
        ret += triangleCircleAlgebraicCommonArea(p[i] - certer, p[j]-certer, redius);
        /// (p[i]-center), means change the center of the polygon with circle center
    }
    return fabs(ret);
}

double polygonArea(vector<V> &p)
{
    double area = 0;
    int i, n = p.size();
    for(i=0; i<n; i++)
        area += p[i] * p[(i+1)%n];
    return fabs(area)/2.0;
}

/**--------------------------------------------------------------**/

int main()
{
    int tc,t=1;
    scanf("%d",&tc);
    while(tc--)
    {
        int n;
        scanf("%d",&n);
        vector<V>point(n);
        for(int i=0;i<n;i++)
        {
            point[i].read();
        }
        V center;
        double p;
        center.read();
        scanf("%lf",&p);
        p/=100.0;
        double area = polygonArea(point);
        double l=0.0, r=1000.0, m, test=500;
        while(test--)
        {
            m = (l+r)/2.0;
            double intersect = polygonCircleIntersection(point,center,m);
            if(intersect/area + EPS >= p)
                r = m;
            else
                l = m;
        }
        printf("Case %d: %d\n",t++,(int)(l+0.5));
    }
    return 0;
}
