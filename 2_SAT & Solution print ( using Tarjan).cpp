///Light oj - 1251
#include<bits/stdc++.h>
#define ll long long
using namespace std;
vector<ll>adj[20005];
stack<ll>st;
ll dis[20005],low[20005],scc[20005],tim,cnt;
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
    for(ll i=2; i<=n+1; i++)
    {
        if(!low[i])
        {
            tarjan(i);
        }
    }
    for(ll i=2; i<=n+1; i+=2)
    {
        if(scc[i]==scc[i^1])
        {
            return 0;
        }
    }
    return 1;
}
void solution_print(ll n)
{
    vector<ll>v;
    for(ll i=2; i<=n+1; i+=2)
    {
        if(scc[i]>scc[i^1])
        {
            v.push_back(i/2);
        }
    }
    cout << v.size();
    for(ll i=0; i<v.size(); i++)
    {
        cout << " " << v[i];
    }
    cout << endl;
}
int main()
{
    ll i,j,n,tc,t=1,m,p,q;
    cin >> tc;
    while(tc--)
    {
        cin >> m >> n;
        n<<=1;///n=2*n
        for(i=1; i<=m; i++)
        {
            cin >> p >> q;
            p<<=1,q<<=1;
            if(p<0)p=-p,p^=1;
            if(q<0)q=-q,q^=1;
            adj[p].push_back(q^1);
            adj[q].push_back(p^1);
        }
        cout << "Case " << t++ << ": ";
        if(!Two_SAT(n))
        {
            cout << "No" << endl;
        }
        else
        {
            cout << "Yes" << endl;
            solution_print(n);
        }
        for(i=0; i<=n+2; i++)
        {
            adj[i].clear();
            low[i]=scc[i]=0;
        }
    }
    return 0;
}
