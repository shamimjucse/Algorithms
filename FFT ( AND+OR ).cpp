///https://csacademy.com/contest/archive/task/and-closure/statement/
#include<bits/stdc++.h>
#define ll long long
using namespace std;
//ll mod = 1000000007;
ll mod = 5767169;
ll BigMod(ll a,ll b,ll m)
{
    ll ans=1;
    a=a%m;
    while(b)
    {
        if(b&1)
            ans=(ans*a)%m;
        a=(a*a)%m;
        b/=2;
    }
    return ans;
}
void FFT_AND(vector<ll>&P, bool inv)
{
    int n=(int)P.size();
    for(int len=1; 2*len<=n; len<<=1)
    {
        for(int i=0; i<n; i+=2*len)
        {
            for(int j=0; j<len; j++)
            {
                ll u = P[i+j];
                ll v = P[i+len+j];
                if(!inv)
                {
                    P[i+j] = v;
                    P[i+len+j] = (u+v)%mod;
                }
                else
                {
                    P[i+j] = (-u+v)%mod;
                    P[i+len+j] = u;
                }
            }
        }
    }
}
vector<ll> Mul_AND(vector<ll> a,vector<ll> b)
{
    size_t n = 1;
    while(n < max(a.size(),b.size()))
        n <<= 1;
    n <<= 1;
    a.resize(n), b.resize(n);
    FFT_AND(a,false), FFT_AND(b,false);
    for(size_t i=0; i<n; i++)
        a[i]*=b[i], a[i]%=mod;
    FFT_AND(a,true);
    for(size_t i=0; i<n; i++)
    {
        if(a[i]<0)
            a[i]+=mod;
    }
    return a;
}
void FFT_OR(vector<ll> &P, bool inv)
{
    int n=(int)P.size();
    for(int len=1; 2*len<=n; len<<=1)
    {
        for(int i=0; i<n; i+=2*len)
        {
            for(int j=0; j<len; j++)
            {
                ll u = P[i+j];
                ll v = P[i+len+j];
                if(!inv)
                {
                    P[i+j] = (u+v)%mod;
                    P[i+len+j] = u ;
                }
                else
                {
                    P[i+j] = v;
                    P[i+len+j] = (u-v)%mod;
                }
            }
        }
    }
}
vector<ll> Mul_OR(vector<ll> a,vector<ll> b)
{
    size_t n = 1;
    while(n < max(a.size(), b.size()))
        n <<= 1;
    n <<= 1;
    a.resize(n), b.resize(n);
    FFT_OR(a,false), FFT_OR(b,false);
    for(size_t i=0; i<n; i++)
        a[i]*=b[i], a[i]%=mod;
    FFT_OR(a,true);
    for(size_t i=0; i<n; i++)
    {
        if(a[i]<0)
            a[i]+=mod;
    }
    return a;
}
int main()
{
    int n;
    cin >> n;
    vector<ll>v(1<<20);
    for(int i=1;i<=n;i++)
    {
        int m;
        cin >> m;
        v[m]=1;
    }
    FFT_AND(v,0);
    for(auto &u : v)
        u = BigMod(u,n,mod);
    FFT_AND(v,1);
    int ans = 1;
    for(int i=1;i<(1<<20);i++)
        ans+=(v[i]!=0);
    cout << ans << endl;
    return 0;
}
