///Light oj - 1266
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[1005][1005],bit[1005][1005],_n;
void update(ll x, ll y, ll val)
{
    for(ll i=x; i<=_n; i+=(i&(-i)))
    {
        for(ll j=y; j<=_n; j+=(j&(-j)))
        {
            bit[i][j]+=val;
        }
    }
}
ll query(ll x, ll y)
{
    ll sm = 0;
    for(ll i=x; i>0; i-=(i&(-i)))
    {
        for(ll j=y; j>0; j-=(j&(-j)))
        {
            sm+=bit[i][j];
        }
    }
    return sm;
}
int main()
{
    ll i,j,n,tc,t=1,x1,x2,y1,y2,p,q;
    scanf("%lld",&tc);
    while(tc--)
    {
        memset(a,0,sizeof a);
        memset(bit,0,sizeof bit);
        _n=1002;///max index

        scanf("%lld",&n);
        printf("Case %lld:\n",t++);
        for(i=1; i<=n; i++)
        {
            scanf("%lld",&q);
            if(q)
            {
                scanf("%lld %lld %lld %lld",&x1,&y1,&x2,&y2);
                x1++,y1++,x2++,y2++;
                p = query(x2,y2)-query(x1-1,y2)-query(x2,y1-1)+query(x1-1,y1-1);
                printf("%lld\n",p);
            }
            else
            {
                scanf("%lld %lld",&x1,&y1);
                x1++,y1++;
                if(!a[x1][y1])
                {
                    a[x1][y1]=1;
                    update(x1,y1,1);
                }
            }
        }
    }
    return 0;
}

