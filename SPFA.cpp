#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int mx = 100002;
vector<ll>adj[mx],cost[mx];
ll dis[mx],vis[mx];
ll SPFA(ll st, ll ed)
{
    memset(dis,0x7f,sizeof dis);
    memset(vis,0,sizeof vis);
    queue<ll>qu;
    qu.push(st);
    vis[st] = 1;
    dis[st] = 0;

    while(!qu.empty())
    {
        ll u = qu.front();
        qu.pop();
        vis[u] = 0;
        for(int i=0;i<adj[u].size();i++)
        {
            ll v = adj[u][i];
            ll c = cost[u][i];
            if(dis[v] > dis[u]+c)
            {
                dis[v] = dis[u]+c;
                if(!vis[v])
                {
                    qu.push(v);
                }
            }
        }
    }
    return dis[ed];
}
int main()
{
    int n,m;
    cin >> n >> m;
    for(int i=1;i<=m;i++)
    {
        ll u,v,c;
        cin >> u >> v >> c;
        adj[u].push_back(v);
        cost[u].push_back(c);

        adj[v].push_back(u);
        cost[v].push_back(c);
    }
    int st,ed;
    cin >> st >> ed;
    ll ans = SPFA(st,ed);
    cout << ans << endl;
    return 0;
}
