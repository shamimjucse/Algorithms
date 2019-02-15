///Light Oj - 1308
#include"bits/stdc++.h"
using namespace std;
vector<int>adj[10005];
int dis[10005],low[10005],AP[10005],vis[10005];
int tim,cnt,ap,component;
void articulationPoint(int u, int p)
{
    dis[u]=low[u]=++tim;
    int child = 0;
    for(int i=0; i<adj[u].size(); i++)
    {
        int v = adj[u][i];
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
    }
}
void dfs(int u)
{
    cnt++;
    vis[u]=1;
    for(int i=0; i<adj[u].size(); i++)
    {
        int v = adj[u][i];
        if(!vis[v] && !AP[v])
        {
            dfs(v);
        }
        if(AP[v] && vis[v]!=component)
        {
            ap++;
            vis[v]=component;
        }
    }
}
int main()
{
    int i,j,k,p,q,m,n,tc,t=1,ans;
    scanf("%d",&tc);
    while(tc--)
    {
        scanf("%d %d",&n,&m);
        for(i=1; i<=m; i++)
        {
            scanf("%d %d",&p,&q);
            adj[p].push_back(q);
            adj[q].push_back(p);
        }
        tim=0;
        articulationPoint(0,0);
        ans=0;
        component = 0;
        unsigned long long way=1;
        for(i=0; i<n; i++)
        {
            if(!vis[i] && !AP[i])
            {
                cnt=ap=0;
                ++component;
                dfs(i);
                if(ap < 2)
                {
                    ans++;
                    way*=cnt;
                }
            }
        }
        if(ans == 1)
        {
            ans++;
            way = (n*(n-1))/2;
        }
        printf("Case %d: %d %llu\n",t++,ans,way);
        for(i=0; i<=n; i++)
        {
            AP[i]=low[i]=vis[i]=0;
            adj[i].clear();
        }
    }
    return 0;
}
