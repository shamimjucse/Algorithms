#include<bits/stdc++.h>
#define ll long long
using namespace std;
vector<ll>adj[10005];
stack<ll>st;
ll dis[10005],low[10005],scc[10005],tim,cnt;
void tarjan(ll u)
{
    dis[u]=low[u]=++tim;
    st.push(u);
    for(ll i=0;i<adj[u].size();i++)
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
    if(low[u]==dis[u])
    {
        scc[u] = ++cnt;
        ll y;
        do
        {
            y = st.top();
            scc[y]=cnt;
            st.pop();
        }
        while(y!=u);
    }
}
ll Two_SAT(ll n)
{
    tim=0;
    cnt=0;
    for(ll i=1;i<=n;i++)
    {
        if(!low[i])
        {
            tarjan(i);
        }
    }
    for(ll i=1;i<=n;i+=2)
    {
        if(scc[i]==scc[i+1])
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    ll i,j,n,tc,t=1,m,p,q;
    cin >> tc;
    while(tc--)
    {
        cin >> n >> m;
        n<<=1;///n=2*n
        for(i=1;i<=m;i++)
        {
            cin >> p >> q;
            p<<=1,q<<=1;
            adj[p].push_back(q-1);
            adj[q-1].push_back(p);
            adj[q].push_back(p-1);
            adj[p-1].push_back(q);
        }
        cout << "Scenario #" << t++ << ":" << endl;
        if(!Two_SAT(n))
        {
            cout << "Suspicious bugs found!" << endl;
        }
        else
        {
            cout << "No suspicious bugs found!" << endl;
        }
        for(i=0; i<=n; i++)
        {
            adj[i].clear();
            low[i]=scc[i]=0;
        }
    }
    return 0;
}

