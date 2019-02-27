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
void build(ll pos, ll st, ll ed)
{
    if(st==ed)
    {
        tr[pos]=a[st];
        return;
    }
    ll mid = st+((ed-st)>>1);
    build(2*pos,st,mid);
    build(2*pos+1,mid+1,ed);
    tr[pos]=tr[2*pos]+tr[2*pos+1];
}
void update(ll pos,ll st, ll ed, ll x, ll val)
{
    if(st==ed && st==x)
    {
        tr[pos]=val;
        return;
    }
    ll mid = st+((ed-st)>>1);
    if(x<=mid)update(2*pos,st,mid,x,val);
    else update(2*pos+1,mid+1,ed,x,val);
    tr[pos]=tr[2*pos]+tr[2*pos+1];
}
ll query(ll pos, ll st, ll ed, ll l, ll r)
{
    if(st>r||ed<l)return 0;
    if(st>=l && ed<=r)
    {
        return tr[pos];
    }
    ll mid = st+((ed-st)>>1);
    return query(2*pos,st,mid,l,r)+query(2*pos+1,mid+1,ed,l,r);
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
        ans+=query(1,1,num,position[p],position[u]);
        u = par[p];
        p = top[u];
    }
    if(dep[u] > dep[v])swap(u,v);
    ans+=query(1,1,num,position[u],position[v]);
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
        build(1,1,num);
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
                update(1,1,num,position[p+1],q);
            }
        }
    }
    return 0;
}
