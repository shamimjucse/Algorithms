/// https://codeforces.com/contest/1096/problem/G
#include<bits/stdc++.h>
#define ll long long
using namespace std;
/*
if bruteforce needed at some point,
consider eliminating zero frequency term
*/
template<class T>inline T pow(T a,T b,T m)
{
    a%=m;T ans=1%m;
    while(b){if(b&1)ans*=a,ans%=m; a*=a; a%=m; b>>=1;}
    return ans;
}

long long generator(long long p)
{
    vector<long long>fact;
    long long phi = p-1, n = phi;
    for(int i=2; i*i<=n; i++)
    {
        if(n%i==0)
        {
            fact.push_back(i);
            while(n%i==0)
                n/=i;
        }
    }
    if(n>1)
        fact.push_back(n);
    for(long long res=2; res<=p; res++)
    {
        bool ok = true;
        for(size_t i=0; i<fact.size()&&ok; i++)
            ok &= pow(res,phi/fact[i],p)!=1;
        if(ok)
            return res;
    }
    return -1;
}

long long MOD=998244353, ROOT=generator(MOD);
void NTT(vector<long long>&a, bool inv) //inv=true means inverse NTT
{
    int n=(int)a.size();
    for(int i=1,j=0; i<n; i++)
    {
        int bit=n>>1;
        for( ; j>=bit; bit>>=1)
            j-=bit ;
        j+=bit ;
        if(i<j)
            swap(a[i],a[j]);
    }
    for(int len=2; len<=n; len<<=1)
    {
        long long wlen=pow(ROOT,(MOD-1)/len,MOD); ///can be precalculated
        if(inv)
            wlen=pow(wlen,MOD-2,MOD); ///can be precalculated
        for(int i=0; i<n; i+=len)
        {
            long long w=1;
            for(int j=0; j<len/2; j++)
            {
                long long u = a[i+j];
                long long v = a[i+j+len/2]*w;
                v%=MOD;
                a[i+j] = (u + v)%MOD;
                a[i+j+len/2] = (u-v)%MOD ;
                w*=wlen ;
                w%=MOD;
            }
        }
    }
    if(inv)
    {
        long long MOD_INV_OF_N = pow(n*1LL,MOD-2,MOD); ///can be precalculated
        for(int i=0; i<n; i++)
            a[i]*=MOD_INV_OF_N, a[i]%=MOD;
    }
}

vector<long long> Mul(const vector<long long>&a, const vector<long long>&b)
{
    vector<long long>res;
    vector<long long> fa(a.begin(),a.end()), fb(b.begin(),b.end());
    ///Do bruteforce here if needed
    size_t n=1;
    while(n < max(a.size(),b.size()))
        n<<=1;
    n<<=1;
    fa.resize(n), fb.resize(n);
    NTT(fa,false), NTT(fb,false);
    for(size_t i=0; i<n; i++)
        fa[i]*=fb[i], fa[i]%=MOD;
    NTT(fa,true);
    res.resize(n);
    for(size_t i=0; i<n; i++)
    {
        res[i]=(long long)(fa[i]);
        if(res[i]<0)
            res[i]+=MOD;
    }
    return res;
    ///res[x] = number of pair(i,j) such a[i] + b[j] == x
}

vector<ll> power(vector<ll>&a, int p)
{
    vector<ll>res;
    res.push_back(1);
    while(p>0)
    {
        if(p&1) res=Mul(res,a);
        a=Mul(a,a);
        p>>=1;
    }
    return res;
}

int main()
{
    int n,k;
    cin >> n >> k;
    //vector<ll>A(10,0);
    vector<ll>A(1<<20);
    for(int i=1;i<=k;i++)
    {
        int m;
        cin >> m;
        A[m]=1;
    }
    //vector<ll>ans = power(A,n/2);
    NTT(A,0);
    for(ll &w : A)
        w = pow(w,n/2LL,MOD);
    NTT(A,1);

    ll sm = 0;
    for(auto x : A)
    {
        sm = (sm+(x*x)%MOD)%MOD;
    }
    cout << sm << endl;
    return 0;
}

/*
Polynomial Exponentiation :  First convert the polynomial into point-value space (fft) .
Calculate exponent of every individual element , then convert back to the sample space (inverse fft).
*/
