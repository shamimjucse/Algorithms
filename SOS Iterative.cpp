///Hakerearth - SPECIAL PAIRS
#include<bits/stdc++.h>
using namespace std;
const int N = 20;
int a[100005],ans[(1<<N)+2],fr[(1<<N)+2],dp[(1<<N)+2][N+2];
int main()
{
    int n,tc;
    cin >> tc;
    while(tc--)
    {
        cin >> n;
        memset(fr,0,sizeof fr);
        for(int i=1; i<=n; i++)
        {
            int p;
            cin >> p;
            /// For submask solution
            fr[p]++;
            /// For supermask solution
            //fr[(1<<N)-1-p]++;
            ///a[i] = p^((1<<N)-1),opposite bit is on
            a[i]=(1<<N)-1-p;
        }

        /***************************************************/
        //Process -1
        for(int mask=0;mask<(1<<N);mask++)
        {
            dp[mask][0] = fr[mask];
            if(mask&1) dp[mask][0]+=fr[mask^1];
            for(int i=1;i<N;i++)
            {
                if(mask&(1<<i))
                    dp[mask][i]=dp[mask][i-1]+dp[mask^(1<<i)][i-1];
                else
                    dp[mask][i]=dp[mask][i-1];
            }
            ans[mask] = dp[mask][N-1];
        }

        /***************************************************/
        //Process - 2
        for(int i = 0; i < N; ++i)
        {
            for(int mask = 0; mask < (1<<N); ++mask)
            {
                if(mask & (1<<i))
                {
                    fr[mask] += fr[mask^(1<<i)];
                }
                ans[mask] = fr[mask];
            }
        }

        /***************************************************/

        int sm = 0;
        for(int i=1; i<=n; i++)
        {
            //ans will always taken from reverse bit
            sm+=ans[a[i]];
        }
        cout << sm << endl;
    }
    return 0;
}
/*
For getting submask solution, we need to increase the frequency of value,
for getting supermask solution, we need to increase the frequency of value^((1<<N)-1),
But for both cases we need to collect solution from need_value^((1<<N)-1).
*/

