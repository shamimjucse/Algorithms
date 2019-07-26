///https://www.spoj.com/problems/LKS
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll v[502],w[502],dp[2][2000002];
int main()
{
    ll i,j,k,m,n;
    cin >> k >> n;
    for(i=1;i<=n;i++)
    {
        cin >> v[i] >> w[i];
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=k;j++)
        {
            if(w[i]<=j)
            {
                dp[(i&1)][j]=max(dp[!(i&1)][j],v[i]+dp[!(i&1)][j-w[i]]);
            }
            else
            {
                dp[(i&1)][j] = dp[!(i&1)][j];
            }
        }
    }
    cout << dp[(n&1)][k] << endl;
    return 0;
}
