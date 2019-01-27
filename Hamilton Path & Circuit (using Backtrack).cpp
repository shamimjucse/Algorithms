///UVa - 775
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll vis[260],N;
vector<ll>adj[260],temp,ans;
void dfs(ll u)
{
    if(ans.size()!=0)return;
    for(ll i=0; i<adj[u].size(); i++)
    {
        ll v = adj[u][i];
        if(temp.size()==N && v==1)
        {
            temp.push_back(1);///circuit
            ans = temp;
            return;
        }
        if(vis[v]==1)
            continue;
        vis[v] = 1;
        temp.push_back(v);
        dfs(v);
        vis[v] = 0;
        temp.pop_back();
    }
}
int main()
{
    ll i,j,p,q;
    string s;
    while(cin >> N)
    {
        getchar();
        while(getline(cin,s) && s!="%")
        {
            stringstream ss(s);
            ss >> p >> q;
            adj[p].push_back(q);
            adj[q].push_back(p);
        }
        vis[1]=1;
        temp.push_back(1);
        dfs(1);
        if(ans.size()==0)
        {
            cout << "N" << endl;
        }
        else
        {
            cout << ans[0];
            for(i=1; i<ans.size(); i++)
            {
                cout << " " << ans[i];
            }
            cout << endl;
        }
        ans.clear();
        temp.clear();
        for(i=0; i<=N; i++)
        {
            vis[i]=0;
            adj[i].clear();
        }
    }
    return 0;
}
