///UVA-1163 Solution
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll par[200005];
struct data
{
    ll u,v,cost;
    bool friend operator<(data x, data y)
    {
        if(x.cost<y.cost)
        {
            return true;
        }
        else
            return false;
    }
};
ll findd(ll u)
{
    if(par[u]==u)
        return u;
    else
        par[u]=findd(par[u]);
    return par[u];
}
data a[200005];
int main()
{
    ll tc,t=1,i,j,k,p,q,n,m,sm,kl;
    while(cin >> m >> n)
    {
        if(m==0&&n==0)
            break;
        sm=0;
        par[0]=0;
        for(i=1; i<=n; i++)
        {
            cin >> a[i].u >> a[i].v >> a[i].cost;
            sm+=a[i].cost;
            par[i]=i;
        }
        sort(a+1,a+1+n);
        ll sum=0,cnt=0;
        for(i=1; i<=n; i++)
        {
            ll f_u=findd(a[i].u);
            ll f_v=findd(a[i].v);
            if(f_u!=f_v)
            {
                par[f_u]=f_v;
                sum+=a[i].cost;
                cnt++;
                if(cnt==m-1)
                    break;
            }
        }
        cout << sm-sum << endl;
    }
    return 0;
}

