#include<bits/stdc++.h>
#define ll long long
#define PI 3.14159265358979323846
const double pi=2.00*acos(0.00);
using namespace std;
map<pair<double,double>,ll>mp;
struct Point
{
    double x,y;
};
Point P[100005],P0,cvx[100005];
ll cvx_no;
ll Triangle_area(Point A, Point B, Point C)
{
    double p=A.x*(B.y-C.y)+B.x*(C.y-A.y)+C.x*(A.y-B.y);
    if(p==0)return 0;
    else if(p>0) return 1;
    else return -1;
}
double Triangle_area2(Point A, Point B, Point C)
{
    double p=A.x*(B.y-C.y)+B.x*(C.y-A.y)+C.x*(A.y-B.y);
    return p;
}
double Distance(Point A, Point B)
{
    return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
double Distance2(Point A, Point B)
{
    return ((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
///angel A according to B&C. Give <BAC / < CAB
double vec_angle(Point A, Point B, Point C)
{
    return acos(((B.x-A.x)*(C.x-A.x)+(B.y-A.y)*(C.y-A.y))/sqrt(((B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y))*((C.x-A.x)*(C.x-A.x)+(C.y-A.y)*(C.y-A.y))))*180.00/pi;
}
double cos_angle(Point A, Point B, Point C)
{
    double x,y,z;
    x=Distance2(A, B);
    y=Distance2(A, C);
    z=Distance2(B, C);
    return acos((x+y-z)/(2.00*sqrt(x*y)))*180.00/pi;
}
void Extreme_point(ll n)
{
    ll p=0;
    for(ll i=1; i<n; i++)
    {
        if((P[i].y<P[p].y) || (P[i].y==P[p].y && P[i].x<P[p].x))
        {
            p=i;
        }
    }
    swap(P[0],P[p]);
    P0=P[0];
}
bool cmp(const Point &A, const Point &B)
{
    ll d=Triangle_area(P0, A, B);
    if(d<0)return false;
    if(!d && Distance(P0, A)>Distance(P0, B))return false;
    return true;
}
void Made_convex(ll n)
{
    ll i,j;
    for(i=0; i<2; i++)
    {
        cvx[i]=P[i];
    }
    j=2;
    for(i=2; i<n; i++)
    {
        while(j>=2 && Triangle_area(cvx[j-2],cvx[j-1],P[i])<=0)
        {
            j--;
        }
        cvx[j++]=P[i];
    }
    cvx_no=j-1;
}
int main()
{
    ll n,m,i,j,p;
    double x,y;
    cin >> n;
    m = 0;
    ///Maping for reduce TLE
    for(i=0; i<n; i++)
    {
        cin >> x >> y;
        mp[ {x,y}]++;
        if(mp[ {x,y}]==1)
        {
            P[m].x = x, P[m].y = y, m++;
        }
    }
    n = m;
    Extreme_point(n);
    sort(P+1,P+n,cmp);
    Made_convex(n);
    double d=0;
    for(i=0; i<=cvx_no-1; i++)
    {
        for(j=i+1; j<=cvx_no; j++)
        {
            d=max(d, Distance(cvx[i],cvx[j]));
        }
    }
    cout << fixed << setprecision(10) << (d) << endl;

    return 0;
}
