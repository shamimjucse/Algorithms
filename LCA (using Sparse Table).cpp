#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll N,lev[10005],sp[17][100005],depth=16;
vector<ll>v[10005];
void dfs(ll u)
{
    for(auto p : v[u])
    {
        if(lev[p]==-1)
        {
            lev[p]=lev[u]+1;
            sp[0][p]=u;
            dfs(p);
        }
    }
}
void build_table()
{
    ll i,j;
    for(i=1; (1<<i)<N; i++)
    {
        for(j=0; j<N; j++)
        {
            if(sp[i-1][j]!=-1)
            {
                sp[i][j]=sp[i-1][sp[i-1][j]];
            }
        }
    }
}
ll lca(ll p, ll q)
{
    if(lev[q]>lev[p])swap(p,q);
    for(ll i=depth; i>=0; i--)
    {
        if(lev[p]>=(1<<i) && lev[p]-(1<<i)>=lev[q])
        {
            p=sp[i][p];
        }
    }
    if(p==q) return p;
    for(ll i=depth; i>=0; i--)
    {
        if(sp[i][p]!=-1 && sp[i][p]!=sp[i][q])
        {
            p=sp[i][p],q=sp[i][q];
        }
    }
    return sp[0][p];
}
int main()
{
    ll i,j,p,q,m,tc,ans,t=1;
    cin >> tc;
    while(tc--)
    {
        cin >> N;
        N++;
        for(i=1; i<N; i++)
        {
            cin >> m;
            for(j=1; j<=m; j++)
            {
                cin >> q;
                v[i].push_back(q);
                v[q].push_back(i);
            }
        }
        memset(lev,-1,sizeof lev);
        memset(sp,-1,sizeof sp);
        lev[1]=0;
        dfs(1);
        build_table();
        cout << "Case " << t++ << ":" << endl;
        cin >> m;
        for(i=1; i<=m; i++)
        {
            cin >> p >> q;
            ans = lca(p,q);
            cout << ans << endl;
        }
    }
    return 0;
}
