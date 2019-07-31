///Convex Hull Tricks
///https://codeforces.com/problemset/problem/319/C
#include <bits/stdc++.h>
#define ll long long
using namespace std;
typedef pair<ll,ll> pll;

///min query increasing slope
///or max query decreasing slope
const int N=1e5+2;
const ll inf = 1e20;
pll stk[N];///lines will be stored here in sorted order
double inter[N];///intersection point of corresponding line
int top=-1;///top=-1 means stack is empty


double intersect(pll a,pll b)
{
    return (b.second-a.second+0.0)/(a.first-b.first);
}
void insert(pll candi)
{
    while(top>0 && intersect(stk[top-1],stk[top]) >= intersect(stk[top-1],candi))
        top--;
    stk[++top] = candi;
    inter[top] = intersect(stk[top-1],candi);
}
ll qry(ll x)
{
    int j=upper_bound(inter+1, inter+top+1, x)-inter-1;
    return stk[j].first*(x) + stk[j].second;
}
//for minimam candi = {inf,0}, for maximum candi = {-inf,0}
void ini(pll candi = {inf,0}, double base = -inf)
{
    top=0;
    stk[0]=candi;
    inter[0]=base;
    insert({0,0}); ///inserting {0,dp[0]}
}

ll a[N],b[N];
int main()
{
    int n;
    cin >> n;
    for(int i=0;i<n;i++)
        cin >> a[i];
    for(int i=0;i<n;i++)
        cin >> b[i];

    ll ans = 0;
    ini(); //Initial set up
    ///y = m * x + c, for insert send {m,c}
    for(int i=0;i<n;i++)
    {
        ans = qry(a[i]); ///query on point a[i]
        insert({b[i],ans}); ///insert {b[i],dp[i]}
    }
    cout<<ans<<endl; ///printing dp[n-1]
    return 0;
}

/**********************************************/

///Online update and online query
///everything is fine as long as you want the minimum

///https://www.spoj.com/problems/GOODG/en/
#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct line
{
    long long a, b;
    double xleft;
    bool type;
    line(long long _a, long long _b)
    {
        a = _a;
        b = _b;
        type = 0;
    }
    bool operator < (const line &other) const
    {
        if(other.type)
        {
            return xleft < other.xleft;
        }
        return a > other.a;
    }
};
double meet(line x, line y)
{
    return 1.0 * (y.b - x.b) / (x.a - y.a);
}
struct cht
{
    set < line > hull;
    cht()
    {
        hull.clear();
    }
    typedef set < line > :: iterator ite;
    bool hasleft(ite node)
    {
        return node != hull.begin();
    }
    bool hasright(ite node)
    {
        return node != prev(hull.end());
    }
    void updateborder(ite node)
    {
        if(hasright(node))
        {
            line temp = *next(node);
            hull.erase(temp);
            temp.xleft = meet(*node, temp);
            hull.insert(temp);
        }
        if(hasleft(node))
        {
            line temp = *node;
            temp.xleft = meet(*prev(node), temp);
            hull.erase(node);
            hull.insert(temp);
        }
        else
        {
            line temp = *node;
            hull.erase(node);
            temp.xleft = -1e18;
            hull.insert(temp);
        }
    }
    bool useless(line left, line middle, line right)
    {
        double x = meet(left, right);
        double y = x * middle.a + middle.b;
        double ly = left.a * x + left.b;
        return y > ly;
    }
    bool useless(ite node)
    {
        if(hasleft(node) && hasright(node))
        {
            return useless(*prev(node), *node, *next(node));
        }
        return 0;
    }
    void addline(long long a, long long b)
    {
        line temp = line(a, b);
        auto it = hull.lower_bound(temp);
        if(it != hull.end() && it -> a == a)
        {
            if(it -> b > b)
            {
                hull.erase(it);
            }
            else
            {
                return;
            }
        }
        hull.insert(temp);
        it = hull.find(temp);
        if(useless(it))
        {
            hull.erase(it);
            return;
        }
        while(hasleft(it) && useless(prev(it)))
        {
            hull.erase(prev(it));
        }
        while(hasright(it) && useless(next(it)))
        {
            hull.erase(next(it));
        }
        updateborder(it);
    }
    long long getbest(long long x)
    {
        if(hull.empty())
        {
            return 1e18;
        }
        line query(0, 0);
        query.xleft = x;
        query.type = 1;
        auto it = hull.lower_bound(query);
        it = prev(it);
        return it -> a * x + it -> b;
    }
}st;
void ini()
{
    st.addline(0,0);
}
int main()
{
    ini();
    ll n,a,d;
    cin >> n;
    ll ans = 0;
    for(int i=1;i<=n;i++)
    {
        cin >> a >> d;
        ans = max(0LL, st.getbest(i)*(-1));
        ans = ans + a + d*i;
        st.addline(d,-ans);
    }
    ans = max(0LL, st.getbest(n+1)*(-1));
    cout << ans << endl;
    return 0;
}
/**
 * f(n) = f(i) + a(i) - d(i)*(n-i)
 * f(n) = f(i) + a(i) - d(i)*n + d(i)*i
 * -f(n) = d(i)*n - [f(i) + a(i) + d(i)*i]
 * -f(n) is taken instant of f(n), for maximizing the ans
 */

/************************************************/
