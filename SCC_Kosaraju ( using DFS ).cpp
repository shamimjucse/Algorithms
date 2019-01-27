#include<bits/stdc++.h>
#define ll long long
using namespace std;
vector<ll>adj[100005],rev[100005],vc;
ll vis[100005],scc[100005],cnt;
void dfs1(ll u)
{
    vis[u] = 1;
    for(ll i=0; i<adj[u].size(); i++)
    {
        ll v = adj[u][i];
        if(!vis[v]) dfs1(v);
    }
    vc.push_back(u);
}
void dfs2(ll u)
{
    vis[u] = 1;
    scc[u] = cnt;
    for(ll i=0; i<rev[u].size(); i++)
    {
        ll v = rev[u][i];
        if(!vis[v]) dfs2(v);
    }
}
void Kosaraju(ll n)
{
    memset(vis,0,sizeof vis);
    for(ll i=1; i<=n; i++)
    {
        if(!vis[i]) dfs1(i);
    }
    reverse(vc.begin(),vc.end());
    memset(vis,0,sizeof vis);
    cnt = 0;
    for(ll i=0; i<vc.size(); i++)
    {
        if(!vis[vc[i]])
        {
            cnt++;
            dfs2(vc[i]);
        }
    }
}
int main()
{
    ll i,j,m,n,p,q,tc;
    cin >> tc;
    while(tc--)
    {
        cin >> n >> m;
        for(i=0; i<m; i++)
        {
            cin >> p >> q;
            adj[p].push_back(q);
            rev[q].push_back(p);
        }
        Kosaraju(n);
        cout << "Number of SCC : " << cnt << endl;

        vc.clear();
        for(i=0; i<=n; i++)
        {
            scc[i]=0;
            adj[i].clear();
            rev[i].clear();
        }
    }
    return 0;
}
