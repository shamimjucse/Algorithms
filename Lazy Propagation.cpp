#include"bits/stdc++.h"
#define ll long long
#define MX 100000
using namespace std;
ll tr[3*MX+2],lazy[3*MX+2],a[MX+2];
void build(ll pos, ll st, ll ed)
{
    if(st==ed)
    {
        tr[pos]=a[st];
        return;
    }
    ll mid = st+((ed-st)>>1);
    build(pos<<1,st,mid);
    build(pos<<1|1,mid+1,ed);
    tr[pos]=tr[pos<<1]+tr[pos<<1|1];
}
void propagate(ll pos, ll st,ll ed)
{
    tr[pos]+=(ed-st+1)*lazy[pos];
    if(st!=ed)
    {
        lazy[2*pos]+=lazy[pos];
        lazy[2*pos+1]+=lazy[pos];
    }
    lazy[pos]=0;
}
void range_update(ll pos,ll st,ll ed,ll l,ll r,ll val)
{
    if(lazy[pos]!=0)propagate(pos,st,ed);
    if(st>r || ed<l)return;
    if(st>=l && ed<=r)
    {
        tr[pos]+=(ed-st+1)*val;
        if(st!=ed)
        {
            lazy[2*pos]+=val;
            lazy[2*pos+1]+=val;
        }
        return;
    }
    ll mid = st+((ed-st)>>1);
    range_update(pos<<1,st,mid,l,r,val);
    range_update(pos<<1|1,mid+1,ed,l,r,val);
    tr[pos]=tr[pos<<1]+tr[pos<<1|1];
}
ll range_query(ll pos,ll st,ll ed,ll l,ll r)
{
    if(st>r || ed<l)return 0;
    if(lazy[pos]!=0)propagate(pos,st,ed);
    if(st>=l && ed<=r)
    {
        return tr[pos];
    }
    ll mid = st+((ed-st)>>1);
    ll q1 = range_query(pos<<1,st,mid,l,r);
    ll q2 = range_query(pos<<1|1,mid+1,ed,l,r);
    return (q1+q2);
}
int main()
{
    ll i,j,k,p,q,n,tc,m,val;
    scanf("%lld",&tc);
    while(tc--)
    {
        scanf("%lld %lld",&n,&m);
        memset(a,0,sizeof a);
        memset(lazy,0,sizeof lazy);
        memset(tr,0,sizeof tr);
        for(i=1;i<=m;i++)
        {
            scanf("%lld %lld %lld",&k,&p,&q);
            if(k==0)
            {
                scanf("%lld",&val);
                range_update(1,1,n,p,q,val);
            }
            else
            {
                val=range_query(1,1,n,p,q);
                printf("%lld\n",val);
            }
        }
    }
    return 0;
}

