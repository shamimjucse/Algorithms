///SPOJ - QTREE5
#include<bits/stdc++.h>
#define MX 100005
#define pb push_back
#define inf 100000000
using namespace std;
vector<int>vc[MX];
multiset<int>ans[MX];
int SubTree[MX],del[MX],par[MX],col[MX];
int dis[17][MX],level[MX];
void dfs(int u, int p)
{
    SubTree[u]=1;
    for(int i=0;i<vc[u].size();i++)
    {
        int v = vc[u][i];
        if(v==p || del[v])continue;
        dfs(v,u);
        SubTree[u]+=SubTree[v];
    }
}
int GetCenter(int u, int p, int sz)
{
    for(int i=0;i<vc[u].size();i++)
    {
        int v = vc[u][i];
        if(v==p || del[v])continue;
        if(SubTree[v]>sz/2)return GetCenter(v,u,sz);
    }
    return u;
}
void SetDist(int u, int p, int cost, int lev)
{
    dis[lev][u]=cost;
    for(int i=0;i<vc[u].size();i++)
    {
        int v = vc[u][i];
        if(v==p || del[v])continue;
        SetDist(v,u,cost+1,lev);
    }
    return;
}
void Decompose(int u, int p, int lev)
{
    dfs(u,-1);
    int center = GetCenter(u,-1,SubTree[u]);
    SetDist(center,-1,0,lev);

    del[center]=1;
    par[center]=p;
    level[center]=lev;
    ans[center].insert(inf);
    for(int i=0;i<vc[center].size();i++)
    {
        int v = vc[center][i];
        if(!del[v])Decompose(v,center,lev+1);
    }
}
void update1(int u)
{
    int v=u,lev=level[u];
    while(v!=-1)
    {
        ans[v].insert(dis[lev][u]);
        v = par[v],lev--;
    }
}
void update2(int u)
{
    int v=u,lev=level[u];
    while(v!=-1)
    {
        ans[v].erase(ans[v].find(dis[lev][u]));
        v = par[v],lev--;
    }
}
int query(int u)
{
    int v=u, lev=level[u];
    int ret = inf;
    while(v!=-1)
    {
        ret = min(ret, *ans[v].begin()+dis[lev][u]);
        v = par[v], lev--;
    }
    return ret==inf?-1:ret;
}
int main()
{
    int i,k,n,m,p,q;
    scanf("%d",&n);
    for(i=1;i<n;i++)
    {
        scanf("%d %d",&p,&q);
        vc[p].pb(q);
        vc[q].pb(p);
    }
    Decompose(1,-1,0);
    scanf("%d",&m);
    while(m--)
    {
        scanf("%d %d",&k,&p);
        if(k)printf("%d\n",query(p));
        else
        {
            if(col[p]) col[p]=0, update2(p);
            else       col[p]=1, update1(p);
        }
    }
    return 0;
}
