/*****************************/
///Big Mod
ll BigMod(ll a,ll b,ll m)//m means mod value
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
/*****************************/

///Mod Inverse
if m is prime :pow(a,m-2,m)
else pow(a,phi(m)-1,m)

/*****************************/
ll Mod_inv(ll a, ll m)
{
    return BigMod(a,m-2,m);
}
/*****************************/
void Mod_inv(int n, ll m)
{
    inv[1] = 1;
    for(int i = 2; i <= n; ++i)
        inv[i] = (m - (m/i) * inv[m%i] % m) % m;
}
/*****************************/

///a * x + b * y = 1
///a * x ≡ 1 mod m
cin >> a;
g = extended_euclidean(a, mod, x, y);
if (g != 1)
{
    cout << "No Inverse!" << endl;
}
else
{
    x = (x % mod + mod) % mod;
    cout << x << endl;
}
/*****************************/
