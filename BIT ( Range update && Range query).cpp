///Light oj -1164
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll bit1[200005],bit2[200005],n;
ll update(ll ar[], ll i, ll val)
{
    while(i<=n)
    {
        ar[i]+=val;
        i+=(i&(-i));
    }
}
ll qry(ll ar[], ll i)
{
    ll ans=0;
    while(i>0)
    {
        ans+=ar[i];
        i-=(i&(-i));
    }
    return ans;
}
ll quary(ll p)
{
    return qry(bit1,p)*p-qry(bit2,p);
}
int main()
{
    ll i,j,k,l,p,q,m,tc,t=1,val;
    scanf("%lld",&tc);
    while(tc--)
    {
        scanf("%lld%lld",&n,&m);
        memset(bit1,0,sizeof bit1);
        memset(bit2,0,sizeof bit2);
        printf("Case %lld:\n",t++);
        while(m--)
        {
            scanf("%lld",&l);
            if(l==0)
            {
                scanf("%lld%lld%lld",&p,&q,&val);
                p++,q++;
                update(bit1, p, val);
                update(bit1, q+1, -val);
                update(bit2, p, val*(p-1));
                update(bit2, q+1, -val*q);
            }
            else
            {
                scanf("%lld%lld",&p,&q);
                p++,q++;
                k=quary(q)-quary(p-1);
                printf("%lld\n",k);
            }
        }
    }
    return 0;
}
