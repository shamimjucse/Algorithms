#include<bits/stdc++.h>
#define ll long long
#define inf 99999999999LL
using namespace std;
vector<ll>adj[100005];
ll match[100005],dis[100005],N;
bool BFS()
{
    queue<ll>qu;
    for(ll i=1; i<=N; i++)
    {
        if(match[i]==0)
        {
            dis[i]=0;
            qu.push(i);
        }
        else
        {
            dis[i]=inf;
        }
    }
    dis[0]=inf;
    while(!qu.empty())
    {
        ll u = qu.front();
        qu.pop();
        if(u==0)continue;
        for(ll i=0; i<adj[u].size(); i++)
        {
            ll v = adj[u][i];
            if(dis[match[v]]==inf)
            {
                dis[match[v]] = dis[u]+1;
                qu.push(match[v]);
            }
        }
    }
    return (dis[0]!=inf);
}
bool DFS(ll u)
{
    if(u==0)return 1;
    for(ll i=0; i<adj[u].size(); i++)
    {
        ll v = adj[u][i];
        if(dis[match[v]]==dis[u]+1)
        {
            if(DFS(match[v]))
            {
                match[v] = u;
                match[u] = v;
                return 1;
            }
        }
    }
    dis[u] = inf;
    return 0;
}
ll MaximumMatching()
{
    ll ans = 0;
    while(BFS())
    {
        for(ll i=1; i<=N; i++)
        {
            if(match[i]==0 && DFS(i))
            {
                ans+=1;
            }
        }
    }
    return ans;
}
int main()
{
    ll i,j,n,m,p,q,k,tc;
    cin >> tc;
    while(tc--)
    {
        cin >> n >> m >> k;
        for(i=1; i<=k; i++)
        {
            cin >> p >> q;
            adj[p].push_back(q+n);
            adj[q+n].push_back(p);
        }
        N = n;
        p = MaximumMatching();
        cout << p << endl;

        for(i=0; i<=n+m; i++)
        {
            match[i] = 0;
            adj[i].clear();
        }
    }
    return 0;
}
