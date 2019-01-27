#include"bits/stdc++.h"
#define ll long long
using namespace std;
ll dp[20][100005],depth,N,lcp;
ll ans[100005],v[7];
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
void LCP()
{
    ll i,j,f,p;
    lcp = 0;
    for(i=depth;i>=0;i--)
    {
        f=0;
        for(j=2;j<=N;j++)
        {
            if(dp[i][v[j-1]]!=dp[i][v[j]])
            {
                f=1;
            }
        }
        if(f==0)
        {
            p=(1<<i);
            lcp+=p;
            for(j=1;j<=N;j++)
            {
                v[j]+=p;
            }
        }
    }
}
int main()
{
    string s2,tmp;
    ll i,j,k,l,m,n,p,q,tc,t=1;
    cin >> tc;
    while(tc--)
    {
        memset(dp,0,sizeof dp);
        cin >> N;
        tmp="";
        s="";
        v[0]=1;
        for(i=1;i<=N;i++)
        {
            cin >> s2;
            v[i]=v[i-1]+tmp.size();
            tmp=s2;
            s+=s2;
        }
        suffexArray();
        LCP();
        cout <<"Case #"<<t++<<": ";
        for(i=1;i<=lcp;i++)
        {
            cout << s[i];
        }
        cout << endl;
    }
    return 0;
}
