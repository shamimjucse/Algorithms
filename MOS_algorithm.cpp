///Light oj - 1188
#include<bits/stdc++.h>
#define ll long long
using namespace std;
#define MX 1000005
ll a[MX],ans[MX],num[MX];
struct mos
{
    ll st,ed,id,sqr;
    bool operator<(const mos &A) const
    {
        return (sqr < A.sqr)||(sqr==A.sqr&&ed<A.ed);
    }
} mo[MX+2];
int main()
{
    ll i,j,n,l,r,p,qry,sq,sm,tc,t=1;
    scanf("%lld",&tc);
    while(tc--)
    {
        scanf("%lld %lld",&n,&qry);
        for(i=1; i<=n; i++)
        {
            scanf("%lld",&p);
            a[i]=p+1;///AS a[0]=0
        }
        sq=sqrt((double)n);
        for(i=1; i<=qry; i++)
        {
            scanf("%lld %lld",&l,&r);
            mo[i].st=l;
            mo[i].ed=r;
            mo[i].id=i;
            mo[i].sqr=(l/sq)+(l%sq!=0);
        }
        sort(mo+1,mo+1+qry);
        ll left=0,right=0;
        sm=0;
        memset(num,0,sizeof num);
        for(i=1; i<=qry; i++)
        {
            l=mo[i].st;
            r=mo[i].ed;
            while(left<l)
            {
                num[a[left]]--;
                if(!num[a[left]]) sm--;
                left++;
            }
            while(left>l)
            {
                left--;
                if(!num[a[left]]) sm++;
                num[a[left]]++;
            }
            while(right<r)
            {
                right++;
                if(!num[a[right]]) sm++;
                num[a[right]]++;
            }
            while(right>r)
            {
                num[a[right]]--;
                if(!num[a[right]]) sm--;
                right--;
            }
            ans[mo[i].id]=sm;
        }
        printf("Case %lld:\n",t++);
        for(i=1; i<=qry; i++)
        {
            printf("%lld\n",ans[i]);
        }
    }
    return 0;
}
