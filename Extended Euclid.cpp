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
