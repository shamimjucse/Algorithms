///Light OJ - 1306
#include<bits/stdc++.h>
#define int long long
using namespace std;

int egcd(int a, int b, int &x, int &y)///return ax+by=gcd(a,b)
{
    if(a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int d = egcd(b%a, a, x1, y1);
    x = y1-(b/a)*x1;
    y = x1;
    return d;
}

bool find_any_solution(int a, int b, int c, int &x, int &y, int &g)/// any solution for ax+by=c
{
    g = egcd(abs(a),abs(b),x,y);
    if (c % g)return false;
    x*=c/g, y*=c/g;
    if(a<0)x=-x;
    if(b<0)y=-y;
    return true;
}
void shift_solution(int & x, int & y, int a, int b, int cnt)
{
    x += cnt*b;
    y -= cnt*a;
}

int find_all_solutions(int a, int b, int c, int xmin, int xmax, int ymin, int ymax)
{
    int x, y, g;
    if(a==0 && b==0)
    {
        if(c==0)return (xmax-xmin+1)*(ymax-ymin+1);
        else return 0;
    }
    if(!find_any_solution(a, b, c, x, y, g)) return 0;
    if(a==0)
    {
        if(y>=ymin && y<=ymax)return (xmax-xmin+1);
        return 0;
    }
    if(b==0)
    {
        if(x>=xmin && x<=xmax)return (ymax-ymin+1);
        else return 0;
    }

    a /= g;
    b /= g;
    int sign_a = a>0 ? +1 : -1;
    int sign_b = b>0 ? +1 : -1;

    shift_solution(x,y,a,b,(xmin-x)/b);
    if(x<xmin) shift_solution(x,y,a,b,sign_b);
    if(x>xmax) return 0;
    int lx1 = x;

    shift_solution(x,y,a,b,(xmax-x)/b);
    if(x>xmax) shift_solution(x,y,a,b,-sign_b);
    int rx1 = x;

    shift_solution(x,y,a,b,-(ymin-y)/a);
    if(y<ymin) shift_solution(x,y,a,b,-sign_a);
    if(y>ymax) return 0;
    int lx2 = x;

    shift_solution(x,y,a,b,-(ymax-y)/a);
    if(y>ymax) shift_solution(x,y,a,b,sign_a);
    int rx2 = x;

    if(lx2>rx2)swap(lx2, rx2);
    int lx = max(lx1, lx2);
    int rx = min(rx1, rx2);

    if(lx>rx) return 0;
    return (rx-lx)/abs(b)+1;
}
int32_t main()
{
    int a,b,c,xmin,xmax,ymin,ymax,tc,t=1;
    cin >> tc;
    while(tc--)
    {
        cin >> a >> b >> c >> xmin >> xmax >> ymin >> ymax;
        int ans = find_all_solutions(a,b,-c,xmin,xmax,ymin,ymax);
        cout << "Case " << t++ << ": " << ans << endl;
    }
    return 0;
}
