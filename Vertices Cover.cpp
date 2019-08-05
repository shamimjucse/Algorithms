///Its a part of another problem such as matching / flow
#include<bits/stdc++.h>
using namespace std;

const int mx = 1002;
bool vis[mx];
int match[mx];
vector<int>adj[mx];

/// Call this function after calling flow
vector<int> koing(int n, int m)
{
    ///Return a optimal set of vertices to cover the graph (vertex cover)
    queue<int> qu;
    vector<bool> vis(n+m+1,0);
    set<int> st;
    for(int i=1; i<=n; i++)
    {
        if(match[i]==0)
        {
            qu.push(i);
            vis[i]=1;
            st.insert(i);
        }
    }
    while(!qu.empty())
    {
        int u = qu.front();
        qu.pop();
        for(auto v : adj[u])
        {
            st.insert(v);
            if(match[v] && !vis[match[v]])
            {
                st.insert(match[v]);
                qu.push(match[v]);
                vis[match[v]]=1;
            }
        }
    }
    vector<int> vc;
    for(int i=1; i<=n; i++)
        if(st.find(i)!=st.end())
            vc.push_back(i);
    for(int i=n+1; i<=n+m; i++)
        if(st.find(i)!=st.end())
            vc.push_back(i);
    return vc;
}
