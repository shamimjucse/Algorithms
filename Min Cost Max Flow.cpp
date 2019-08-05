/// Light OJ - 1404
#include<bits/stdc++.h>
#define T int
using namespace std;

const int mx = 52;
const int inf = 1e9;

int head[mx],par[mx];
T dis[mx];
bool chk[mx];

struct edge
{
    int u,v,cap,next;
    T cost;
    edge() {}
    edge(int a, int b, int c, T d, int e){u=a, v=b, cap=c, cost=d, next=e;}
};

edge e[2*mx*mx];
int ed;

int init(int n)
{
    for(int i=0; i<=n; i++)head[i]=-1;
    ed = 0;
}

inline void addEdge(int u, int v, int cap, T cost)
{
    e[ed] = edge(u,v,cap,cost,head[u]);
    head[u] = ed++;
    e[ed] = edge(v,u,0,-cost,head[v]);
    head[v] = ed++;
}

int spfa(int src, int snk, int tot)
{
    queue<int>qu;
    for(int i=0;i<=tot;i++)par[i]=-1,chk[i]=false,dis[i]=inf;
    qu.push(src);
    dis[src] = 0;
    chk[src] = true;
    while(!qu.empty())
    {
        int u = qu.front();
        qu.pop();
        chk[u] = false;
        for(int i=head[u]; i!=-1; i=e[i].next)
        {
            int v = e[i].v;
            T w = e[i].cost;
            if(e[i].cap>0 && dis[v]>dis[u]+w)
            {
                dis[v] = dis[u]+w;
                par[v] = i;
                if(!chk[v])
                {
                    chk[v]=true;
                    qu.push(v);
                }
            }
        }
    }
    if(par[snk]==-1)return 0;
    int cap = inf;
    for(int i=par[snk]; i!=-1; i=par[e[i].u]) cap=min(cap,e[i].cap);
    for(int i=par[snk]; i!=-1; i=par[e[i].u]) e[i].cap-=cap,e[i^1].cap+=cap;
    return cap;
}

pair<int,T>minCostMaxFlow(int src, int snk, int tot)
{
    T ret = 0;
    int flow = 0;
    while(true)
    {
        int cap = spfa(src,snk,tot);
        if(cap == 0) break;
        flow+=cap;
        ret+=cap*dis[snk];
    }
    return {flow,ret};
}

int main()
{
    int tc,t=1;
    cin >> tc;
    while(tc--)
    {
        int n,m,p;
        cin >> n >> m >> p;
        init(n+2); //Clear
        for(int i=1;i<=m;i++)
        {
            int u,v,w,c;
            cin >> u >> v >> w >> c;
            addEdge(u,v,w,c);
            addEdge(v,u,w,c);
        }
        int src = 0, snk = n+1;
        addEdge(0,1,p,0);
        addEdge(n,n+1,p,0);
        pair<int,int>ans = minCostMaxFlow(src,snk,snk);
        cout << "Case " << t++ << ": ";
        if(ans.first<p)cout << "impossible\n";
        else cout << ans.second << "\n";
    }
    return 0;
}
