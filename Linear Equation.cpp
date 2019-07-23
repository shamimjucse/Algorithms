///Light OJ - 1124
#include<bits/stdc++.h>
#define MOD 100000007LL
#define mx 22
typedef long long ll;
using namespace std;
ll inv[mx];
ll bigmod(ll a,ll p)
{
    ll ret = 1;
    while(p > 0)
    {
        if(p&1)ret=(ret*a)%MOD;
        a = (a*a)%MOD;
        p/=2;
    }
    return ret;
}
ll ncr(ll n, ll r)
{
    if(n<0)return 0;
    if(n<r)return 0;
    ll ret=1;
    for(ll i=n;i>n-r;i--)
        ret=(ret*i) % MOD;
    return (ret*inv[r]) % MOD;
}
int main()
{
    inv[0]=1;
    for(ll i=1;i<21;i++)inv[i]=(inv[i-1]*bigmod(i,MOD-2)) % MOD;
    int t,tst=1;
    scanf("%d",&t);
    while(t--)
    {
        ll k,n;
        scanf("%lld %lld",&k,&n);
        ll ara[k];
        for(int i=0;i<k;i++)
        {
            ll a,b;
            scanf("%lld %lld",&a,&b);
            n-=a;
            ara[i]=b-a;
        }
        if(n<0)
        {
            printf("Case %d: 0\n",tst++);
            continue;
        }
        ll ans=0, lim=(1<<k);
        for(int bit=0;bit<lim;bit++)
        {
            ll sum = 0, cnt = 0;
            for(int j=0;j<k;j++)
            {
                if(bit & (1<<j))sum+=ara[j]+1,cnt++;
            }
            if(cnt&1)ans=(ans-ncr(n-sum+k-1,k-1)+MOD)%MOD;
            else ans=(ans+ncr(n-sum+k-1,k-1))%MOD;
        }
        printf("Case %d: %lld\n",tst++,ans);
    }
    return 0;
}
