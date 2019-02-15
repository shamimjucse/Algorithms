#include<bits/stdc++.h>
#define ll long long
#define inf 9999999999999999LL
#define prll pair<ll,ll>
using namespace std;
vector<prll>v[1000005];
ll dis[1000005];
void dijkstra(ll u)
{
    priority_queue<prll,vector<prll>,greater<prll> >pq;
    pq.push({0,u});
    dis[u]=0;
    while(!pq.empty())
    {
        u = pq.top().second;
        pq.pop();
        for(ll i=0;i<v[u].size();i++)
        {
            ll nw = v[u][i].second;
            ll cost = v[u][i].first;
            if(dis[u]+cost < dis[nw])
            {
                dis[nw] = dis[u]+cost;
                pq.push({dis[nw],nw});
            }
        }
    }
}
int main()
{
    ll i,j,n,m,p,q,c,tc;
    cin >> tc;
    while(tc--)
    {
        cin >> n >> m;
        for(i=1;i<=m;i++)
        {
            cin >> p >> q >> c;
            v[p].push_back({c,q});
            v[q].push_back({c,p});
        }
        cin >> p >> q;
        for(i=0;i<=n;i++)dis[i]=inf;
        dijkstra(p);

        if(dis[q]==inf)cout << "No Path" << endl;
        else cout << dis[q] << endl;

        for(i=0;i<=n;i++)v[i].clear();
    }
    return 0;
}
