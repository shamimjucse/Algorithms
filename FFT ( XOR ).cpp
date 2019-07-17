//https://csacademy.com/contest/archive/task/random_nim_generator/
#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll mod = 30011;
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
void FFT_XOR(vector<ll> &P, bool inv)
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
                P[i+j] = (u + v)%mod;
                P[i+len+j] = (u-v)%mod;
            }
        }
    }
    if(inv)
    {
        ll Inv = BigMod(n,mod-2,mod);
        for(int i=0; i<n; i++)
        {
            //P[i]=(P[i]*Mod_Inverse[n%mod])%mod; /// P[i] = P[i]/n
            P[i]=(P[i]*Inv)%mod;
        }
    }
}
vector<ll> multiply(vector<ll> a,vector<ll> b)
{
    size_t n = 1;
    while(n < max(a.size(), b.size()))
        n <<= 1;
    n <<= 1;
    a.resize(n), b.resize(n);
    FFT_XOR(a,false), FFT_XOR(b,false);
    for(size_t i=0; i<n; i++)
        a[i]*=b[i], a[i]%=mod;
    FFT_XOR(a,true);
    for(size_t i=0; i<n; i++)
    {
        if(a[i]<0)
            a[i]+=mod;
    }
    return a;
}
int main()
{
    int n,k;
    cin >> n >> k;
    int N;
    while(N < k)
        N<<=1;
    N<<=1;
    vector<ll> ans(k+1,1);
    ans.resize(N);
    FFT_XOR(ans,0);
    for(int i=0; i<N; i++)
        ans[i] = BigMod(ans[i],n,mod);
    FFT_XOR(ans,1);
    for(int i=0; i<N; i++)
        if(ans[i] < 0)
            ans[i]+=mod;

    cout<< accumulate(ans.begin() + 1, ans.end(), 0LL) % mod <<endl;
    return 0;
}
