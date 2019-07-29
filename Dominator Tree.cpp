#include<bits/stdc++.h>
using namespace std;

const int mx = 100002;
vector<int>adj[mx],adjr[mx];
int indeg[mx];
vector<int> topSort(int n)
{
    vector<int> vc;
    priority_queue<int,vector<int>,greater<int> >pq;
    for(int i=1; i<=n; i++)
        if(indeg[i]==0)
            pq.push(i);
    while(!pq.empty())
    {
        int u = pq.top();
        pq.pop();
        vc.push_back(u);
        for(int i=0; i<adj[u].size(); i++)
        {
            int v = adj[u][i];
            indeg[v]--;
            if(!indeg[v])
                pq.push(v);
        }
    }
    return vc;
}

int lev[mx],sp[17][mx],depth=16;
int LCA(int u, int v)
{
    if(lev[v]>lev[u])
        swap(u,v);
    for(int i=depth; i>=0; i--)
    {
        if(lev[u]>=(1<<i) && lev[u]-(1<<i)>=lev[v])
        {
            u = sp[i][u];
        }
    }
    if(u == v)
        return u;
    for(int i=depth; i>=0; i--)
    {
        if(sp[i][u]!=sp[i][v])
        {
            u = sp[i][u], v = sp[i][v];
        }
    }
    return sp[0][u];
}

//It doesn't make any existing tree, it just make sparse table of the tree 
void dominator(int n)
{
    vector<int> vc = topSort(n);
    for(int i=0; i<vc.size(); i++)
    {
        int u = vc[i];
        if(adjr[u].size()==0)
        {
            for(int k=0; k<=depth; k++)
                sp[k][u] = 0;
            lev[u] = 0;
        }
        else
        {
            int p = adjr[u][0];
            for(int j=0; j<adjr[u].size(); j++)
            {
                int q = adjr[u][j];
                p = LCA(p,q);
            }
            sp[0][u] = p;
            lev[u] = lev[p]+1;
            for(int k=1; k<=depth; k++)
                sp[k][u] = sp[k-1][sp[k-1][u]];
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tc,t=1;
    cin >> tc;
    while(tc--)
    {
        int n,m;
        cin >> n >> m;
        for(int i=1; i<=n; i++)
        {
            adj[i].clear();
            adjr[i].clear();
        }
        memset(indeg,0,sizeof indeg);
        for(int i=0; i<m; i++)
        {
            int u,v;
            cin >> u >> v;
            adj[u].push_back(v);
            adjr[v].push_back(u);
            indeg[v]++;
        }
        dominator(n);

        int qry;
        cin >> qry;
        cout << "Case " << t++ << ":\n";
        while(qry--)
        {
            int u,v;
            cin >> u >> v;
            if(LCA(u,v)>=2)
                cout << "NO\n";
            else
                cout << "YES\n";
        }
    }
    return 0;
}
/*
The problem says that you will be given a directed acyclic graph (DAG) of N nodes
rooted at node 1. Now you will have to answer Q queries. The i-th query will contain
two integer Ui and Vi which actually denote two nodes from the DAG. You have to
say if you can find two paths: 1 to Ui and 1 to Vi such that these two paths are both
edge disjoint and vertex disjoint at the same time. There can be multiple path for 1 to
Ui but you will have to choose any one from those. Same goes for path from 1 to Vi.
But these two chosen path should be both edge disjoint and vertex disjoint to each
other.
*/
