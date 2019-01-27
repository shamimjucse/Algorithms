#include <bits/stdc++.h>
#define ll long long
#define inf 9999999999999LL
using namespace std;
vector<ll>v;
ll a[1000005];
ll lis()
{
    a[0]=-inf;
    for(ll i=1; i<=v.size(); i++)
    {
        a[i]=inf;
    }
    ll len=0;
    for(ll i=0; i<v.size(); i++)
    {
        ll lo=0;
        ll hi=len;
        while(lo<=hi)
        {
            ll mid=lo+(hi-lo)/2;
            if(a[mid]<v[i])
                lo=mid+1;
            else
                hi=mid-1;
        }
        a[lo]=v[i];
        if(lo>len)
            len=lo;
    }
    return len;
}
int main()
{
    ll i,j,n,m,tc;
    cin >> tc;
    while(tc--)
    {
        cin >> n;
        for(i=0; i<n; i++)
        {
            cin >> m;
            v.push_back(m);
        }
        m = lis();
        cout << "Maximum increasing subsequence = " << m << endl;
        v.clear();
    }
    return 0;
}
