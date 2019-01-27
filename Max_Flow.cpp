///Light oj - 1153 solution
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MX = 100;
const int INF = 5005;

struct edge
{
    int x,y,f,c;
};
vector<edge> e;
vector<int> adj[MX+2];
int src,snk,ptr[MX+2],dis[MX+2];
void addEdge(int p, int q, int c)
{
    edge ed;
    ed = {p,q,0,c};
    adj[p].push_back(e.size());
    e.push_back(ed);
    ed = {q,p,0,c};
    adj[q].push_back(e.size());
    e.push_back(ed);
}
bool bfs()
{
    memset(dis,-1,sizeof dis);
    queue<int>qu; dis[src] = 0, qu.push(src);
    while(!qu.empty() && dis[snk]==-1)
    {
        int u = qu.front(); qu.pop();
        for(int i = 0;i<adj[u].size();i++)
        {
            int id = adj[u][i], v = e[id].y;
            if(dis[v]==-1 && e[id].f<e[id].c)
            {
                dis[v] = dis[u] + 1;
                qu.push(v);
            }
        }
    }
    return ~dis[snk];
}
int dfs(int u, int flow)
{
    if(!flow) return 0;
    if(u == snk) return flow;
    for( ; ptr[u]<adj[u].size() ; ptr[u]++)
    {
        int id = adj[u][ptr[u]], v = e[id].y;
        if(dis[v]!=dis[u]+1) continue;
        int pushed = dfs(v,min(flow,e[id].c-e[id].f));
        if(pushed)
        {
            e[id].f+=pushed;
            e[id^1].f-=pushed;
            return pushed;
        }
    }
    return 0;
}
ll MaxFlowDinic()
{
    ll flow =0;
    while(bfs())
    {
        memset(ptr,0,sizeof ptr);
        while(int pushed=dfs(src,INF))
        {
            flow+=pushed;
        }
    }
    return flow;
}
int main()
{
    int i,j,m,n,p,q,c,tc,t=1;
    scanf("%d",&tc);
    while(tc--)
    {
        scanf("%d",&n);
        scanf("%d %d %d",&src,&snk,&m);
        for(i=1; i<=m; i++)
        {
            scanf("%d %d %d", &p, &q, &c);
            addEdge(p,q, c);
        }
        printf("Case %d: %lld\n",t++, MaxFlowDinic());
        e.clear();
        for(i=0;i<=n;i++)adj[i].clear();
    }
    return 0;
}
