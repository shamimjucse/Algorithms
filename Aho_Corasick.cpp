///Light OJ - 1427(Substring Frequency (II))
#include<bits/stdc++.h>
#define MX 250002
using namespace std;
int indx,len,tree[MX][26];
int val[MX],ed[MX],suffix[MX],path[MX];
void init()
{
    indx=0, len=0;
    memset(tree[0],-1,sizeof tree[0]);
    memset(suffix,0,sizeof suffix);
    memset(val,0,sizeof val);
}
inline int New()
{
    indx++;
    memset(tree[indx],-1,sizeof tree[indx]);
    return indx;
}
inline void insert(string s, int pos)
{
    int now = 0;
    for(int i=0; i<s.size(); i++)
    {
        int id = s[i]-'a';
        if(tree[now][id]==-1)
            tree[now][id]=New();
        now = tree[now][id];
    }
    ed[pos]=now;
}
void reverse_link()
{
    queue<int>qu;
    for(int i=0; i<26; i++)
    {
        if(tree[0][i]!=-1)
        {
            qu.push(tree[0][i]);
        }
        else tree[0][i]=0;
    }
    while(!qu.empty())
    {
        int u=qu.front();
        qu.pop();
        for(int i=0;i<26;i++)
        {
            int v = tree[u][i];
            if(v==-1)
            {
                tree[u][i]=tree[suffix[u]][i];
                continue;
            }
            suffix[v]=tree[suffix[u]][i];
            qu.push(v);
            path[++len]=v;
        }
    }
}
void search(string s)
{
    int now = 0;
    for(int i=0;i<s.size();i++)
    {
        int id = s[i]-'a';
        now = tree[now][id];
        val[now]++;
    }
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
