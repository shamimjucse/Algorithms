#include"bits/stdc++.h"
#define ll long long
using namespace std;
ll dp[20][100005],depth;
ll ans[100005];
string s;
struct data
{
    ll x,y,pos;
    data() {}
    data(ll _x, ll _y, ll _pos)
    {
        x=_x,y=_y,pos=_pos;
    }
    bool operator<(const data &p)const
    {
        //return (x==p.x?(y==p.y?pos<p.pos:y<p.y):x<p.x);
        return (x==p.x?y<p.y:x<p.x);
    }
} a[100005];
void suffexArray()
{
    /// use int instant LL for reduce TLE
    s=' '+s;
    ll i,j,k,l,row;
    l=s.size();
    memset(dp,0,sizeof dp);
    for(i=1; i<l; i++)
    {
        dp[0][i]=s[i];
    }
    for(row=1,k=1; k<l; row++,k*=2)
    {
        for(i=1; i<l; i++)
        {
            a[i].x  = dp[row-1][i];
            a[i].y  = (i+k<=l) ? dp[row-1][i+k]:-1;
            a[i].pos= i;
        }
        sort(a+1,a+l); /// sort start from index 1
        for(i=1; i<l; i++)
        {
            dp[row][a[i].pos]=(i>1&&a[i].x==a[i-1].x&&a[i].y==a[i-1].y)?dp[row][a[i-1].pos]:dp[row][a[i-1].pos]+1;
        }
        if(row==l) break;
    }
    depth = row-1;
    for(i=1; i<l; i++)
    {
        ans[dp[depth][i]]=i-1; /// storing ans 0 indexing
    }
}
int main()
{
    ll i,j,k,l,m,n,row,p;
    while(cin >> s)
    {
        suffexArray();
        for(i=1; i<s.size(); i++)
        {
            printf("%lld\n",ans[i]);
        }
    }
    return 0;
}

