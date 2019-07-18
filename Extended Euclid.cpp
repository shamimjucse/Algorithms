/// UVA - 10104
#include<bits/stdc++.h>
#define ll long long
using namespace std;

template<class T> T egcd(T a, T b, T &x, T &y)///return ax+by=gcd(a,b)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    T x1, y1;
    T g = egcd(b, a%b, x1, y1);
    x = y1;
    y = x1-(a/b)*y1;
    return g;
}
template<class T> bool solution(T a, T b, T c, T &x, T &y, T &g)/// any solution for ax+by=c
{
    g = egcd(abs(a),abs(b),x,y);
    if(c%g!=0)return false;
    x*=c/g, y*=c/g;
    if(a<0)x = -x;
    if(b<0)y = -y;
    return true;
}
int main()
{
    ll a,b,x,y,g;
    while(cin >> a >> b)
    {
        g = egcd(a,b,x,y);
        cout << x << " " << y << " " << g << endl;
    }
    return 0;
}
