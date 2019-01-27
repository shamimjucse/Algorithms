#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[1000000+2];
ll tmp[1000000+2];
ll ans;
void mergeSort(ll st, ll ed)
{
    if(st==ed)
        return;
    ll mid=st+(ed-st)/2;
    mergeSort(st,mid);
    mergeSort(mid+1,ed);
    ll s=st;
    ll e=mid+1;
    ll cnt=st;
    ll c=0;
    while(s<=mid||e<=ed)
    {
        if(s>mid) tmp[cnt++]=a[e++];
        else if(e>ed) tmp[cnt++]=a[s++],ans+=c;
        else if(a[s]<a[e]) tmp[cnt++]=a[s++],ans+=c;
        else tmp[cnt++]=a[e++],c++;
    }
    for(int i=st;i<=ed;i++)
    {
        a[i]=tmp[i];
    }
}
int main()
{
    ll n;
    while(cin >> n)
    {
        for(int i=0;i<n;i++)
        {
            cin >> a[i];
        }
        ans=0;
        mergeSort(0,n-1);
        cout << ans << endl;
    }
    return 0;
}
