/// SPOJ - MKTHNUM
#include<bits/stdc++.h>
#define ll long long
#define MX 100002
using namespace std;
struct node
{
    int info,l,r;
    node()
    {
        info=l=r=0;
    }
} tr[20*MX];
int root[MX],a[MX],avail;

int update(int pre, int st, int ed, int x, int val)
{
    int nod = ++avail;
    tr[nod] = tr[pre];
    if( st==ed )
    {
        tr[nod].info+=val;
        return nod;
    }
    int mid = (st+ed)>>1;
    if(x<=mid)tr[nod].l=update(tr[nod].l,st,mid,x,val);
    else      tr[nod].r=update(tr[nod].r,mid+1,ed,x,val);
    tr[nod].info = tr[tr[nod].l].info + tr[tr[nod].r].info;
    return nod;
}
int query(int nod, int pre, int st, int ed, int k)
{
    if(st == ed)
    {
        return st;
    }
    int mid = (st+ed)>>1;
    int nw = tr[tr[nod].l].info-tr[tr[pre].l].info;
    if(nw>=k)return query(tr[nod].l,tr[pre].l,st,mid,k);
    else     return query(tr[nod].r,tr[pre].r,mid+1,ed,k-nw);
}
map<int,int>mp;
vector<int>vc;
int main()
{
    int i,j,n,m,qry,l,r,k;
    cin >> n >> qry;
    for(i=1;i<=n;i++)
    {
        cin >> a[i];
        vc.push_back(a[i]);
    }
    sort(vc.begin(),vc.end());
    for(i=0;i<vc.size();i++)
    {
        mp[vc[i]]=i+1;
    }
    for(i=1;i<=n;i++)
    {
        root[i]=update(root[i-1],1,n,mp[a[i]],1);
    }
    while(qry--)
    {
        cin >> l >> r >> k;
        m = query(root[r],root[l-1],1,n,k);
        cout << vc[m-1] << endl;
    }
    return 0;
}
