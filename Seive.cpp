// Light OJ - 1197
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int mx = 50000;
vector<ll>pr;
bitset<mx+2>vis;
void seive()
{
    vis[0]=vis[1]=1;
    for(int i=4;i<=mx;i+=2)vis[i]=1;
    for(int i=3;i*i<=mx;i+=2)
    {
        if(!vis[i])
        {
            for(int j=i*i;j<=mx;j+=i+i)
            {
                vis[j] = 1;
            }
        }
    }
    pr.push_back(2);
    for(int i=3;i<=mx;i+=2)if(!vis[i])pr.push_back(i);
}
bool prime(ll n)
{
    if(n==1)return 0;
    else if(n==2)return 1;
    else if(n%2==0)return 0;
    else for(int i=1;i<pr.size() && pr[i]*pr[i]<=n;i++)if(n%pr[i]==0)return 0;
    return 1;
}
ll segmentseive(ll l, ll r)
{
    bool ck[r-l+2];
    for(int i=0;i<=r-l;i++)ck[i] = 0;
    if(l==1)ck[0] = 1;
    for(int i=0;i<pr.size() && pr[i]*pr[i]<=r;i++)
    {
        ll st = pr[i] * ((l/pr[i])+(l%pr[i]!=0));
        if(st==pr[i])st+=pr[i];
        for(ll j=st;j<=r;j+=pr[i])ck[j-l] = 1;
    }
    ll res = 0;
    for(int i=0;i<=r-l;i++)if(!ck[i])res++;
    return res;
}
int main()
{
    seive();
    //cout << pr.size() << endl;
    int tc,t=1;
    scanf("%d",&tc);
    while(tc--)
    {
        ll l,r;
        scanf("%lld %lld",&l,&r);
        ll sm = segmentseive(l,r);
        printf("Case %d: %lld\n",t++,sm);
    }
    return 0;
}

/********************************************************/

/**
    Linear Sieve / Sieve of Eratosthenes
    Complexity: O(n)
*/
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1000'005;
vector<int>prime;
bool is_composite[maxn];

void sieve(int n = 1000'000)
{
    for(int i=2; i<=n; i++)
    {
        if(!is_composite[i])
            prime.push_back(i);
        for(int j=0; j<prime.size() && i*prime[j]<=n; j++)
        {
            is_composite[i*prime[j]] = 1;
            if(i%prime[j] == 0)
                break;
        }
    }
}

int lp[maxn];
vector<int> pr;
void sieve2(int n = 1000'000)
{
    for (int i=2; i<=n; ++i)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back (i);
        }
        for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=n; ++j)
        {
            lp[i * pr[j]] = pr[j];
        }
    }
}
int main()
{
    sieve();
    cout << prime.size() << endl; /// 78498
    sieve2();
    cout << pr.size() << endl;
    return 0;
}
