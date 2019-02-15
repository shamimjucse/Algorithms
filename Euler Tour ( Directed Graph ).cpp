#include<bits/stdc++.h>
#define ll int
#define prll pair<ll,ll>
using namespace std;
vector<prll>adj[100005];
list<ll>lst;
ll indeg[100005],outdeg[100005];
ll EulerCheck(ll n)
{
    ll i,odd=0;
    for(i=1; i<=n; i++)
    {
        if(abs(indeg[i]-outdeg[i])>1)
            return 0;
        if(indeg[i]!=outdeg[i])
            odd++;
    }
    if(odd==0)return 2;
    else if(odd==2)return 1;
    return 0;
}
ll StartNode(ll p, ll n)
{
    if(p==1)
    {
        for(ll i=1;i<=n;i++)
        {
            if(indeg[i]<outdeg[i])
                return i;
        }
    }
    else
    {
        for(ll i=1;i<=n;i++)
        {
            if(indeg[i]>0)
                return i;
        }
    }
}
ll EndNode(ll n)
{
    for(ll i=1;i<=n;i++)
    {
        if(indeg[i]>outdeg[i])
                return i;
    }
}
void EulerTour(list<ll>::iterator i, ll u)
{
    for(ll j=0;j<adj[u].size();j++)
    {
        prll &v = adj[u][j];
        if(v.second)
        {
            v.second = 0;
            EulerTour(lst.insert(i,u), v.first);
        }
    }
}
int main()
{
    ll i,j,p,q,n,m,tc,t=1;
    cin >> tc;
    while(tc--)
    {
        cin >> n >> m;
        for(i=0; i<m; i++)
        {
            cin >> p >> q;
            adj[p].push_back({q,1});
            indeg[q]++;
            outdeg[p]++;
        }

        if(t!=1) cout << endl;
        cout << "Case #" << t++ << endl;
        p = EulerCheck(n);
        /// p =1 (Euler Path)
        /// p =2 (Euler Circuit)
        if(p)
        {
            lst.clear();
            q = StartNode(p,n);
            EulerTour(lst.begin(), q);
            if(lst.size()!=m || m==0)
            {
                cout << "Euler Tour not possible." << endl;
                continue;
            }
            if(p==1)
            {
                q = EndNode(n);
                cout << q;
                list<ll>::iterator it = lst.begin();
                for( ;it!=lst.end();it++)
                {
                    cout << " " << *it;
                }
                cout << endl;
            }
            else
            {
                list<ll>::iterator it = lst.begin();
                q = *it;
                for( ;it!=lst.end();it++)
                {
                    cout << *it << " ";
                }
                cout << q << endl;
            }
        }
        else
        {
            cout << "Euler Tour not possible." << endl;
        }
        for(i=0; i<=n; i++)
        {
            adj[i].clear();
            indeg[i]=outdeg[i]=0;
        }
    }
    return 0;
}

