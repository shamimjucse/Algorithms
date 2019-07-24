#include"bits/stdc++.h"
#define ll long long
using namespace std;
ll dis[11][11],dp[11][1<<11];
ll HamiltonianPath(ll n)
{
    ll i,j,k,mask,cnt,max_mask;
    for(i=0; i<n; i++)
    {
        dp[i][1<<i]=1;
    }
    max_mask = (1<<n)-1;
    for(mask=0; mask<=max_mask; mask++)
    {
        for(j=0; j<n; j++)
        {
            if(mask & (1<<j))
            {
                for(k=0; k<n; k++)
                {
                    if(k!=j && (mask&(1<<k)))
                    {
                        if(dis[j][k] && dp[k][mask^(1<<j)])
                        {
                            dp[j][mask]+=dp[k][mask^(1<<j)];
                            ///dp[j][mask]=1; break;
                        }
                    }
                }
            }
        }
    }
    cnt = 0;
    for(i=0; i<n; i++)
    {
        cnt+=dp[i][max_mask];
    }
    return cnt;
}
int main()
{
    ll i,j,m,n,p,q,tc;
    cin >> tc;
    while(tc--)
    {
        cin >> n >> m;
        for(i=1; i<=m; i++)
        {
            cin >> p >> q;
            p--,q--;
            dis[p][q]=dis[q][p]=1;
        }

        p = HamiltonianPath(n);
        p==0?cout<<"No"<<endl:cout<<"Yes"<<endl;

        memset(dp,0,sizeof dp);
        memset(dis,0,sizeof dis);
    }
    return 0;
}
