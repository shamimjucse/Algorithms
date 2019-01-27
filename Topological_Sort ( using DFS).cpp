#include <bits/stdc++.h>
#define ll long long
using namespace std;
vector<ll>v[100005],vc;
ll vis[100005];
void topSort(ll u)
{
    vis[u]=1;
    for(ll i=0; i<v[u].size(); i++)
    {
        ll nw = v[u][i];
        if(vis[nw]==0)
        {
            topSort(nw);
        }
    }
    vc.push_back(u);
}
int main()
{
    ll i,p,q,m,n;
    while(cin >> n >> m)
    {
        for(i=1; i<=m; i++)
        {
            cin >> p >> q;
            v[p].push_back(q);
        }
        for(i=1; i<=n; i++)
        {
            if(!vis[i])
            {
                topSort(i);
            }
        }
        reverse(vc.begin(),vc.end());
        for(i=0; i<vc.size(); i++)
        {
            cout << vc[i] << " ";
        }
        cout << endl;
        vc.clear();
        for(i=0;i<=n;i++)
        {
            v[i].clear();
            vis[i]=0;
        }
    }
    return 0;
}
