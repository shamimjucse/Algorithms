#include"bits/stdc++.h"
#define ll long long
#define inf 999999999999LL
using namespace std;
ll dis[17][17],dp[17][(1<<17)+2],path[17];
ll ShortestHamiltonianPath(ll n)
{
    ll i,j,k,mask;
    for(i=0; i<n; i++)
    {
        fill(dp[i],dp[i]+(1<<n),inf);
    }
    for(i=0; i<n; i++)
    {
        dp[i][1<<i]=0;
    }
    for(mask=1 ; mask<(1<<n) ; mask+=2)
    {
        for(i=0; i<n; i++)
        {
            if((mask & (1<<i))!=0)
            {
                for(j=0; j<n; j++)
                {
                    if((mask & (1<<j))!=0)
                    {
                        dp[i][mask]=min(dp[i][mask],
                                        dp[j][mask^(1<<i)]+dis[i][j]);
                    }
                }
            }
        }
    }
    ll ans = inf+inf;
    for(i=1; i<n; i++)
    {
        ans = min(ans,dp[i][(1<<n)-1]);
    }
    return ans;
}
void PathPrint(ll n)
{
    ll i,j,last,nw,mask;
    mask = (1<<n)-1;
    last = -1;
    for(i=n-1; i>=0; i--)
    {
        nw = -1;
        for(j=0; j<n; j++)
        {
            if((mask & (1<<j))!=0)
            {
                if(nw==-1||dp[nw][mask]+(last==-1?0:dis[nw][last])>
                        dp[j][mask]+(last==-1?0:dis[j][last]))
                {
                    nw = j;
                }
            }
        }
        path[i] = nw;
        mask^=(1<<nw);
        last = nw;
    }
    cout << "Shortest Path : " << path[0]+1;
    for(i=1; i<n; i++)
    {
        cout << "->" << path[i]+1;
    }
    cout << endl;
}
int main()
{
    ll i,j,m,n,p,q,c,tc;
    cin >> tc;
    while(tc--)
    {
        cin >> n >> m;
        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                dis[i][j] = inf;
            }
        }
        for(i=1; i<=m; i++)
        {
            cin >> p >> q >> c;
            p--,q--;
            dis[p][q] = c;
        }

        p = ShortestHamiltonianPath(n);
        if(p<inf)
        {
            cout << "Minimum cost = " << p << endl;
            PathPrint(n);
        }
        else
        {
            cout << "No path exists" << endl;
        }
    }
    return 0;
}
