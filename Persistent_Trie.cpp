///codechef GPD
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e7+5;
int node = 1, tr[N][2];
int NewNode(int lft, int rgt)
{
    tr[node][0] = lft;
    tr[node][1] = rgt;
    return node++;
}
int Insert(int cur, int x, int i=30)
{
    if(i==-1)
    {
        return NewNode(0,0);
    }
    int lft, rgt;
    int bit = (x>>i)&1;
    if( bit )
    {
        lft = tr[cur][0];
        rgt = Insert(tr[cur][1],x,i-1);
    }
    else
    {
        rgt = tr[cur][1];
        lft = Insert(tr[cur][0],x,i-1);
    }
    return NewNode(lft,rgt);
}
int MaxQuery(int cur, int x)
{
    int ret = 0;
    for(int i=30;i>=0;i--)
    {
        int bit = (x>>i)&1;
        if( bit )
        {
            if(tr[cur][0])ret|=(1<<i),cur = tr[cur][0];
            else cur = tr[cur][1];
        }
        else
        {
            if(tr[cur][1])ret|=(1<<i),cur = tr[cur][1];
            else cur = tr[cur][0];
        }
    }
    return ret;
}
int MinQuery(int cur, int x)
{
    int ret = 0;
    for(int i=30;i>=0;i--)
    {
        int bit = ((x>>i)&1);
        if( !bit )
        {
            if(tr[cur][0])cur = tr[cur][0];
            else ret|=(1<<i), cur = tr[cur][1];
        }
        else
        {
            if(tr[cur][1])cur = tr[cur][1];
            else ret|=(1<<i),cur = tr[cur][0];
        }
    }
    return ret;
}
int main()
{
    int i,j,n,k,u,v,qry,f;
    map<int,int>mp;
    cin >> n >> qry;
    cin >> u >> k;
    mp[u]=Insert(0, k);
    for(i=1;i<n;i++)
    {
        cin >> u >> v >> k;
        mp[u] = Insert(mp[v], k);
    }
    int last = 0;
    while(qry--)
    {
        cin >> f;
        if(f^last)
        {
            cin >> v >> k;
            v^=last, k^=last;
            int mn = MinQuery(mp[v],k);
            int mx = MaxQuery(mp[v],k);
            cout << mn << " " << mx << endl;
            last = mn ^ mx;
        }
        else
        {
            cin >> v >> u >> k;
            u^=last, v^=last, k^=last;
            mp[u] = Insert(mp[v], k);
        }
    }
    return 0;
}
