///Hakerearth - SPECIAL PAIRS
#include<bits/stdc++.h>
using namespace std;
const int N = 20;
int a[100005],ans[2000005],fr[1000005],dp[(1<<N)+2][N+2];
int main()
{
    int i,j,k,p,q,m,n,tc;
    cin >> tc;
    while(tc--)
    {
        cin >> n;
        memset(fr,0,sizeof fr);
        for(i=1; i<=n; i++)
        {
            cin >> p;
            fr[p]++;
            a[i]=(1<<N)-1-p;
        }
        for(int mask=0;mask<(1<<N);mask++)
        {
            dp[mask][0] = fr[mask];
            if(mask&1) dp[mask][0]+=fr[mask^1];
            for(i=1;i<=N;i++)
            {
                if(mask&(1<<i))
                    dp[mask][i]=dp[mask][i-1]+dp[mask^(1<<i)][i-1];
                else
                    dp[mask][i]=dp[mask][i-1];
            }
        }
        int sm = 0;
        for(i=1; i<=n; i++)
        {
            sm+=dp[a[i]][N];
        }
        cout << sm << endl;
    }
    return 0;
}
