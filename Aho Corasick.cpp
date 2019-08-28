///Light OJ - 1427(Substring Frequency (II))
#include<bits/stdc++.h>
#define mx 250002
using namespace std;
int tr[mx][26],suffix[mx],node,len;
int val[mx],ed[mx],path[mx];
int End[mx],sf[mx];
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
    End[cur]++;
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
            
            if(End[suffix[v]]) sf[v] = suffix[v];//sf[v] = some node where end a string
            else               sf[v] = sf[suffix[v]];
            
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

/****************************************************************************/

//https://codeforces.com/problemset/problem/587/F
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;

const int mx = 250005;
vector<int>vc;
int tr[mx][26],suffix[mx],node;
int ed[mx],path[mx],End[mx],sf[mx],cnt[mx],fr[mx];
struct Aho_Corasick
{
    int root,len;
    Aho_Corasick()
    {
        root=++node;
        suffix[root]=root, sf[root]=root;
        memset(tr[root],-1,sizeof tr[root]);
    }
    inline int New()
    {
        node++;
        suffix[node]=root, sf[node]=root;
        memset(tr[node],-1,sizeof tr[node]);
        return node;
    }
    inline void insert(string &s, int pos, int f)
    {
        int cur = root;
        for(int i=0;i<s.size();i++)
        {
            int c = s[i]-'a';
            if(tr[cur][c]==-1)
            {
                int nd = New();
                tr[cur][c] = nd;
            }
            cur = tr[cur][c];
        }
        if(f)ed[pos] = cur;
        End[cur]++;
    }
    void reverse_link()
    {
        queue<int>qu;
        for(int i=0;i<26;i++)
        {
            if(tr[root][i]!=-1)
            {
                qu.push(tr[root][i]);
                if(End[tr[root][i]])
                    cnt[tr[root][i]] = End[tr[root][i]];
            }
            else tr[root][i] = root;
        }
        while(!qu.empty())
        {
            int u = qu.front();
            qu.pop();
            for(int i=0;i<26;i++)
            {
                int v = tr[u][i];
                if(v==-1)
                {
                    tr[u][i] = tr[suffix[u]][i];
                    continue;
                }
                suffix[v] = tr[suffix[u]][i];
                qu.push(v);

                if(End[v]) cnt[v] = End[v]+cnt[suffix[v]];
                else       cnt[v] = cnt[suffix[v]];

                if(End[suffix[v]]) sf[v] = suffix[v];
                else               sf[v] = sf[suffix[v]];
            }
        }
    }
    int search(string &s)
    {
        int cur = root, sum = 0;
        for(int i=0;i<s.size();i++)
        {
            int c = s[i]-'a';
            cur = tr[cur][c];
            sum+=cnt[cur];
        }
        return sum;
    }
    void search2(string &s)
    {
        for(int i=0;i<vc.size();i++)
        {
            fr[vc[i]]=0;
        }
        vc.clear();

        int cur = root;
        for(int i=0;i<s.size();i++)
        {
            int c = s[i]-'a';
            cur = tr[cur][c];

            int now = cur;
            while(now>root)
            {
                if(End[now])
                {
                    fr[now]++;
                    vc.push_back(now);
                }
                now = sf[now];
            }
        }
    }
};
Aho_Corasick ac,ah[352];
string s[mx];
vector<int>q[mx];
ll ans[mx],res[mx];
int main()
{
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int n,m;
    cin >> n >> m;
    int sq = sqrt(n)+2;
    for(int i=1;i<=n;i++)
    {
        cin >> s[i];
        int k = (i/sq)+(i%sq!=0);
        ah[k].insert(s[i],i,0);
        ac.insert(s[i],i,1);
    }
    ac.reverse_link();
    int k = (n/sq)+(n%sq!=0);
    for(int i=1;i<=sq;i++)
    {
        ah[i].reverse_link();
    }
    int l,r,id;
    for(int i=1;i<=m;i++)
    {
        cin >> l >> r >> id;
        q[id].push_back(l);
        q[id].push_back(r);
        q[id].push_back(i);
    }
    for(k=1;k<=n;k++)
    {
        if(!q[k].size())continue;
        ac.search2(s[k]);
        for(int i=1;i<=sq;i++)
        {
            res[i]=ah[i].search(s[k]);
        }
        for(int j=0;j<q[k].size();j+=3)
        {
            l = q[k][j], r = q[k][j+1], id = q[k][j+2];
            int lft = (l/sq)+(l%sq!=0)+((l-1)%sq!=0);
            int rgt = (r/sq);
            ans[id] = 0;
            for(int i=lft;i<=rgt;i++)
            {
                ans[id]+=res[i];
            }
            if(lft-1>0)
            {
                for(int i=l;i<=(lft-1)*sq && i<=r;i++)
                    ans[id]+=fr[ed[i]];
            }
            if(lft-1 != rgt+1)
            {
                for(int i=rgt*sq+1;i<=r;i++)
                {
                    ans[id]+=fr[ed[i]];
                }
            }
        }
    }
    for(int i=1;i<=m;i++)
    {
        cout << ans[i] << "\n";
    }
    return 0;
}
/***********************************************************************/
