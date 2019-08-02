#include<bits/stdc++.h>
using namespace std;

const int mx = 300000;
struct node
{
    int len,link,real,next[26];
};

int last,avl;
node sa[2*mx];
inline int New()
{
    avl++;
    sa[avl].len = 0, sa[avl].link = 0, sa[avl].real = 0;
    memset(sa[avl].next, 0, sizeof sa[avl].next);
    return avl;
}
inline void Insert(int root, char ch)
{
    int cur = New();
    int c = ch-'a'; ///Check it
    sa[cur].real = 1;
    sa[cur].len = sa[last].len + 1;
    int p = last;
    while(p!=0 && !sa[p].next[c])
    {
        sa[p].next[c] = cur;
        p = sa[p].link;
    }
    if(p == 0)
    {
        sa[cur].link = root;
    }
    else
    {
        int q = sa[p].next[c];
        if(sa[p].len + 1 == sa[q].len)
        {
            sa[cur].link = q;
        }
        else
        {
            int clone = New();
            sa[clone].len = sa[p].len + 1;
            sa[clone].link = sa[q].link;
            memcpy(sa[clone].next,sa[q].next,sizeof(sa[clone].next));
            while (p!=0 && sa[p].next[c] == q)
            {
                sa[p].next[c] = clone;
                p = sa[p].link;
            }
            sa[cur].link = sa[q].link = clone;
        }
    }
    last = cur;
}
int automata(string &s)
{
    //avl = 0; //For testcase
    int root = New();
    last = root;
    for(int i=0;i<s.size();i++)
    {
        Insert(root, s[i]);
    }
    return root;
}

int cnt[2*mx];//Do memset for testcase
void count_Occurrence(int root)
{
    vector<pair<int,int>>vc;
    for(int i=root;i<=avl;i++)
    {
        cnt[i]=sa[i].real;
        vc.push_back({sa[i].len,i});
    }
    sort(vc.begin(),vc.end());
    for(int i=vc.size()-1;i>=0;i--)
    {
        int now = vc[i].second;
        cnt[sa[now].link]+=cnt[now];
    }
}

int search(int cur, string &s)
{
    //count_Occurrence(cur);//call this function in main()
    for(int i=0;i<s.size();i++)
    {
        if(sa[cur].next[s[i]-'a'])
        {
            cur = sa[cur].next[s[i]-'a'];
        }
        else return 0;
    }
    return cnt[cur]; //Number of occurrence
}

///Distinct substring: ds[v] = 1 + ∑ ds[w]
int ds[2*mx];//Do memset for testcase
int distSub(int u)
{
    if(ds[u])return ds[u];
    ds[u] = 1;
    for(int i=0; i<26; i++)
    {
        if(sa[u].next[i])
        {
            ds[u]+=distSub(sa[u].next[i]);
        }
    }
    return ds[u];//With empty string
}

///Sum of length of all Distinct substring: dp[v] = ∑ ds[w] + dp[w]
///Depends on: call distSub(root) to precal ds[]
int dp[2*mx];//Do memset for testcase
int lenSum(int u)
{
    if(dp[u])return dp[u];
    for(int i=0; i<26; i++)
    {
        if(sa[u].next[i])
        {
            dp[u]+=ds[sa[u].next[i]]+lenSum(sa[u].next[i]);
        }
    }
    return dp[u];
}

///Longest common substring of two strings
string LCS(string S, string T)
{
    int root = automata(S);
    int cur = root, l = 0, best = 0, pos = 0;
    for(int i=0;i<T.size();i++)
    {
        int c = T[i]-'a';///Check it
        while(cur!=root && sa[cur].next[c]==0)
        {
            cur = sa[cur].link;
            l = sa[cur].len;
        }
        if(sa[cur].next[c])
        {
            cur = sa[cur].next[c];
            l++;
        }
        if(l>best)
        {
            best = l;
            pos = i;
        }
    }
    //return best; //Length
    return T.substr(pos-best+1,best);
}

///Find a pattern with at most K mismatch:
string s; //Global string
int dfs(int u, int i, int k) //dfs(curRoot, curPos, remainingMismatch)
{
    if(u==0)return 0;
    if(i==s.size())return cnt[u];
    int c = s[i]-'a';
    int res = dfs(sa[u].next[c], i+1, k);
    if(k!=0)
    {
        for(int j=0;j<16;j++)
        {
            if(j!=c)
            {
                res+=dfs(sa[u].next[j], i+1, 0);
            }
        }
    }
    return res;
}
