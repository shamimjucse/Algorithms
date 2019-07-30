///Hakerearth - SPECIAL PAIRS
#include<bits/stdc++.h>
using namespace std;

const int N = 20;/// 2^N > max value
int a[100005],ans[(1<<N)+2],fr[(1<<N)+2],dp[N][(1<<N)+2];

int call(int pos, int mask)
{
    if(pos<0)return fr[mask];

    int &ret = dp[pos][mask];
    if(~ret) return ret;
    ret = 0;
    if(mask & (1<<pos))
    {
        ret+=call(pos-1, mask);
        ret+=call(pos-1, mask^(1<<pos));
    }
    else
    {
        ret+=call(pos-1, mask);
    }
    return ret;
}
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
        //Process - 1
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
        //Process -2
        for(int mask=0;mask<(1<<N);mask++)
        {
            dp[0][mask] = fr[mask];
            if(mask&1) dp[0][mask]+=fr[mask^1];
            for(int i=1;i<N;i++)
            {
                if(mask&(1<<i))
                    dp[i][mask]=dp[i-1][mask]+dp[i-1][mask^(1<<i)];
                else
                    dp[i][mask]=dp[i-1][mask];
            }
            ans[mask] = dp[N-1][mask];
        }

        /***************************************************/
        //Process - 3
        memset(dp,-1,sizeof dp);
        for(int i=0;i<(1<<N);i++)
        {
            ans[i] = call(N-1,i);
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
