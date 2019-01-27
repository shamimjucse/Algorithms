#include <bits/stdc++.h>
#define ll long long
#define inf 99999999LL
using namespace std;
ll a[100005],b[322];
int main()
{
    ll i,j,p,q,m,n,sz,l,r,ans;
    char ch;
    while(cin >> n >> m)
    {
        sz = sqrt((double)n);
        for(i=0; i<=sz+2; i++) b[i]=inf;
        ///0-indexing
        for(i=0; i<n; i++)
        {
            cin >> a[i];
            b[i/sz]=min(b[i/sz],a[i]);
        }
        for(j=0; j<m; j++)
        {
            cin >> ch >> l >> r;
            if(ch=='q')
            {
                l--,r--;
                p=l/sz+1, q=r/sz;
                ans = inf;
                for(i=l; i<p*sz && i<n && i<=r; i++)
                {
                    ans=min(ans,a[i]);
                }
                for(i=p; i<q; i++)
                {
                    ans=min(ans,b[i]);
                }
                for(i=max(q*sz,l); i<=r; i++)
                {
                    ans=min(ans,a[i]);
                }
                cout << ans << endl;
            }
            else
            {
                l--;
                a[l]=r;
                p=l/sz;
                b[p]=inf;
                for(i=p*sz; i<n&& i<(p+1)*sz; i++)
                {
                    b[p]=min(b[p],a[i]);
                }
            }
        }
    }
    return 0;
}

