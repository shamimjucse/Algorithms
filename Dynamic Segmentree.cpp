///http://codeforces.com/problemset/problem/669/E
#include<bits/stdc++.h>
#define MX 1e9+2
using namespace std;
map<int,int>mp;
int avail=0;
struct node
{
    int l,r,info;
    node(){l=0,r=0,info=0;}
};
node tr[100000*30+2];
int update(int no, int st, int ed, int x, int val)
{
    int idx = no;
    if(!no)
    {
        idx=++avail;
        tr[idx]=node();
    }
    if(st==ed && st==x)
    {
        tr[idx].info+=val;
        return idx;
    }
    int mid = (st+ed)>>1;
    if(mid>=x)      tr[idx].l=update(tr[idx].l,st,mid,x,val);
    else            tr[idx].r=update(tr[idx].r,mid+1,ed,x,val);
    tr[idx].info = (tr[tr[idx].l].info+tr[tr[idx].r].info);
    return idx;
}
int query(int idx, int st, int ed, int l, int r)
{
    if(idx==0)        return 0;
    if(st>=l && ed<=r)return tr[idx].info;
    int mid=(st+ed)>>1;
    if(mid>=r)        return query(tr[idx].l,st,mid,l,r);
    else if(mid<st)   return query(tr[idx].r,mid+1,ed,l,r);
    else              return query(tr[idx].l,st,mid,l,mid)+query(tr[idx].r,mid+1,ed,mid+1,r);
}
int main()
{
    int i,j,f,t,m,n,p;
    while(cin >> n)
    {
        for(i=1;i<=n;i++)
        {
            cin >> f >> t >> m;
            if(f==1)
            {
                mp[m] = update(mp[m],1,MX,t,1);
            }
            else if(f==2)
            {
                mp[m] = update(mp[m],1,MX,t,-1);
            }
            else
            {
                p = query(mp[m],1,MX,1,t);
                cout << p << endl;
            }
        }
        mp.clear();
        for(i=1;i<=n;i++)tr[i]=node();
    }
    return 0;
}

