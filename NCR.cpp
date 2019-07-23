///nCr = n!/(r!(n-r!))
/******************************/
const int N = 1000;
ll ncr[N+2][N+2];
void precall_NCR()
{
    ncr[0][0]=1;
    for(int i=1; i<=N; i++)
    {
        ncr[i][0]=1;
        for(int j=1; j<=i; j++)
        {
            ncr[i][j]=(ncr[i-1][j] + ncr[i-1][j-1])%mod;
        }
    }
}
/******************************/
ll NCR(ll n, ll r)
{
    if(n<0)return 0;
    if(n<r)return 0;
    ll ret=1;
    for(ll i=n;i>n-r;i--)
        ret=(ret*i) % MOD;
    return (ret*mod_inverse[r]) % MOD;
}
/******************************/
ll ncr(ll n, ll r)
{
    if(n<0 || n<r)return 0;
    ll p = fact[n];
    p=(p*bigMod(fact[r],mod-2,mod))%mod;
    p=(p*bigMod(fact[n-r],mod-2,mod))%mod;
    return p;
}
/******************************/
///Large n,r small prime modulo
inline ll factorial(int k,int p)
{
    ll ans=1;
    for(int i=2; i<=k; i++)
        ans=(ans*i)%p;///if p is constant , precal this function
    return ans;
}
pair<ll,ll> sep(ll n,int p)
{
    /**	let n!=a*(p^k) such a%p!=0 then this function
    return {a%p,k}p is prime*/
    ll k=n/p;
    if(k<p)
    {
        ll ans = (k&1) ? ((p-1)*factorial(n%p,p) % p)*factorial(k,p) %p : factorial(n%p,p)*factorial(k,p)%p;
        return {ans, k};
    }
    else
    {
        pair<ll, ll> w = sep(k,p);
        ll ans = (k&1) ? ((p-1)*factorial(n%p,p) % p)*w.xx %p : factorial(n%p,p)*w.xx %p;
        return {ans, k + w.yy};
    }
}
ll ncr(ll n,ll r,int p) //p is prime [small/iterable ]
{
    pair<ll,ll> a = sep(n,p);
    pair<ll,ll> b = sep(r,p);
    pair<ll,ll> c = sep(n-r,p);
    if(a.yy-b.yy-c.yy)
        return 0;
    return a.xx*pow(b.xx*c.xx%p,p-2,p) % p;
}
/******************************/
///Non-prime constant moduli:
ll k[20][MX];
ll f[MX];
const ll moduli = 521254688;
int phi;
vector<int> prime;
void pre(int N) //N is largest input
{
    int n=moduli;
    phi=moduli;
    for(int i=2; i*i<=n; i++)
    {
        if(n%i==0)
        {
            while(n%i==0)
                n/=i;
            prime.pb(i);
            phi-=phi/i;
        }
    }
    if(n>1)
    {
        phi-=phi/n;
        prime.pb(n);
    }
    f[0]=1;
    for(int j=1; j<=N; j++)
    {
        int n=j;
        for(int i=0; i<SZ(prime); i++)
        {
            k[i][j]=k[i][j-1];
            while(n%prime[i]==0)
            {
                k[i][j]++;
                n/=prime[i];
            }
        }
        f[j]=(f[j-1]*n)%moduli;
    }
}
int ncr(int n,int r)
{
    ll ans = f[n]*pow( (f[r]*f[n-r])%moduli,phi-1,moduli) %moduli;
    for(int i=0; i<SZ(prime); i++)
    {
        ans*=pow(prime[i],k[i][n]-k[i][r]-k[i][n-r],moduli);
        ans%=moduli;
    }
    return ans;
}
/******************************************* 20/15 NCR Table **************************************************/

     0      0      0      0      0      0      0      0      0      0      0      0      0      0      0      0
     1      1      0      0      0      0      0      0      0      0      0      0      0      0      0      0
     1      2      1      0      0      0      0      0      0      0      0      0      0      0      0      0
     1      3      3      1      0      0      0      0      0      0      0      0      0      0      0      0
     1      4      6      4      1      0      0      0      0      0      0      0      0      0      0      0
     1      5     10     10      5      1      0      0      0      0      0      0      0      0      0      0
     1      6     15     20     15      6      1      0      0      0      0      0      0      0      0      0
     1      7     21     35     35     21      7      1      0      0      0      0      0      0      0      0
     1      8     28     56     70     56     28      8      1      0      0      0      0      0      0      0
     1      9     36     84    126    126     84     36      9      1      0      0      0      0      0      0
     1     10     45    120    210    252    210    120     45     10      1      0      0      0      0      0
     1     11     55    165    330    462    462    330    165     55     11      1      0      0      0      0
     1     12     66    220    495    792    924    792    495    220     66     12      1      0      0      0
     1     13     78    286    715   1287   1716   1716   1287    715    286     78     13      1      0      0
     1     14     91    364   1001   2002   3003   3432   3003   2002   1001    364     91     14      1      0
     1     15    105    455   1365   3003   5005   6435   6435   5005   3003   1365    455    105     15      1
     1     16    120    560   1820   4368   8008  11440  12870  11440   8008   4368   1820    560    120     16
     1     17    136    680   2380   6188  12376  19448  24310  24310  19448  12376   6188   2380    680    136
     1     18    153    816   3060   8568  18564  31824  43758  48620  43758  31824  18564   8568   3060    816
     1     19    171    969   3876  11628  27132  50388  75582  92378  92378  75582  50388  27132  11628   3876
     1     20    190   1140   4845  15504  38760  77520 125970 167960 184756 167960 125970  77520  38760  15504
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
