///UVA - 11838
#include"bits/stdc++.h"
#define ll long long
using namespace std;
vector<ll>adj[100005];
stack<ll>st;
ll dis[100005],low[100005],scc[100005],tim,cnt;
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
int main()
{
    ll i,j,k,n,m,p,q;
    while(cin >> n >> m && (n||m))
    {
        for(i=1; i<=m; i++)
        {
            cin >> p >> q >> k;
            if(k==1)
            {
                adj[p].push_back(q);
            }
            else
            {
                adj[p].push_back(q);
                adj[q].push_back(p);
            }
        }
        scc_tarjan(n);
        if(cnt==1)k=1;
        else k=0;
        cout << k << endl;

        for(i=0; i<=n; i++)
        {
            adj[i].clear();
            low[i]=scc[i]=0;
        }
    }
    return 0;
}


