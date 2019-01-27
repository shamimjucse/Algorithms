#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[12],b[12],dis[12][12],dp[11][(1<<11)],N,ans;
vector<ll>v;
ll TSP(ll pos, ll mask)
{
    if(mask == (1<<N)-1)
        return dis[pos][0];
    ll &ret = dp[pos][mask];
    if(~ret) return ret;
    ret = INT_MAX;
    for(ll i=0; i<N; i++)
    {
        if((mask & (1<<i))==0)
        {
            ll p = mask | (1<<i);
            ret = min(ret, dis[pos][i]+TSP(i,p));
        }
    }
    return ret;
}
void PathPrint(ll pos, ll mask)
{
    if(mask == (1<<N)-1)
    {
        v.push_back(0);
        return ;
    }
    for(ll i=0; i<N; i++)
    {
        if((mask & (1<<i))==0)
        {
            ll p = mask | (1<<i);
            ll q = dis[pos][i]+TSP(i,p);
            if(q==ans)
            {
                v.push_back(i);
                ans-=dis[pos][i];
                PathPrint(i,p);
                break;
            }
        }
    }
}
int main()
{
    ll i,j,r,c,n,m,tc,k;
    cin >> tc;
    while(tc--)
    {
        cin >> r >> c;
        cin >> a[0] >> b[0];
        cin >> n;
        for(i=1; i<=n; i++)
        {
            cin >> a[i] >> b[i];
        }
        for(i=0; i<=n; i++)
        {
            for(j=0; j<=n; j++)
            {
                dis[i][j]=abs(a[i]-a[j])+abs(b[i]-b[j]);
            }
        }
        N = n+1;
        memset(dp,-1,sizeof dp);
        m = TSP(0,0);
        cout << "The shortest path has length " << m << endl;

        ans = m;
        PathPrint(0,0);
        cout << "The path is :: " << endl;
        for(i=0; i<v.size(); i++)
        {
            k = v[i];
            cout << a[k] << " " << b[k] << endl;
        }
    }
    return 0;
}
