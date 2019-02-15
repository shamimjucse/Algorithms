///Light OJ - 1348 - Aladdin and the Return Journey
#include<bits/stdc++.h>
#define ll long long
#define maxn 30010
using namespace std;

struct edge
{
    ll to,nxt;
}e[2*maxn];
ll id,num;
ll head[maxn],tr[3*maxn];
void add_edge(ll u, ll v)
{
    e[id].to=v; e[id].nxt=head[u]; head[u]=id++;
    e[id].to=u; e[id].nxt=head[v]; head[v]=id++;
}
ll dep[maxn],sz[maxn],child[maxn],par[maxn];
void dfs1(ll node, ll parent, ll depth)
{
    dep  [node] = depth;
    sz   [node] = 1;
    child[node] = 0;
    par  [node] = parent;
    for(ll i=head[node] ; ~i ; i=e[i].nxt)
    {
        ll nw = e[i].to;
        if(nw==parent)continue;
        dfs1(nw,node,depth+1);
        sz[node]+=sz[nw];
        if(sz[child[node]]<sz[nw]) child[node]=nw;
    }
}
ll top[maxn],position[maxn],a[maxn],b[maxn];
void dfs2(ll node, ll val)
{
    top[node] = val;
    position[node] = ++num;
    if(child[node])dfs2(child[node],val);
    for(ll i=head[node] ; ~i ; i=e[i].nxt)
    {
        ll v = e[i].to;
        if(v==par[node] || v==child[node])continue;
        dfs2(v,v);
    }
}
void build(ll n)
{
    for(ll i=0;i<n;i++)
    {
        tr[i+n]=a[i+1];
    }
    for(ll i=n-1;i>0;i--)
    {
        tr[i]=tr[i<<1]+tr[i<<1|1];
    }
}
void update(ll n, ll pos, ll v)
{
    pos+=n;
    for(tr[pos]=v,pos>>=1;pos>0;pos>>=1)
    {
        tr[pos]=tr[pos<<1]+tr[pos<<1|1];
    }
}
ll query(ll n, ll x, ll y)
{
    y++;
    x+=n;y+=n;
    ll s=0;
    for(;x<y;x>>=1,y>>=1)
    {
        if(x&1) s+=tr[x++];
        if(y&1) s+=tr[--y];
    }
    return s;
}
ll HLD(ll u, ll v)
{
    ll p = top[u], q = top[v];
    ll ans = 0;
    while( p != q )
    {
        if(dep[p] < dep[q])
        {
            swap(p,q);
            swap(u,v);
        }
        ans+=query(num,position[p]-1,position[u]-1);
        u = par[p];
        p = top[u];
    }
    if(dep[u] > dep[v])swap(u,v);
    ans+=query(num,position[u]-1,position[v]-1);
    return ans;
}
int main()
{
    ll i,j,k,p,q,m,n,tc,t=1,qry;
    scanf("%lld",&tc);
    while(tc--)
    {
        scanf("%lld",&n);
        for(i=1;i<=n;i++)
        {
            scanf("%lld",&b[i]);
        }
        memset(head,-1,sizeof head);
        id = num = 0;
        for(i=1;i<n;i++)
        {
            scanf("%lld %lld",&p,&q);
            add_edge(p+1,q+1);
        }
        dfs1(1,0,0);
        dfs2(1,1);
        for(i=1;i<=n;i++)
        {
            a[position[i]] = b[i];
        }
        build(num);
        scanf("%lld",&qry);
        printf("Case %lld:\n",t++);
        while(qry--)
        {
            scanf("%lld %lld %lld",&k,&p,&q);
            if(k==0)
            {
                m = HLD(p+1, q+1);
                printf("%lld\n",m);
            }
            else
            {
                update(num,position[p+1]-1,q);
            }
        }
    }
    return 0;
}
