///Convex Hull Tricks

/**********************************************/

///Online update and online query
///everything is fine as long as you want the minimum/maximum

///https://codeforces.com/problemset/problem/1083/E
#include <bits/stdc++.h>
#define ll long long
using namespace std;
typedef long double float128;
const ll is_query = -(1LL<<62), inf = 1e18;
struct Line
{
    ll m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line& rhs) const
    {
        if (rhs.b != is_query)return m < rhs.m;
        const Line* s = succ();
        if (!s)return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};

struct HullDynamic : public multiset<Line>   // // will maintain lower hull for minimum/maximum
{
    bool bad(iterator y)
    {
        auto z = next(y);
        if (y == begin())
        {
            if (z == end())return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end())return y->m == x->m && y->b <= x->b;
        return (float128)(x->b - y->b)*(z->m - y->m) >= (float128)(y->b - z->b)*(y->m - x->m);
    }
    void add_line(ll m, ll b)
    {
        //auto y = insert({ -m, -b });// For minimum
        auto y = insert({ m, b });// For maximum
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y))
        {
            erase(y);
            return;
        }
        while (next(y) != end() && bad(next(y)))erase(next(y));
        while (y != begin() && bad(prev(y)))erase(prev(y));
    }

    ll getbest(ll x)
    {
        auto l = *lower_bound((Line)
        {
            x, is_query
        });
        //return -(l.m * x + l.b);//// For minimum
        return (l.m * x + l.b);//// For maximum
    }
}st;

vector<pair<pair<ll,ll>,ll>>v;
int main()
{
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    ll n;
    cin >> n;
    for(int i=0;i<n;i++)
    {
        ll x,y,a;
        cin >> x >> y >> a;
        v.push_back({{x,y},a});
    }
    sort(v.begin(),v.end());
    ll ans = 0;
    st.add_line(0,0);
    for(int i=0;i<n;i++)
    {
        ll x = v[i].first.first;
        ll y = v[i].first.second;
        ll a = v[i].second;

        ll val = st.getbest(y)+x*y-a;
        st.add_line(-x,val);
        ans = max(ans,val);
    }
    cout<<ans<<endl;
    return 0;
}

/**********************************************/

///For ofline mimimum query
///https://codeforces.com/problemset/problem/319/C
#include <bits/stdc++.h>
#define ll long long
using namespace std;
typedef pair<ll,ll> pll;

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

///For ofline maximum query
///https://codeforces.com/problemset/problem/1083/E
#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct CHT
{
    vector<long long> a, b;

    double cross(int i, int j, int k)
    {
        return 1.d*(a[j] - a[i])*(b[k] - b[i]) - 1.d*(a[k] - a[i])*(b[j] - b[i]);
    }

    void add(long long A, long long B)
    {
        a.push_back(-A),b.push_back(-B);
        while (a.size() > 2 && cross(a.size() - 3, a.size() - 2, a.size() - 1) <= 0)
        {
            a.erase(a.end() - 2);
            b.erase(b.end() - 2);
        }
    }
    long long query(long long x)
    {
        if (a.empty())return (long long)1e18;
        int l = 0, r = a.size() - 1;
        while (l < r)
        {
            int mid = l + (r - l)/2;
            long long f1 = a[mid] * x + b[mid];
            long long f2 = a[mid + 1] * x + b[mid + 1];
            if (f1 > f2)l = mid + 1;
            else r = mid;
        }
        return -(a[l]*x + b[l]);
    }
}st;

vector<pair<pair<ll,ll>,ll>>v;
int main()
{
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    ll n;
    cin >> n;
    for(int i=0;i<n;i++)
    {
        ll x,y,a;
        cin >> x >> y >> a;
        v.push_back({{x,y},a});
    }
    sort(v.begin(),v.end());
    ll ans = 0;
    st.add(0,0);
    for(int i=0;i<n;i++)
    {
        ll x = v[i].first.first;
        ll y = v[i].first.second;
        ll a = v[i].second;

        ll val = st.query(y)+x*y-a;
        st.add(-x,val);
        ans = max(ans,val);
    }
    cout<<ans<<endl;
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
        //line temp = line(-a, -b);//for maximum
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
        return (it -> a * x + it -> b);
        //return (it -> a * x + it -> b);//for maximum
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
