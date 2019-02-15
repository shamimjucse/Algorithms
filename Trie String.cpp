///Remember the Word (UVALive - 3942)
#include<bits/stdc++.h>
#define ll long long
#define mod 20071027LL
using namespace std;
ll trie[400002][28],last[400002],a[400005],tim;
string s,s2;
void add()
{
    ll r = 0;
    for(ll i=0;i<s2.size();i++)
    {
        if(trie[r][s2[i]-'a']==0)
            trie[r][s2[i]-'a']=++tim;
        r = trie[r][s2[i]-'a'];
    }
    last[r] = 1;
}
void query(ll i, ll v)
{
    ll r = 0;
    for(;i<s.size();i++)
    {
        r = trie[r][s[i]-'a'];
        if(r==0)return;
        if(last[r])
        {
            a[i]=(a[i]+v)%mod;
        }
    }
}
int main()
{
    ll i,j,k,p,q,m,n,t=1,cs=0;
    while(cin >> s)
    {
        tim = 0;
        memset(trie,0,sizeof trie);
        memset(last,0,sizeof last);
        memset(a,0,sizeof a);
        cin >> n;
        for(i=1;i<=n;i++)
        {
            cin >> s2;
            add();
        }
        a[0]=1;
        s="*"+s;
        for(i=1;i<s.size();i++)
        {
            if(a[i-1])query(i,a[i-1]);
        }
        cout << "Case "<<t++<<": ";
        cout << a[s.size()-1] << endl;
    }
    return 0;
}
