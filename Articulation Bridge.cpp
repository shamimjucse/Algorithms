///light oj - 1026 Solution
#include"bits/stdc++.h"
#define ll long long
using namespace std;
vector<ll>adj[10005];
ll dis[10005],low[10005],tim,cnt;
pair<ll,ll>pr[100005];
map<pair<ll,ll>,ll>mp;
void articulationBridge(ll u, ll p)
{
    dis[u]=low[u]=++tim;
    for(ll i=0; i<adj[u].size(); i++)
    {
        ll v = adj[u][i];
        if(v==p)continue;
        if(!low[v])
        {
            low[v]=1;
            articulationBridge(v,u);
            low[u]=min(low[u],low[v]);

            ll lo=min(u,v),hi=max(u,v);
            if(low[v]>dis[u] && !mp.count({lo,hi}))
            {
                mp[{lo,hi}]=1;
                pr[cnt]={lo,hi};
                cnt++;
            }
        }
        else
        {
            low[u]=min(low[u],dis[v]);
        }
    }
}
int main()
{
    ll i,j,k,m,n,p,q,tc,t=1;
    char ch;
    scanf("%lld",&tc);
    while(tc--)
    {
        scanf("%lld",&n);
        for(i=0; i<n; i++)
        {
            scanf("%lld",&p);
            getchar();
            scanf("%c %lld %c",&ch,&m,&ch);
            for(j=0; j<m; j++)
            {
                scanf("%lld",&q);
                adj[p].push_back(q);
                adj[q].push_back(p);
            }
        }
        cnt = 0;
        tim = 0;
        for(i=0; i<n; i++)
        {
            if(!low[i])
                articulationBridge(i,i);
        }
        sort(pr,pr+cnt);
        printf("Case %lld:\n%lld critical links\n",t++,cnt);
        for(i=0;i<cnt;i++)
        {
            printf("%lld - %lld\n",pr[i].first,pr[i].second);
        }
        mp.clear();
        for(i=0; i<n; i++)
        {
            adj[i].clear();
            low[i]=0;
        }
    }
    return 0;
}

