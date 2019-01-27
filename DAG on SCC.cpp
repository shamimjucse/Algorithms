///SPOJ - HELPR2D2
#include"bits/stdc++.h"
#define ll long long
using namespace std;
vector<ll>adj[1005];
stack<ll>st;
ll dis[1005],low[1005],scc[1005],tim,cnt;
ll a[1005][1005],num[1005],vis[1005];
void tarjan(ll u)
{
    dis[u]=low[u]=++tim;
    st.push(u);
    for(ll i=0; i<adj[u].size(); i++)
    {
        ll v = adj[u][i];
        if(!low[v])
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(!scc[v])
        {
            low[u]=min(low[u],dis[v]);
        }
    }
    if(low[u] == dis[u])
    {
        scc[u] = ++cnt;
        ll y;
        do
        {
            y = st.top();
            scc[y]=cnt;
            num[cnt]++;
            st.pop();
        }
        while(y != u);
    }
}
void scc_tarjan(ll n)
{
    tim = 0;
    cnt = 0;
    for(ll i=1; i<=n; i++)
    {
        if(!low[i])
        {
            tarjan(i);
        }
    }
}
ll dfs(ll u)
{
    vis[u]=1;
    ll p = num[u];
    for(ll i=0;i<adj[u].size();i++)
    {
        ll v = adj[u][i];
        if(!vis[v]) p+=dfs(v);
    }
    return p;
}
ll BuildDag(ll n)
{
    ll i,j;
    for(i=0; i<=n; i++) adj[i].clear();
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(scc[i]!=scc[j] && a[i][j])
            {
                adj[scc[i]].push_back(scc[j]);
            }
        }
    }
    ll ans = 0;
    for(i=1;i<=cnt;i++)
    {
        memset(vis,0,sizeof vis);
        if(dfs(i)==n)
        {
            ans+=num[i];
        }
    }
    return ans;
}
int main()
{
    ll i,j,k,n,m,p,q,tc;
    cin >> tc;
    while(tc--)
    {
        cin >> n;
        for(i=1;i<=n;i++)
        {
            cin >> m;
            for(j=1;j<=m;j++)
            {
                cin >> p;
                adj[p].push_back(i);
                a[p][i]=1;
            }
        }
        scc_tarjan(n);
        p = BuildDag(n);
        cout << p << endl;

        memset(a,0,sizeof a);
        memset(num,0,sizeof num);
        for(i=0; i<=n; i++)
        {
            adj[i].clear();
            low[i]=scc[i]=0;
        }
    }
    return 0;
}
