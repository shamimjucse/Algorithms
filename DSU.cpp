///https://codeforces.com/contest/600/problem/E
#include<bits/stdc++.h>
#define ll long long
#define N 100005
using namespace std;
vector<ll>adj[N];
ll col[N],ans[N],heavy[N],sz[N];
void dfs(ll u, ll p)
{
    sz[u]=1;
    heavy[u]=-1;
    for(ll i=0; i<adj[u].size(); i++)
    {
        ll v = adj[u][i];
        if(v==p)continue;
        dfs(v,u);
        sz[u]+=sz[v];
        if(heavy[u]==-1 || sz[v]>sz[heavy[u]]) heavy[u]=v;
    }
}
bool hv[N];
ll cnt[N],mx,sm;
void Add(ll u, ll p, ll x)
{
    cnt[col[u]]+=x;
    if(cnt[col[u]]==mx)sm+=col[u];
    else if(cnt[col[u]]>mx)mx=cnt[col[u]],sm=col[u];
    for(ll i=0; i<adj[u].size(); i++)
    {
        ll v = adj[u][i];
        if(v==p || hv[v])continue;
        Add(v,u,x);
    }
}
void dsu(ll u, ll p, bool flg)
{
    for(ll i=0; i<adj[u].size(); i++)
    {
        ll v = adj[u][i];
        if(v==p || v==heavy[u])continue;
        dsu(v,u,0); ///CLR Light Child
    }
    if(~heavy[u])dsu(heavy[u],u,1),hv[heavy[u]]=1;///Keep Heavy Child
    Add(u,p,1);///Actual work in cnt array
    ans[u] = sm;
    if(~heavy[u]) hv[heavy[u]]=0;
    if(flg==0) Add(u,p,-1),sm=mx=0;
}
int main()
{
    ll i,j,k,p,q,m,n;
    cin >> n;
    for(i=1; i<=n; i++)
    {
        cin >> col[i];
    }
    for(i=1; i<n; i++)
    {
        cin >> p >> q;
        adj[p].push_back(q);
        adj[q].push_back(p);
    }
    dfs(1,-1);
    dsu(1,-1,1);
    for(i=1; i<=n; i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
