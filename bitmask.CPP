#include"bits/stdc++.h"
#define ll long long
using namespace std;
ll a[30];
int main()
{
    ll i,j,k,n,sm,m;
    while(cin >> n)
    {
        for(i=0;i<n;i++)
        {
            cin >> a[i];
        }
        sm=0;
        for(i=0;i<(1LL<<n);i++)
        {
            for(j=0;j<n;j++)
            {
                if(i&(1LL<<j))
                {
                    sm+=a[j];
                }
            }
        }
        cout << sm << endl;
    }
    return 0;
}

