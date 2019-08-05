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

/*********************************************************/
///Vertices Cover
#include<bits/stdc++.h>
using namespace std;

const int mx = 1002;
bool vis[mx];
int match[mx];
vector<int>adj[mx];

/// Call this function after calling matching
vector<int> koing(int n, int m)
{
    ///Return a optimal set of vertices to cover the graph (vertex cover)
    queue<int> qu;
    vector<bool> vis(n+m+1,0);
    set<int> st;
    for(int i=1; i<=n; i++)
    {
        if(match[i]==0)
        {
            qu.push(i);
            vis[i]=1;
            st.insert(i);
        }
    }
    while(!qu.empty())
    {
        int u = qu.front();
        qu.pop();
        for(auto v : adj[u])
        {
            st.insert(v);
            if(match[v] && !vis[match[v]])
            {
                st.insert(match[v]);
                qu.push(match[v]);
                vis[match[v]]=1;
            }
        }
    }
    vector<int> vc;
    for(int i=1; i<=n; i++)
        if(st.find(i)!=st.end())
            vc.push_back(i);
    for(int i=n+1; i<=n+m; i++)
        if(st.find(i)!=st.end())
            vc.push_back(i);
    return vc;
}
/*********************************************************/
