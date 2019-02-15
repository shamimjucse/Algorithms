/// SPOJ - HISTOGRA
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
vector<ll>hgt,vc;
ll Histogram()
{
    ll sm = 0, i = 0;
    hgt.pb(0), vc.clear();
    while(i < hgt.size())
    {
        if(vc.empty() || hgt[i]>hgt[vc.back()])
        {
            vc.push_back(i);
            i++;
        }
        else
        {
            ll t = vc.back();
            vc.pop_back();
            sm = max(sm,hgt[t]*(vc.empty() ? i : i-vc.back()-1));
        }
    }
    return sm;
}
int main()
{
    ll i,j,k,n,tc;
    while(cin >> n && n)
    {
        hgt.assign(n,0);
        for(i=0;i<n;i++)cin>>hgt[i];
        k = Histogram();
        cout << k << endl;
    }
    return 0;
}
