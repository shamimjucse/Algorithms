#include <bits/stdc++.h>
#define ll long long
using namespace std;
vector<ll>v[100005],vc;
ll indeg[100005];
void topSort(ll n)
{
    priority_queue<ll,vector<ll>,greater<ll> >pq;
    for(ll i=1;i<=n;i++)
    {
        if(indeg[i]==0)
        {
            pq.push(i);
        }
    }
    while(!pq.empty())
    {
        ll u = pq.top();
        pq.pop();
        vc.push_back(u);
        for(ll i=0;i<v[u].size();i++)
        {
            ll nw = v[u][i];
            indeg[nw]--;
            if(!indeg[nw])
            {
                pq.push(nw);
            }
        }
    }
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
            indeg[q]++;
        }
        topSort(n);
        for(i=0; i<vc.size(); i++)
        {
            cout << vc[i] << " ";
        }
        cout << endl;
        vc.clear();
        for(i=0;i<=n;i++)
        {
            v[i].clear();
            indeg[i]=0;
        }
    }
    return 0;
}
