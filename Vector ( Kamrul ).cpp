/**  ~*BISMILLAHIR RAHMANIR RAHIM*~  **/
///vector template;

#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1);
const double EPS = 1e-10;

struct vctr
{
  double x, y;
  vctr() { x = y = 0.0; }
  vctr( double _x, double _y ) : x(_x), y(_y) { }
};

vctr operator + ( const vctr& a, const vctr& b )    { return vctr(a.x+b.x, a.y+b.y); }
vctr operator - ( const vctr& a, const vctr& b )    { return vctr(a.x-b.x, a.y-b.y); }
vctr operator * ( const vctr& a, double s )         { return vctr(a.x*s, a.y*s); }
vctr operator * ( double s, const vctr& a )         { return vctr(a.x*s, a.y*s); }
vctr operator / ( const vctr& a, double s )         { return vctr(a.x/s, a.y/s); }
vctr operator / ( double s, const vctr& a )         { return vctr(a.x/s, a.y/s); }

double dotp( vctr a, vctr b )       { return a.x*b.x + a.y*b.y; }
double crossp( vctr a, vctr b )     { return a.x*b.y - a.y*b.x; }
vctr unit_vector( vctr a )          { return a/sqrt(dotp(a, a)); }
double angle_in( vctr a, vctr b )   { return acos( dotp(a, b)/sqrt(dotp(a, a)*dotp(b, b)) ); }
vctr rotate_cw90( vctr a )          { return vctr(a.y, -a.x); }
vctr rotate_ccw90( vctr a )         { return vctr(-a.y, a.x); }

vctr rotate_ccw( vctr a, double theta )
{
  return vctr( a.x*cos(theta)-a.y*sin(theta), a.x*sin(theta)+a.y*cos(theta) );
}
vctr intersectPoint( vctr a, vctr b, vctr c, vctr d )
{
  b = b-a, d = d-c, c = c-a;
  assert( dotp(b, b)>EPS && dotp(d, d)>EPS );
  return a + b*crossp(c, d)/crossp(b, d);
}

int main()
{
  ios_base :: sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
  return 0;
}
