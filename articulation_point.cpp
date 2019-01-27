#include"bits/stdc++.h"
#define ll long long
using namespace std;
vector<ll>adj[10005];
ll dis[10005],low[10005],AP[10005],tim,cnt;
void articulationPoint(ll u, ll p)
{
    dis[u]=low[u]=++tim;
    ll child = 0;
    for(ll i=0;i<adj[u].size();i++)
    {
        ll v = adj[u][i];
        if(v==p)continue;
        if(!low[v])
        {
            low[v]=1;
            child++;
            articulationPoint(v,u);
            low[u]=min(low[u],low[v]);
            if(u!=p && low[v]>=dis[u] && !AP[u])
            {
                AP[u]=1;
                cnt++;
            }
        }
        else
        {
            low[u]=min(low[u],dis[v]);
        }
    }
    if(u==p && child>1)
    {
        AP[u]=1;
        cnt++;
    }
}
int main()
{
    ll i,j,k,p,q,m,n,tc,t=1;
    scanf("%lld",&tc);
    while(tc--)
    {
        scanf("%lld %lld",&n,&m);
        for(i=1;i<=m;i++)
        {
            scanf("%lld %lld",&p,&q);
            adj[p].push_back(q);
            adj[q].push_back(p);
        }
        tim=0;
        cnt = 0;
        articulationPoint(1,1);
        printf("Case %lld: %lld\n",t++,cnt);
        for(i=1;i<=n;i++)
        {
            AP[i]=low[i]=0;
            adj[i].clear();
        }
    }
    return 0;
}
