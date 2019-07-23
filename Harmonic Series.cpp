/// Light OJ - 1234
///1+1/2+1/3+1/4+1/5......
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int lim = 100000;
const double gama = 0.5772156649;
//0.57721566490153286060651209008240243104215933593992 as much
double Bn[] = {1.0/6.0, -1.0/30.0, 1.0/42.0, -1.0/30.0, 5.0/66.0};
double har[100002];
void precall()
{
    for(int i=1;i<=lim;i++)
    {
        har[i]=har[i-1]+1.0/i;
    }
}
double harmonic(ll n)
{
    if(n<=lim)return har[n];
    double r = log(n) + gama + .5/n;
    for(int i = 0; i < 5; i++)
    {
        r -= (har[i] / (2.0*(i+1)*pow(n,2*(i+1)))) ;
    }
    return r;
}
int main()
{
    precall();
    int tc,t=1;
    cin >> tc;
    while(tc--)
    {
        ll n;
        cin >> n;
        double k = harmonic(n);
        cout << "Case " << t++ << ": " <<fixed <<setprecision(10)<< k << endl;
    }
    return 0;
}
