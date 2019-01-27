#include<bits/stdc++.h>
#define ll int
#define prll pair<ll,ll>
using namespace std;
vector<prll>adj[5002];
list<ll>lst;
ll EulerCheck(ll n)
{
    ll i,odd=0;
    for(i=1; i<=n; i++)
    {
        if(adj[i].size()%2!=0)odd++;
    }
    if(odd==0)return 2;
    else if(odd==2)return 1;
    return 0;
}
ll StartNode(ll p, ll n)
{
    p = p%2;
    for(ll i=1;i<=n;i++)
    {
        if(adj[i].size()!=0 && adj[i].size()%2==p)
        {
            return i;
        }
    }
}
ll EndNode(ll p, ll n)
{
    for(ll i=1;i<=n;i++)
    {
        if(i!=p && adj[i].size()!=0 && adj[i].size()%2!=0)
        {
            return i;
        }
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
            for(ll k=0;k<adj[v.first].size();k++)
            {
                prll &nw = adj[v.first][k];
                if(nw.first==u && nw.second)
                {
                    nw.second = 0;
                    break;
                }
            }
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
            adj[q].push_back({p,1});
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
                q = EndNode(q,n);
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
        for(i=0; i<=n; i++)adj[i].clear();
    }
    return 0;
}

