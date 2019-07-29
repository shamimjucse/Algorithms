/*
 * Author  : Md Shamim Imtiaz
 * Cover   : Furthest point from polygon
 * Problem : https://vjudge.net/problem/Kattis-roberthood
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const double EPS = 1e-9;

struct V //Point
{
	double x,y;
	V(){x=y=0;}
	V(double _x,double _y){x=_x,y=_y;}

	V       operator - ()	    {return V(-x,-y);}
	V       operator - (V a)	{return V(x-a.x,y-a.y);}
	V       operator + (V a)	{return V(x+a.x,y+a.y);}
	double  operator * (V a)	{return (x*a.y-y*a.x);}

	bool    operator ==(V a)	{return fabs(x-a.x)<EPS and fabs(y-a.y)<EPS;}
	double  len()               {return sqrt(x*x+y*y);}
	void    read()              {scanf("%lf %lf",&x,&y);}
	bool operator < (const V &a)const
	{return x<a.x || (x==a.x && y<a.y);}
};

double area(V a,V b,V c)    {return fabs((b-a)*(c-a));}
double dist(V a,V b)        {return (a-b).len();}

double polygonDiameter(vector<V> &p)
{
    int n=(int)p.size();
    if(n<2) return 0;
    else if(n==2) return dist(p[0],p[1]);//distance between two points
    else
    {
        int i=n-1,j=0,k=1;
        double res=0;
        while(area(p[i], p[j], p[k+1]) > area(p[i],p[j],p[k]))
            k++;
        i=0,j=k;
        while(i<=k && j<n)
        {
            res=max(dist(p[i],p[j]),res);
            while(j < n-1 and area(p[i],p[i+1],p[j+1]) > area(p[i],p[i+1],p[j]))
            {
                j++;
                res=max(dist(p[i],p[j]),res);
            }
            i++;
        }
        return res;
    }
}

double cross(V o, V a, V b) {return (a-o)*(b-o);}
vector<V> convexHull(vector<V> p)  ///anti-clock wise
{
    int n = (int)p.size();
    vector<V> ch(n+1);
    sort(p.begin(), p.end());
    int i, m = 0, t;
    for(i = 0; i < n; i++)
    {
        while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--)
    {
        while(m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    ch.resize(m-1);
    return ch;
}

int main()
{
    int n;
    cin>>n;
    vector<V>point(n);
    for(int i=0; i<n; i++)
    {
        point[i].read();
    }

    point = convexHull(point);
    double d = polygonDiameter(point);

    cout<<setprecision(8)<<fixed<<d<<endl;

}
