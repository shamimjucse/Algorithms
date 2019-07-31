/// Light OJ - 1252
#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int>>adj[102];
//nxt[u] = next sibling of node u
//child[u] = first child of node u
//cost[u] = cost of edge v->u, where v is the parent of node u
int cost[102],child[102],nxt[102];
int dfs(int u, int p)
{
    int pre = 0;
    child[u] = 0;
    for(auto pr : adj[u])
    {
        int v = pr.first;
        int c = pr.second;
        if(v != p)
        {
            dfs(v,u);
            if(!child[u])child[u] = v;
            nxt[pre] = v;
            cost[v] = c;
            pre = v;
        }
    }
    nxt[pre] = 0;
}
int k,dp[102][102];
int call(int u, int c)
{
    if(u==0)return 0;
    int &ret = dp[u][c];
    if(~ret)return ret;
    //disconnect from root
    ret = 1 + call(nxt[u],c) + call(child[u],k);
    //connected with root
    int p = c - cost[u];
    for(int i=0;i<=p;i++)
        ret = min(ret, call(child[u],i) + call(nxt[u],p-i));
    return ret;
}
int main()
{
    int tc,t=1;
    cin >> tc;
    while(tc--)
    {
        int n;
        cin >> n >> k;
        for(int i=1;i<=n;i++)adj[i].clear();
        for(int i=1;i<n;i++)
        {
            int u,v,c;
            cin >> u >> v >> c;
            adj[u].push_back({v,c});
            adj[v].push_back({u,c});
        }
        dfs(1,0);
        memset(dp,-1,sizeof dp);
        int ans = call(1,k)+1;
        cout << "Case " << t++ << ": " << ans << endl;
    }
    return 0;
}
