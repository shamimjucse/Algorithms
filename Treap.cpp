///https://codeforces.com/problemset/problem/863/D
#include<bits/stdc++.h>
#define T long long
using namespace std;

typedef pair<int,int> pii;
const int mx = 200002;

T data[mx],sum[mx]; ///Treap data type
bool lazy[mx];
int lft[mx],rgt[mx],sz[mx],rp[mx],node=1;

/** 0 is null and these gonna always hold
data[0]=lft[0]=rght[0]=prio[0]=sz[0]=0;
we will use these identity implicitely */

inline int New(T value)
{
    data[node] = value;
    lazy[node] = 0;
    sum[node] = value;
    ///any other data
    lft[node]=rgt[node]=0;
    lazy[node]=0;
    sz[node]=1,rp[node]=rand();
    return node++;
}

inline void update(int nd)
{
    if(nd)
    {
        sz[nd]=sz[lft[nd]]+sz[rgt[nd]]+1;
        //sum[nd] = sum[lft[nd]]+sum[rgt[nd]]+data[nd];
    }
}
void propagate(int nd)
{
    if(nd && lazy[nd])
    {
        swap(lft[nd],rgt[nd]);
        lazy[nd]=0;
        lazy[lft[nd]]^=1, lazy[rgt[nd]]^=1;
    }
}

/** Split By Size : return two treap , first size of first one is
of size s (smalle) [if sz[node]<s then size of first one is sz[node],
and second one is 0] second one contating remaing */

void splitBySize(int nd, int x, int &l, int &r)
{
    propagate(nd);
    if(nd==0)l=r=0;
    else if(x==0)l=0,r=nd;
    else if(sz[nd]<=x)l=nd,r=0;
    else if(sz[lft[nd]]>=x)
    {
        splitBySize(lft[nd],x,l,lft[nd]);
        r = nd, update(nd);
    }
    else
    {
        splitBySize(rgt[nd],x-1-sz[lft[nd]],rgt[nd],r);
        l = nd, update(nd);
    }
}

/** Split By Value : return two treap , first one contaian
all vaues is less-equal Val, second one contain remaining */

void splitByValue(int nd, T val, int &l, int &r)
{
    //propagate(nd);
    if(nd==0)l=r=0;
    else if(data[nd] <= val)
    {
        splitByValue(rgt[nd],val,rgt[nd],r);
        l = nd, update(nd);
    }
    else
    {
        splitByValue(lft[nd],val,l,lft[nd]);
        r = nd, update(nd);
    }
}

///Split By Sum : return two treap, sum of the first treap is <= sm
void splitBySum(int nd, T sm, int &l, int &r)
{
    //propagate(nd);
    if(nd==0)l=r=0;
    else if(sm==0)l=0,r=node;
    else if(sum[node] <= sm)l=node,r=0;
    else if(sum[lft[node]] >= sm)
    {
 		splitBySum(lft[node],sm,l, lft[node]);
     	r = nd, update(nd);
    }
    else if(sm < sum[lft[nd]]+data[nd])
    {
        l = lft[nd], lft[nd] = 0;
        r = nd, update(nd);
    }
    else
    {
        splitBySum(rgt[nd],sm-data[nd]-sum[lft[nd]],rgt[nd],r);
        l = nd, update(nd);
    }
}
///Join : Join two treap l,r max in l must be <= min in r
int join(int l, int r)
{
    propagate(l),propagate(r);
    if(l==0)return r;
    if(r==0)return l;
    if(rp[l]>rp[r])
    {
        rgt[l]=join(rgt[l],r);
        update(l);
        return l;
    }
    else
    {
        lft[r]=join(l,lft[r]);
        update(r);
        return r;
    }
}

///Merge : similar with join but no restriction
int Merge(int l, int r)
{
    //propagate(l),propagate(r);
    if(l==0)return r;
    if(r==0)return l;
    if(rp[r] > rp[l])swap(l,r);
    int L,R;
    splitByValue(r,data[l],L,R);
    lft[l] = Merge(lft[l],L);
    rgt[l] = Merge(rgt[l],R);
    return l;
}

vector<T>ans;
void print(int nd)
{
    propagate(nd);
    if(nd==0)return;
    print(lft[nd]);
    ans.push_back(data[nd]);
    print(rgt[nd]);
}

int main()
{
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int n,qry,m,treap=0;
    cin >> n >> qry >> m;
    for(int i=1; i<=n; i++)
    {
        int p;
        cin >> p;
        treap = join(treap,New(p));
    }
    while(qry--)
    {
        int type,l,r;
        cin >> type >> l >> r;
        if(type==1)
        {
            int a1,a2,a3,a4;
            splitBySize(treap,r,a2,a3);
            splitBySize(a2,l-1,a1,a2);
            splitBySize(a2,sz[a2]-1,a2,a4);

            a2=join(a4,a2);
            treap=join(a1,join(a2,a3));
        }
        else
        {
            int a1,a2,a3;
            splitBySize(treap,r,a2,a3);
            splitBySize(a2,l-1,a1,a2);
            lazy[a2]^=1;
            treap=join(a1,join(a2,a3));
        }
    }
    ans.push_back(0);
    print(treap);
    for(int i=1; i<=m; i++)
    {
        int p;
        cin >> p;
        cout << ans[p] << " ";
    }
    cout << endl;
    return 0;
}
