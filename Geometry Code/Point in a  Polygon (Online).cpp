/**
 * Author    : Shamim Imtiaz (shamimjucse)
 * Algorithm : Point in a convex polygon.
 * Type      : Online Query
 * Complexity: log(n) per query
 * Input     : Convex Polygon point in counter-clock-wise order
 * Problem   : Light OJ-1196
 */

#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int mx = 100005;
struct point
{
    long long x,y;
};
point hull[mx];//0 index, base input
inline long long triArea(const point &a, const point &b, const point &c)
{
    return a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y);
}
inline bool inConvexPoly(int sz, const point &p)
{
    int lo = 1, hi = sz-1, mid;
    while(hi-lo>1)
    {
        mid = (lo+hi)>>1;
        if(triArea(hull[0], hull[mid], p) < 0) hi = mid;
        else lo = mid;
    }
    if(triArea(hull[0], hull[lo], p) < 0)return false;
    if(triArea(hull[lo], hull[hi], p) < 0)return false;
    if(triArea(hull[hi], hull[0], p) < 0)return false;
    return true;
}

int main()
{
    int tc,t=1;
    cin >> tc;
    while(tc--)
    {
        int n;
        cin >> n;
        for(int i=0;i<n;i++)
        {
            cin >> hull[i].x >> hull[i].y;
        }
        int qry;
        cin >> qry;
        cout << "Case " << t++ << ":\n";
        for(int i=1;i<=qry;i++)
        {
            point a;
            cin >> a.x >> a.y;
            if(inConvexPoly(n,a))cout << "y\n";
            else cout << "n\n";
        }
    }
    return 0;
}
