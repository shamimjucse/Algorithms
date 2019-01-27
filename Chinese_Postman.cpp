///UVa - 10296
#include<bits/stdc++.h>
#define ll long long
#define inf 9999999999LL
using namespace std;
ll dis[16][16],deg[16],dp[1<<16],N;
void floyd_warshall(ll n)
{
    ll i,j,k;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            for(k=1;k<=n;k++)
            {
                if(dis[j][k]>dis[j][i]+dis[i][k])
                {
                    dis[j][k]=dis[j][i]+dis[i][k];
                }
            }
        }
    }
}
ll ChinesePostman(ll mask)
{
    if(mask == 0) return 0;
    ll &ret = dp[mask];
    if(~ret) return ret;
    ret = inf;
    for(ll i=1;i<=N;i++)
    {
        if((mask&(1<<i)))
        {
            for(ll j=1;j<i;j++)
            {
                if((mask&(1<<j)))
                {
                    ll p = mask^(1<<i)^(1<<j);
                    ret = min(ret,dis[i][j]+ChinesePostman(p));
                }
            }
        }
    }
    return ret;
}
int main()
{
    ll i,j,m,n,p,q,k,sm;
    while(cin >> n && n)
    {
        cin >> m;
        for(i=0;i<=n;i++)
        {
            for(j=0;j<=n;j++)
            {
                if(i==j)dis[i][j]=0;
                else dis[i][j]=inf;
            }
        }
        sm=0;
        memset(deg,0,sizeof deg);
        for(i=1;i<=m;i++)
        {
            cin >> p >> q >> k;
            sm+=k;
            deg[p]++,deg[q]++;
            dis[p][q]=dis[q][p]=min(dis[q][p],k);
        }
        floyd_warshall(n);
        ll mask = 0;
        for(i=1;i<=n;i++)
        {
            if(deg[i]&1)
            {
                mask = mask|(1<<i);
            }
        }
        N = n;
        memset(dp,-1,sizeof dp);
        sm+=ChinesePostman(mask);
        cout << sm << endl;
    }
    return 0;
}
