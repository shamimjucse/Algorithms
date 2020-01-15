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

/*-----------------------------------------------------------------------*/
///Light oj - 1264
#include<bits/stdc++.h>
using namespace std;

int a[14][14],cst[(1<<14)+5];
int main()
{
    int tc,t=1; cin >> tc;
    while(tc--)
    {
        int n; cin >> n;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cin >> a[i][j];
            }
        }
        for(int mask=0;mask<(1<<n);mask++)
        {
            cst[mask] = 0;
            for(int i=0;i<n;i++)
            {
                if(mask&(1<<i))
                {
                    for(int j=0;j<n;j++)
                    {
                        if(mask&(1<<j))
                        {
                            cst[mask]+=a[i][j];
                        }
                    }
                }
            }
        }
        for(int mask=0;mask<(1<<n);mask++)
        {
            for(int sub=mask;sub>0;sub=mask&(sub-1))
            {
                cst[mask] = min(cst[mask], cst[sub]+cst[mask^sub]);
            }
        }
        cout << "Case " << t++ << ": " << cst[(1<<n)-1] << "\n";
    }
    return 0;
}
