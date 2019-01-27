#include"bits/stdc++.h"
#define ll long long
#define MX 100000
using namespace std;
ll tr[3*MX+2];
ll a[MX+2];
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
        tr[pos]=val%2;
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
int main()
{
    ll i,j,k,n,q,p,x,v;
    scanf("%lld",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%lld",&p);
        a[i]=p%2;
    }
    build(1,1,n);
    scanf("%lld",&q);
    while(q--)
    {
        scanf("%lld %lld %lld",&p,&x,&v);
        if(p==0)
        {
            update(1,1,n,x,v);
        }
        else if(p==1)
        {
            k=query(1,1,n,x,v);
            k=(v-x+1)-k;
            printf("%lld\n",k);
        }
        else
        {
            k=query(1,1,n,x,v);
            printf("%lld\n",k);
        }
    }
    return 0;
}

