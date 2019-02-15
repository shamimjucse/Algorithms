#include<bits/stdc++.h>
#define ll long long
#define PI 3.14159265358979323846
const double pi=2.00*acos(0.00);
using namespace std;
struct Point
{
    double x,y;
    bool operator<(const Point &p)const
    {
        return x<p.x||(x==p.x&&y<p.y);
    }
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
    return acos(((B.x-A.x)*(C.x-A.x)+(B.y-A.y)*(C.y-A.y))
                /sqrt(((B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y))
                      *((C.x-A.x)*(C.x-A.x)+(C.y-A.y)*(C.y-A.y))))*180.00/pi;
}
double cos_angle(Point A, Point B, Point C)
{
    double x,y,z;
    x=Distance2(A, B);
    y=Distance2(A, C);
    z=Distance2(B, C);
    return acos((x+y-z)/(2.00*sqrt(x*y)))*180.00/pi;
}
void Made_convex(ll n)
{
    ll i,j=0,k;
    for(i=0;i<n;i++)
    {
        while(j>=2 && Triangle_area(cvx[j-2],cvx[j-1],P[i])<=0) j--;
        cvx[j++]=P[i];
    }
    for(i=n-2,k=j+1;i>=0;i--)
    {
        while(j>=k && Triangle_area(cvx[j-2],cvx[j-1],P[i])<=0) j--;
        cvx[j++]=P[i];
    }
    cvx_no=j-1;
}
int main()
{
    ll n,i,j,p,tc,t=1;
    cin >> tc;
    while(tc--)
    {
        scanf("%lld",&n);
        for(i=0; i<n; i++)
        {
            cin >> P[i].x >> P[i].y;
        }
        sort(P,P+n);
        Made_convex(n);
        if(cvx_no<3)
        {
            cout << "Case " << t++ << ": 0" << endl;
            continue;
        }
        ///point are 0 to cvx_no-1
        double d=vec_angle(cvx[0],cvx[cvx_no-1],cvx[1]);
        for(i=1;i<cvx_no;i++)
        {
            double d2 = vec_angle(cvx[i],cvx[i-1],cvx[i+1]);
            if(d2<d)d=d2;
        }
        cout << "Case " << t++ << ": " << fixed << setprecision(6) << (d) << endl;
    }
    return 0;
}
