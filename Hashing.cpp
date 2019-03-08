#include<bits/stdc++.h>
#define ll long long
using namespace std;
///Base : 131,293,1193,3037,100006981,100602179
///Mod : 1000000007,1000000009,1000000241,1000000579
///Mod : 1000003891,1050006697,1550006357,1950006859
///Mod : 2000006321,2008005653,2038006843,2138005801

#define b1 31LL
#define b2 113LL
#define mod1 999951475219LL
#define mod2 999999991513LL

string s;
map<ll,ll>mp1,mp2;
ll B1[1000005],B2[1000005],H1[1000005],H2[1000005],len;

void CalculateBase(ll n)
{
    B1[0]=1,B2[0]=1;
    for(ll i=1;i<=n;i++)
    {
        B1[i] = (B1[i-1]*b1)%mod1;
        B2[i] = (B2[i-1]*b2)%mod2;
    }
}
pair<ll,ll> HashValue(ll l, ll r)
{
    ll v1 = ((H1[r]-B1[r-l+1]*H1[l-1])%mod1+mod1)%mod1;
    ll v2 = ((H2[r]-B2[r-l+1]*H2[l-1])%mod2+mod2)%mod2;
    return {v1,v2};
}
void add(char ch)
{
    s+=ch;
    H1[len+1]=(((H1[len]*b1)%mod1)+(s[len]-'A'+1))%mod1;
    H2[len+1]=(((H2[len]*b2)%mod2)+(s[len]-'A'+1))%mod2;
    len = len+1;
}

///All are 1 indexing
int main()
{
    ll i,j,tc,p,q;
    pair<ll,ll>pr;
    char ch;
    cin >> tc;
    CalculateBase(1000000);
    while(tc--)
    {
        cin >> s;
        len = s.size();
        for(i=0;i<len;i++)
        {
            H1[i+1]=(((H1[i]*b1)%mod1)+(s[i]-'A'+1))%mod1;
            H2[i+1]=(((H2[i]*b2)%mod2)+(s[i]-'A'+1))%mod2;
        }

        ///solution part
        ///add(ch);
        ///pr = HashValue(p,q);

        mp1.clear();mp2.clear();
    }
    return 0;
}
