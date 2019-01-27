///Hakerearth - SPECIAL PAIRS
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[1000005],fr[2000005],dp[21][(1<<20)+2];
ll call(ll pos, ll mask)
{
    //if(mask>1000000) return 0LL;
    if(pos==20)return fr[mask];
    ll &ret = dp[pos][mask];
    if(~ret) return ret;
    ret = 0;
    if(mask&(1<<pos))
    {
        ret+=call(pos+1, mask^(1<<pos));
    }
    else
    {
        ret+=call(pos+1, mask);
        ret+=call(pos+1, mask^(1<<pos));
    }
    return ret;
}
int main()
{
    ll i,j,k,p,q,m,n,tc,sm;
    cin >> tc;
    while(tc--)
    {
        cin >> n;
        memset(fr,0,sizeof fr);
        for(i=1;i<=n;i++)
        {
            cin >> a[i];
            fr[a[i]]++;
        }
        memset(dp,-1,sizeof dp);
        sm = 0;
        for(i=1;i<=n;i++)
        {
            sm+=call(0,a[i]);
        }
        cout << sm << endl;
    }
    return 0;
}
