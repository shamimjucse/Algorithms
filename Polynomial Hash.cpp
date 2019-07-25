///https://algo.codemarshal.org/contests/ruet-iupc-19/problems/D
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mx = 200002;
vector<ll>adj[mx];
ll a[mx],st[mx],ed[mx],mp[mx],tim;
void dfs(ll u, ll p)
{
    st[u] = ++tim;
    mp[tim] = u;
    for(int i=0;i<adj[u].size();i++)
    {
        ll v = adj[u][i];
        if(v!=p)
        {
            dfs(v,u);
        }
    }
    ed[u] = tim;
}

#define mid ((st+ed)>>1)
#define lft 2*pos
#define rgt 2*pos+1
#define base 131
#define mod 1000000007LL

ll power(ll a, ll b, ll m)
{
    ll ans = 1;
    a%=mod;
    while(b)
    {
        if(b&1)
            ans = (ans*a)%mod;
        a = (a*a)%mod;
        b>>=1;
    }
    return ans;
}

ll tr[4*mx],lazy[4*mx],inv = power(base,mod-2,mod);
void build(ll pos, ll st, ll ed)
{
    lazy[pos] = 0;
    if(st==ed)
    {
        ll b = (a[mp[st]]>=0) ? base : inv;
        tr[pos]=power(b,abs(a[mp[st]]),mod);
        return;
    }
    build(lft,st,mid);
    build(rgt,mid+1,ed);
    tr[pos]=(tr[lft]+tr[rgt])%mod;
}
void propagate(ll pos, ll st, ll ed)
{
    ll b = (lazy[pos]>=0) ? base : inv;
    tr[pos]=(tr[pos]*power(b,abs(lazy[pos]),mod))%mod;
    if(st!=ed)lazy[lft]+=lazy[pos], lazy[rgt]+=lazy[pos];
    lazy[pos] = 0;
}
void update(ll pos, ll st, ll ed, ll l, ll r, ll val)
{
    if(lazy[pos]!=0)propagate(pos,st,ed);
    if(st>r || ed<l)return;
    if(st>=l && ed<=r)
    {
        ll b = (val>=0) ? base : inv;
        tr[pos]=(tr[pos]*power(b,abs(val),mod))%mod;
        if(st!=ed)lazy[lft]+=val,lazy[rgt]+=val;
        return;
    }
    update(lft,st,mid,l,r,val);
    update(rgt,mid+1,ed,l,r,val);
    tr[pos]=(tr[lft]+tr[rgt])%mod;
}
ll query(ll pos, ll st, ll ed, ll l, ll r)
{
    if(st>r || ed<l)return 0;
    if(lazy[pos]!=0)propagate(pos,st,ed);
    if(st>=l && ed<=r)return tr[pos];
    return (query(lft,st,mid,l,r)+query(rgt,mid+1,ed,l,r))%mod;
}

int main()
{
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tc,t=1;
    cin >> tc;
    while(tc--)
    {
        ll n,qry;
        cin >> n >> qry;
        for(int i=1;i<=n;i++)
        {
            cin >> a[i];
            adj[i].clear();
        }
        for(int i=1;i<n;i++)
        {
            int u,v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        tim = 0;
        dfs(1,0);
        build(1,1,n);
        cout << "Case " << t++ << ":\n";
        while(qry--)
        {
            ll type,x,y;
            cin >> type >> x >> y;
            if(type == 1)
            {
                update(1,1,n,st[x],ed[x],y);
            }
            else
            {
                ll p = query(1,1,n,st[x],ed[x])%mod;
                ll q = query(1,1,n,st[y],ed[y])%mod;
                if(p==q)cout << 1 << "\n";
                else    cout << 0 << "\n";
            }
        }
    }
    return 0;
}
/**
{2,5,3,2,5,7,5,12}
(2x^2 + x^3 + 5x^3 + x^7 + x^12) [x = base];
prefix hs[i] = hs[i-1]+power(base,value,mod)
if(value<0) power(inverse(base),abs(value),mod)
*/
/*
You have given a tree of N nodes. Nodes are numbered from 1 to N and the tree is rooted on the node 1.
Every node of the tree has a value on it.
Subtree rooted at U and V are similar if they produce the same array after sorting all values of their subtree.
Subtree rooted at 2 and 3 are similar, because both of them produce the same array {1, 1, 1, 2} after sorting all
the values associated with the nodes of those two subtrees. But subtree rooted at 3 and 4 are not similar
because subtree rooted at 3 produces the array {1, 1, 1, 2}, and subtree rooted at 4 produces the array {1, 1,
2, 2}, and they are not the same array.
Along with the tree you will also given some operation to perform. There are two types of operations
1. Update(X, V): add V to all the nodes of subtree rooted at X.
2. Query(X, Y): Check If subtree rooted at X and Y are similar.

Input
First line of the input will contain a single integer, T, denoting the number of test cases. Each test case starts
with two space separated integers N, O. N denotes the number of nodes in the tree and O denotes the number
of operations.
Next line contains N space separated integers, i-th of which indicates the associated value of i-th node. Next
N-1 lines contain two space separated integer U, V, denoting that there is an edge between node U and V.
Each of next O lines contains three integers, describing an operation. First of them is the type of operation,
which can be either 1 or 2. If it is 1, then the following two integers are X, V, denoting an update operation.
Otherwise, the following two integers are X, Y, denoting a query operation.

Output
For each test case, print the line without quotation “Case t:” Where t is the number of the test case starting
from 1. For each Query(X, Y) operation print 1 if subtree rooted at X, Y are similar; otherwise print 0, in
separate line. Check sample input output for exact formatting.

input:
2
13 4
3 1 2 1 1 2 1 1 1 1 2 2 1
1 2
1 3
1 4
2 5
2 6
2 7
3 8
3 9
3 10
4 11
4 12
4 13
2 2 3
2 3 4
1 12 -1
2 3 4
2 1
1 1
1 2
2 1 2

Output:
Case 1:
1
0
1
Case 2:
0
*/
