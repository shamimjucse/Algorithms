///Codechef - PRIMEDST
#include<bits/stdc++.h>
#define MX 50007
#define pb push_back
#define ll long long
using namespace std;
vector<int>vc[MX],prime;
int SubTree[MX],del[MX],dis[MX],vis[MX];
ll ans=0,sum,n;
void seive()
{
    for(int i=4; i<MX; i+=2)vis[i]=1;
    for(int i=3; i*i<MX; i+=2)
        if(!vis[i])for(int j=i*i; j<MX; j+=i+i)vis[j]=1;
    for(int i=2; i<MX; i++)if(!vis[i])prime.pb(i);
}
void dfs(int u, int p)
{
    SubTree[u]=1;
    for(int i=0; i<vc[u].size(); i++)
    {
        int v = vc[u][i];
        if(v==p || del[v])continue;
        dfs(v,u);
        SubTree[u]+=SubTree[v];
    }
}
int GetCenter(int u, int p, int sz)
{
    for(int i=0; i<vc[u].size(); i++)
    {
        int v = vc[u][i];
        if(v==p || del[v])continue;
        if(SubTree[v]>sz/2)return GetCenter(v,u,sz);
    }
    return u;
}
void CalculateDist(int u, int p, int dist, int sz)
{
    int i = lower_bound(prime.begin(),prime.end(),dist)-prime.begin();
    for( ; i<prime.size()&&prime[i]<=sz; i++)
    {
        if((prime[i]-dist)>=0)sum+=dis[prime[i]-dist];
    }
    for(int i=0; i<vc[u].size(); i++)
    {
        int v = vc[u][i];
        if(v!=p && !del[v])CalculateDist(v,u,dist+1,sz);
    }
}
void SetDist(int u, int p, int dist)
{
    for(int i=0; i<vc[u].size(); i++)
    {
        int  v = vc[u][i];
        if(v!=p && !del[v])SetDist(v,u,dist+1);
    }
    dis[dist]++;
}
void Decompose(int u, int p)
{
    dfs(u,-1);
    int center = GetCenter(u,-1,SubTree[u]);
    for(int i=0; i<n&&dis[i]; i++)dis[i]=0;
    dis[0] = 1, sum = 0;
    for(int i=0; i<vc[center].size(); i++)
    {
        int v = vc[center][i];
        if(del[v])continue;
        CalculateDist(v,center,1,SubTree[u]);
        SetDist(v,center,1);
    }
    ans+=sum;
    del[center]=1;
    for(int i=0; i<vc[center].size(); i++)
    {
        int v = vc[center][i];
        if(!del[v])Decompose(v,center);
    }
}
int main()
{
    int i,p,q;
    scanf("%lld",&n);
    for(i=1; i<n; i++)
    {
        scanf("%d %d",&p,&q);
        vc[p].pb(q);
        vc[q].pb(p);
    }
    seive();
    Decompose(1,-1);
    ll tot = n*(n-1)/2;
    double d = (ans*1.0)/(tot*1.0);
    //cout<<fixed<<setprecision(6)<<d<<endl;
    printf("%.10lf\n",d);

    return 0;
}
