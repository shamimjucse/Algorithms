#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[12],b[12],dis[12][12],dp[11][(1<<11)],N;
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
int main()
{
    ll i,j,r,c,n,m,tc;
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
    }
    return 0;
}
