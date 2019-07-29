#include<bits/stdc++.h>
#define ll long long
#define mod 100019 //Small moduli
using namespace std;
ll inv[100022];
void mod_Inv()
{
    inv[1] = 1;
    for(int i=2; i<=mod; i++)
    {
        inv[i] = (mod-(mod/i)*inv[mod%i]%mod)%mod;
    }
}
///Takes point value , return coefficient vector in O(n^2)
vector<ll> dvand_mod( vector<ll> alpha, vector<ll>b)///Function( alpha[i] ) = b[i]
{
    int j,k,n = (int)alpha.size();
    vector<ll> x(b.begin(),b.end());
    for(k=0; k<n-1; k++)
    {
        for(j=n-1; k<j; j--)
        {
            x[j] = ((x[j]-x[j-1])*inv[(alpha[j]-alpha[j-k-1]+mod)%mod])%mod;//note the inv[x] = x^(-1) modulo mod
        }
    }
    for(k=n-2; 0<=k; k--)
    {
        for(j=k; j<n-1; j++)
        {
            x[j]=(x[j]-alpha[k]*x[j+1])%mod;
        }
    }
    for(int i=0; i<n; i++)
        if(x[i]<0)
            x[i]+=mod;
    return x; ///return n term polynomial ( n-1 order ), in reverse order : f(n) = 10 + 3x + 8x^2
}

///same as above , work on real number
vector<double> dvand_real(vector<double>alpha, vector<double>b)
{
    int j,k,n = (int)alpha.size();
    vector<double> x(b.begin(),b.end());
    for(k=0; k<n-1; k++)
    {
        for(j=n-1; k<j; j--)
        {
            x[j] = (x[j]-x[j-1])/(alpha[j]-alpha[j-k-1]);
        }
    }
    for(k=n-2; 0<=k; k--)
    {
        for(j=k; j<n-1; j++)
        {
            x[j] = x[j]-alpha[k]*x[j+1];
        }
    }
    return x;
}

vector<ll>fn;
///Take x, return the value of f(n)
ll solution(ll m)
{
    ll p = 1, sm = 0;
    for(int i=0; i<fn.size(); i++)
    {
        sm = (sm+fn[i]*p)%mod;
        p = (p*m)%mod;
    }
    return sm;
}
int main()
{
    mod_Inv();
    int tc,t=1;
    cin >> tc;
    while(tc--)
    {
        int n,qry;
        cin >> n;
        vector<ll>x(n), y(n);
        for(int i=0; i<n; i++)
        {
            cin >> x[i] >> y[i];
        }
        fn = dvand_mod(x,y);
        cout << "Case " << t++ <<":\n";
        cin >> qry;
        while(qry--)
        {
            ll m;
            cin >> m;
            cout << solution(m) << "\n";
        }
    }
    return 0;
}
