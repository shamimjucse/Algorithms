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
    //if(c<0)return 100000;
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

/***************************************/

///https://toph.co/p/t5-racing
#include<bits/stdc++.h>
using namespace std;
vector<int>adj[102];
int cost[102],child[102],nxt[102];
void dfs(int u, int p)
{
    int pre = 0;
    child[u] = 0;
    for(auto v : adj[u])
    {
        if(v != p)
        {
            dfs(v,u);
            if(!child[u])
                child[u] = v;
            nxt[pre] = v;
            pre = v;
        }
    }
    nxt[pre] = 0;
}
int k,dp[102][202][2];
int call(int u, int c, int fg)
{
    if(c<0)return 0;
    if(u==0)return 0;
    int &ret = dp[u][c][fg];
    if(~ret)return ret;

    ret = call(nxt[u],c,fg);
    if(fg==0)
    {
        int p = c-1;
        for(int i=0; i<=p; i++)
        {
            ret = max(ret, cost[u] + call(nxt[u],p-i,1) + call(child[u],i,0));
        }
        p = c-2;
        for(int i=0; i<=p; i++)
        {
            ret = max(ret, cost[u] + call(child[u],i,1) + call(nxt[u],p-i,0));
        }
    }
    else
    {
        int p = c-2;
        for(int i=0; i<=p; i++)
        {
            ret = max(ret, cost[u] + call(nxt[u],p-i,1) + call(child[u],i,1));
        }
    }
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
        for(int i=1; i<=n; i++)
        {
            cin >> cost[i];
            adj[i].clear();
        }
        for(int i=1; i<n; i++)
        {
            int u,v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(1,0);
        memset(dp,-1,sizeof dp);
        int ans = call(1,k+1,0);
        cout << "Case " << t++ << ": " << ans << endl;
    }
    return 0;
}

/***************************************/
