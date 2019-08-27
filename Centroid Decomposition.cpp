//https://vjudge.net/problem/Gym-101991A
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int mx = 100005;
ll ans;
vector<int>adj[mx];
int SubTree[mx],del[mx];
int bit[mx],L,R;

void update(int i, int val)
{
    i+=1;
    while(i<mx)
    {
        bit[i]+=val;
        i+=(i&(-i));
    }
}
int query(int i)
{
    i+=1;
    if(i<=0)return 0;
    int sm = 0;
    while(i>0)
    {
        sm+=bit[i];
        i-=(i&(-i));
    }
    return sm;
}
void dfs(int u, int p)
{
    SubTree[u] = 1;
    for(auto v : adj[u])
    {
        if(v==p || del[v])continue;
        dfs(v,u);
        SubTree[u]+=SubTree[v];
    }
}
int GetCenter(int u, int p, int sz)
{
    for(auto v : adj[u])
    {
        if(v==p || del[v])continue;
        if(SubTree[v]>sz/2)return GetCenter(v,u,sz);
    }
    return u;
}
void SetDist(int u, int p, int lev, int val)
{
     update(lev,val);
     for(auto v : adj[u])
     {
         if(v==p || del[v])continue;
         SetDist(v,u,lev+1,val);
     }
}
void solution(int u, int p, int lev)
{
    ans+=query(R-lev)-query(L-lev-1); ///Solution for particular range
    for(auto v : adj[u])
    {
        if(v==p || del[v])continue;
        solution(v,u,lev+1);
    }
}
void Decompose(int u, int p)
{
    dfs(u,-1);
    int center = GetCenter(u,-1,SubTree[u]); ///Find a center node
    SetDist(center,-1,0,1); ///Set distance for the subtree of node center from center

    del[center] = 1; ///Mark as a center
    for(auto v : adj[center])
    {
        if(!del[v])
        {
            SetDist(v,center,1,-1); ///Remove the subtree node level for a child node from center for calculation
            solution(v,center,1); ///Find solution for node v
        }
    }
    update(0,-1); ///Remove the center node level
    for(auto v : adj[center])
    {
        if(!del[v])
        {
            Decompose(v,center);
        }
    }
}

int main()
{
    //freopen("awesome.in","r",stdin);
    int tc;
    cin >> tc;
    while(tc--)
    {
        int n,l,r;
        cin >> n >> l >> r;
        for(int i=1;i<n;i++)
        {
            int u,v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        L = n-1-r, R = n-1-l;
        Decompose(1,-1);
        cout << ans << "\n";

        ans = 0;
        for(int i=0;i<=n;i++)
        {
            adj[i].clear();
            del[i] = 0;
            bit[i] = 0;
        }
    }
    return 0;
}
