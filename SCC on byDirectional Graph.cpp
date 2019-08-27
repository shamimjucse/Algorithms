// Light OJ - 1291
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mx = 10005;
vector<int>adj[mx],vc[mx];
int dis[mx],low[mx],tim,component;
int vis[mx],com[mx];
map<pair<int,int>,int>mp;
void bridge(int u, int p)
{
    dis[u]=low[u]=++tim;
    for(auto v : adj[u])
    {
        if(v==p)continue;
        if(!low[v])
        {
            low[v] = 1;
            bridge(v,u);
            low[u] = min(low[u],low[v]);

            if(low[v] > dis[u])
            {
                mp[{u,v}] = 1;
                mp[{v,u}] = 1;
            }
        }
        else
        {
            low[u] = min(low[u],dis[v]);
        }
    }
}
void dfs(int u)
{
    com[u] = component;
    for(auto v : adj[u])
    {
        if(!com[v] && !mp.count({u,v}))
        {
            dfs(v);
        }
    }
}
void build(int u, int p)
{
    vis[u] = 1;
    for(auto v:adj[u])
    {
        if(v!=p && !vis[v])
        {
            if(com[u]!=com[v])
            {
                vc[com[u]].push_back(com[v]);
                vc[com[v]].push_back(com[u]);
            }
            build(v,u);
        }
    }
}
int main()
{
    int tc,t=1;
    scanf("%d",&tc);
    while(tc--)
    {
        int n,m;
        scanf("%d %d",&n,&m);
        for(int i=1;i<=m;i++)
        {
            int p,q;
            scanf("%d %d",&p,&q);
            adj[p].push_back(q);
            adj[q].push_back(p);
        }
        tim = 0;
        bridge(0,0);
        component = 0;
        for(int i=0;i<n;i++)
        {
            if(!com[i])
            {
                component++;
                dfs(i);
            }
        }
        build(0,-1);
        ll cnt = 0;
        for(int i=1;i<=component;i++)
            if(vc[i].size()==1)cnt++;
        ll ans = (cnt+1)/2;
        printf("Case %d: %lld\n",t++,ans);

        mp.clear();
        for(int i=0; i<=n; i++)
        {
            adj[i].clear();
            vc[i].clear();
            low[i]=com[i]=vis[i]=0;
        }
    }
    return 0;
}
