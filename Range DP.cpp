///https://codeforces.com/contest/1178/problem/F1
#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
using namespace std;

ll dp[502][502];
int a[502];
ll call(ll st, ll ed)
{
    if(st==ed)
        return 1;
    if(st==ed+1)
        return 1;
    ll &ret=dp[st][ed];
    if(~ret)
        return ret;
    int mn = st;
    for(int i=st+1; i<=ed; i++)
        if(a[mn]>a[i])
            mn=i;
    ll l = 0, r = 0;
    for(int k=st-1; k<mn; k++)
        (l+=call(st,k)*call(k+1,mn-1)%mod)%=mod;
    for(int k=mn; k<=ed; k++)
        (r+=call(mn+1,k)*call(k+1,ed)%mod)%=mod;
    ret=(l*r)%mod;
    return ret;
}
int main()
{
    int i,j,k,m,n;
    cin >> n >> m;
    for(i=1; i<=m; i++)
        cin >> a[i];

    /*******************************/

    for(i=1; i<=m; i++)
        dp[i][i] = dp[i][i-1] = 1;
    dp[m+1][m] = 1;

    for(int length=2; length<=m; length++)
    {
        for(int st=1,ed=length; ed<=m; st++,ed++)
        {
            int mn = st;
            for(i=st+1; i<=ed; i++)
            {
                if(a[mn]>a[i])
                    mn=i;
            }
            ll lsm=0,rsm=0;
            for(k=st-1; k<mn ; k++)
            {
                (lsm+=dp[st][k]*dp[k+1][mn-1]%mod)%=mod;
            }
            for(k=mn; k<=ed; k++)
            {
                (rsm+=dp[mn+1][k]*dp[k+1][ed]%mod)%=mod;
            }
            dp[st][ed]=lsm*rsm%mod;
        }
    }
    cout << dp[1][m] << endl;

    /*******************************/

    memset(dp,-1,sizeof dp);
    cout << call(1,m) << endl;


    return 0;
}
