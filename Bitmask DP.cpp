#include"bits/stdc++.h"
#define ll long long
using namespace std;
ll a[17][17],dp[17][(1<<17)+2],n;
ll Bitmask_dp(ll row, ll mask)
{
    if(row>n) return 0;
    ll &ret = dp[row][mask];
    if(~ret) return ret;
    ret=0;
    for(ll i=1;i<=n;i++)
    {
        if((mask & (1<<i))==0)
        {
            ll p = mask | (1<<i);
            ret=max(ret,a[row][i]+Bitmask_dp(row+1,p));
        }
    }
    return ret;
}
int main()
{
    ll i,j,k,tc,t=1;
    cin >> tc;
    while(tc--)
    {
        cin >> n;
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=n;j++)
            {
                cin >> a[i][j];
            }
        }
        memset(dp,-1,sizeof dp);
        k=Bitmask_dp(1,1);
        cout << "Case " << t++ << ": " << k << endl;
    }
    return 0;
}

