#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll N,a[100005],sp[17][100005],depth=16;
void build_table()
{
    ll i,j;
    for(i=0;i<N;i++) sp[0][i]=a[i];
    for(i=1;i<=depth;i++)
    {
        for(j=0;j<=N-(1<<i);j++)
        {
            sp[i][j]=min(sp[i-1][j],sp[i-1][j+(1<<(i-1))]);
        }
    }
}
ll sparse_table(ll l, ll r)///0-indexing
{
    ll ans = 1e9+2,i;
    for(i=depth;i>=0;i--)
    {
        if(l+(1<<i)-1<=r)
        {
            ans=min(ans,sp[i][l]);
            l+=(1<<i);
        }
    }
    return ans;
}
int main()
{
    ll l,r,p,q,i,j;
    cin >> N;
    for(i=0;i<N;i++)
    {
        cin >> a[i];
    }
    build_table();
    cin >> q;
    for(i=1;i<=q;i++)
    {
        cin >> l >> r;
        p=sparse_table(l,r);
        cout << p << endl;
    }
    return 0;
}

