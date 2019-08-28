///Light OJ - 1427(Substring Frequency (II))
#include<bits/stdc++.h>
#define mx 250002
using namespace std;
int tr[mx][26],suffix[mx],node,len;
int val[mx],ed[mx],path[mx];
void init()
{
    node=0, len=0;
    memset(tr[0],-1,sizeof tr[0]);
    memset(suffix,0,sizeof suffix);
    memset(val,0,sizeof val);
}
inline int New()
{
    node++;
    memset(tr[node],-1,sizeof tr[node]);
    return node;
}
inline void insert(string s, int pos)
{
    int cur = 0;
    for(int i=0; i<s.size(); i++)
    {
        int c = s[i]-'a';
        if(tr[cur][c]==-1)
            tr[cur][c]=New();
        cur = tr[cur][c];
    }
    ed[pos]=cur;
}
void reverse_link()
{
    queue<int>qu;
    for(int i=0; i<26; i++)
    {
        if(tr[0][i]!=-1)
        {
            qu.push(tr[0][i]);
        }
        else tr[0][i]=0;
    }
    while(!qu.empty())
    {
        int u=qu.front();
        qu.pop();
        for(int i=0;i<26;i++)
        {
            int v = tr[u][i];
            if(v==-1)
            {
                tr[u][i]=tr[suffix[u]][i];
                continue;
            }
            suffix[v]=tr[suffix[u]][i];
            qu.push(v);
            path[++len]=v;
        }
    }
}
//Make tree with reverse suffix link
vector<int>rtr[mx];
void makeTree()
{
    for(int i=0;i<=node;i++)rtr[i].clear();
    for(int i=1;i<=node;i++)
    {
        rtr[suffix[i]].push_back(i);
    }
}
//calculate occurrence of every state for string s
int dfs(int u)
{
    for(auto v : rtr[u])
    {
        val[u]+=dfs(v);
    }
    return val[u];
}
void search(string s)
{
    int cur = 0;
    for(int i=0;i<s.size();i++)
    {
        int c = s[i]-'a';
        cur = tr[cur][c];
        val[cur]++;
    }
    //makeTree();
    //dfs(0);
    for(int i=len;i>=1;i--)
    {
        val[suffix[path[i]]]+=val[path[i]];
    }
}
string s,s2;
int main()
{
    int i,n,tc,t=1;
    cin >> tc;
    while(tc--)
    {
        init();
        cin >> n;
        cin >> s;
        for(i=1; i<=n; i++)
        {
            cin >> s2;
            insert(s2,i);
        }
        reverse_link();
        search(s);
        cout << "Case " << t++ << ":" << endl;
        for(i=1;i<=n;i++)
        {
            cout << val[ed[i]] << "\n";
        }
    }
    return 0;
}

