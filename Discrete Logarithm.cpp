///http://lightoj.com/volume_showproblem.php?problem=1325
#include<bits/stdc++.h>
#define ll long long
#define mod 100000007LL
using namespace std;
ll BigMod(ll a, ll b, ll m)
{
    ll ans = 1;
    a = a%m;
    while(b)
    {
        if(b&1)
            ans = (ans*a)%m;
        a = (a*a)%m;
        b/=2;
    }
    return ans;
}
ll discreteLog(ll a, ll b, ll m)///return x such a^x=b mod m
{
    ll l = sqrt((double)m);
    unordered_map<ll,ll>mp;
    mp[1] = 0;
    ll p = 1;
    for(int i=1;i<=l;i++)
    {
        p = (p*a)%m;
        mp[p] = i;
    }
    p = BigMod(p,m-2,m); //modular inverse
    ll q = b;
    for(int i=0;i*l<m;i++)
    {
        if(mp.count(q))
        {
            return l*i + mp[q];
        }
        q = (q*p)%m;
    }
}
int main()
{
    ll a,b,tc,t=1;
    cin >> tc;
    while(tc--)
    {
        cin >> a >> b;
        cout << "Case " << t++ << ": " << discreteLog(a,b,mod) << endl;
    }
    return 0;
}
