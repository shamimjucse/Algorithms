/**
 * UVa   : 12307
 * Cover : Smallest Enclosing Rectangle, Convex Hull
 * Author: Md. Shamim Imtiaz (Jahangirnagar University)
 */
#include<bits/stdc++.h>
#define EPS 1e-9
using namespace std;

const double INF = 1e30;
int    dcmp(double x)   {if(fabs(x)<EPS) return 0;else return x<0 ? -1 : 1;}

struct V ///Point
{
    double x,y;
    V(){x=0.0;y=0.0;}
    V(double _x, double _y):x(_x),y(_y){}

	V 	    operator - ()			{return V(-x,-y);}
	V 	    operator - (V a)	    {return V(x-a.x,y-a.y);}
	V 	    operator + (V a)	    {return V(x+a.x,y+a.y);}
	double 	operator * (V a)	    {return (x*a.y-y*a.x);}
	V 	    operator / (double a)	{return V(x/a,y/a);}
	bool    operator == (V b)       {return dcmp(x-b.x)==0 && dcmp(y-b.y)==0;}

	double len()    {return sqrt(x*x+y*y);}
	double dot(V a) {return x*a.x + y*a.y;}

    void read()     {scanf("%lf %lf",&x,&y);}
    bool operator < (const V &a)const {return dcmp(x-a.x)<0 || (dcmp(x-a.x)==0 && dcmp(y-a.y)<0);}
};

double dist(V a,V b){return (a-b).len();}
pair<double,double> minimamRectangleArea(vector<V>&p) //expect Vs in anti clock-wise order
{
    int n = (int)p.size();//assuming polygon has at least 3 vertex, if (n<3) handle special case
    int l = 1, r = 1, u = 1;
    double area = INF, per = INF;
    for( int i = 0; i < n; i++)
    {
        V edge = (p[(i+1)%n]-p[i]) / dist(p[(i+1)%n], p[i]);
        while(edge.dot(p[r%n]-p[i]) < edge.dot(p[(r+1)%n]-p[i]))
            r++;
        while(u < r || edge*(p[u%n]-p[i]) < edge*(p[(u+1)%n]-p[i]))
            u++;
        while(l < u || edge.dot(p[l%n]-p[i]) > edge.dot(p[(l+1)%n]-p[i]))
            l++;
        double w = edge.dot(p[r%n]-p[i]) - edge.dot(p[l%n]-p[i]);
        double h = fabs(((p[i]-p[u%n])* (p[(i+1)%n]-p[u%n])) / dist(p[i], p[(i+1)%n]));
        area = min(area, w * h);
        per = min(per, (w + h)*2);
    }
    return {area,per};//return { minimam rectangle area, rectangle perimeter }
}

double cross(V o, V a, V b) {return (a-o)*(b-o);}
vector<V> convexHull(vector<V> p)  //anti-clock wise
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
    while(cin >> n && n)
    {
        vector<V>point(n);
        for(int i=0;i<n;i++)
            point[i].read();
        point = convexHull(point);
        pair<double,double> res = minimamRectangleArea(point);
        cout<<setprecision(2)<<fixed<<res.first<<" "<<res.second<<endl;
    }
    return 0;
}
