///LightOJ - 1082
/*
* For Min Query only decreasing value for any index is acceptable
* For Max Query only increasing value for any index is acceptable
*/
#include<bits/stdc++.h>
using namespace std;
vector<int>v,lft,rgt;
int _n;
void Update(int r,int val)
{
    v[r-1]=val;
    int i=r;
    while(i<=_n)
    {
        lft[i]=min(lft[i],val);
        i+=(i&(-i));
    }
    i=r;
    while(i>0)
    {
        rgt[i]=min(rgt[i],val);
        i-=(i&(-i));
    }
}
int Query(int l,int r)
{
    int res = INT_MAX;
    int i=l;
    while(i+(i&(-i))<=r)
    {
        res=min(res,rgt[i]);
        i+=(i&(-i));
    }
    res=min(res,v[i-1]);
    i=r;
    while(i-(i&(-i))>=l)
    {
        res=min(res,lft[i]);
        i-=(i&(-i));
    }
    return res;
}
int main()
{
    int i,j,k,p,q,m,n,tc,t=1;
    scanf("%d",&tc);
    while(tc--)
    {
        scanf("%d %d",&n,&m);
        v.clear();
        for(i=0; i<n; i++)
        {
            scanf("%d",&p);
            v.push_back(p);
        }

        k = log(n)/log(2)+1;
        _n = pow(2.0,double(k));
        lft.clear(),rgt.clear();

        for(i=0; i<=_n; i++)
        {
            lft.push_back(INT_MAX);
            rgt.push_back(INT_MAX);
        }
        for(i=0; i<n; i++)
        {
            Update(i+1,v[i]);
        }

        printf("Case %d:\n",t++);
        while(m--)
        {
            scanf("%d %d",&p,&q);
            k = Query(p,q);
            printf("%d\n",k);
        }
    }
    return 0;
}
