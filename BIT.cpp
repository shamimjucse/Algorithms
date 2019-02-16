#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll bit[1000005],_n,_len;
void update(ll i, ll val)
{
    while(i<=_n)
    {
        bit[i]+=val;
        i+=(i&(-i));
    }
}
ll query(ll i)
{
    ll sum=0;
    while(i>0)
    {
        sum+=bit[i];
        i-=(i&(-i));
    }
    return sum;
}
ll select(ll k)
{
    ll i,p,h=0;
    for(i=_len; i>=0; i--)
    {
        p=1<<i;
        if(p+h>_n) continue;
        if(bit[p+h]<k)
        {
            h+=p;
            k-=bit[h];
        }
    }
    return h+1;
}
int main()
{
    ///main code
    return 0;
}
