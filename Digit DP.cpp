///https://codeforces.com/contest/1036/problem/C
#include<bits/stdc++.h>
#define ll long long
using namespace std;
string s;
ll dp[20][5][2];
void getstring(ll n)
{
    s = "";
    while(n>0)
    {
        s+=(n%10+'0');
        n/=10;
    }
    reverse(s.begin(),s.end());
}
ll digit(ll pos, ll cnt, ll flg)
{
    if(cnt>3)return 0;
    if(pos == s.size())return 1;
    ll &ret = dp[pos][cnt][flg];
    if(~ret) return ret;
    ret = 0;
    if(flg)
    {
        for(ll i=0;i<10;i++)
        {
            ret+=digit(pos+1,i?cnt+1:cnt,flg);
        }
    }
    else
    {
        for(ll i = 0;i<s[pos]-'0';i++)
        {
            ret+=digit(pos+1,i?cnt+1:cnt,1);
        }
        ret+=digit(pos+1,(s[pos]-'0')?cnt+1:cnt,flg);
    }
    return ret;
}
int main()
{
    ll i,j,l,r,n,m,tc,sm;
    cin >> tc;
    while(tc--)
    {
        cin >> l >> r;
        memset(dp,-1,sizeof dp);
        getstring(r);
        sm=digit(0,0,0);
        memset(dp,-1,sizeof dp);
        getstring(l-1);
        sm-=digit(0,0,0);
        cout << sm << endl;
    }
    return 0;
}
