#include<bits/stdc++.h>
#define ll long long
#define pi 3.141592653589793
#define eps 0.000001
using namespace std;

int dcmp(double x){if(fabs(x)<eps) return 0;else return x<0 ? -1 : 1;}
struct Point
{
    double x,y;
    bool operator < (const Point &a)const
    {return dcmp(x-a.x)<0 || (dcmp(x-a.x)==0 && dcmp(y-a.y)<0);}
    Point(double x=0, double y=0):x(x),y(y){}
    void read(){scanf("%lf %lf",&x,&y);}
};

typedef Point Vector;
Vector operator + (Vector a, Vector b){return Vector(a.x+b.x, a.y+b.y);}
Vector operator - (Vector a, Vector b){return Vector(a.x-b.x, a.y-b.y);}
Vector operator * (Vector a, double b){return Vector(a.x*b, a.y*b);}
Vector operator / (Vector a, double b){return Vector(a.x/b, a.y/b);}
bool operator == (Vector a, Vector b){return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;}
double Dot(Vector a, Vector b){return a.x*b.x+a.y*b.y;}
double Cross(Vector a, Vector b){return a.x*b.y-a.y*b.x;}
double Length(Vector a){return sqrt(Dot(a,a));}
Vector Rotate(Vector a, double rad)
{return Vector(a.x*cos(rad)-a.y*sin(rad), a.x*sin(rad)+a.y*cos(rad));}

///pab
double PTL(Point p, Point a, Point b)
{
    Vector v1=b-a,v2=p-a;
    return fabs(Cross(v1,v2)/Length(v1));
}

#define N 110
Point a[N],b[N],c[N<<1],v,p;
int m,n,ans;
double d,aa;

int check(Point x, Point y, Vector v)
{
    double p1,p2; int p[2]={0},pp[2]={0},t=0;
    for(int i=1;i<=n;i++)
    {
        p1=PTL(a[i],x,x+v);p2=PTL(a[i],y,y+v);
        int k = 0;
        if(dcmp(p1)==0 || dcmp(p2)==0)k=1;
        if(dcmp(p1+p2-d)==0 && !k) t++;else
        if(dcmp(p1-p2)<0)p[0]++;else pp[0]++;
    }
    for(int i=1;i<=m;i++)
    {
        p1=PTL(b[i],x,x+v);p2=PTL(b[i],y,y+v);
        int k = 0;
        if(dcmp(p1)==0 || dcmp(p2)==0)k=1;
        if(dcmp(p1+p2-d)==0 && !k) t++;else
        if(dcmp(p1-p2)<0)p[1]++;else pp[1]++;
    }
    t+=min(p[1]+pp[0], p[0]+pp[1]);
    return t;
}

int main()
{
    while(~scanf("%d %d %lf",&n,&m,&d) && n)
    {
        ans = 100000; if(d==0)d=0.0001;
        for(int i=1;i<=n;i++) a[i].read(),c[i]=a[i];
        for(int i=1;i<=m;i++) b[i].read(),c[i+n]=b[i];
        int line = 0;
        for(int i=2;i<=n+m;i++)if(dcmp(Cross(c[2]-c[1],c[i]-c[1]))==0)line++;
        if(line==n+m-1) line=1;else line = 0;
        for(int i=1;i<=n+m;i++)for(int j=i+1;j<=n+m;j++)
        {
            v=c[j]-c[i];
            if(line)v=Rotate(v,pi*0.5);
            Point t = Rotate(v,pi*0.5);
            t=t*d/Length(t);
            ans=min(ans,check(c[i],c[i]+t,v));
            ans=min(ans,check(c[i],c[i]-t,v));
        }
        printf("%d\n",ans);
    }
    return 0;
}
