/*****************************************************************
 * Algorithm  : Suffix Automation
 * Author     : Md Shamim Imtiaz (shamimjucse)
 * Memory     : O(2*n)
 * Complexity : O(nlogk), k is char size
 * Cover Area : Build Suffix Automation, Count Occurrence,
                String Matching, Distinct Substring,
                Sum of length of all Distinct substring,
                Smallest non-appearing substring,
                Longest common substring of two strings,
                Longest Common Substring of Multiple Strings,
                Find pattern with at most K mismatch,
                Smallest cyclic shift, Position of all occurrence
 * Problem    : SPOJ - LCS,NSUBSTR,LCS2,SUBLEX   HDU - 4622,4641
 *****************************************************************/

#include<bits/stdc++.h>
using namespace std;

const int mx = 300000;
struct node
{
    int len,link,real,next[26];
};

int last,avl;
node sa[2*mx];
//int pos[2*mx];//problem specific
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
            //pos[clone] = pos[q];//problem specific
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
        //pos[last] = i;//problem specific
    }
    return root;
}
/********************************************/

///Number of substring end this position
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
/********************************************/

///String Matching
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
/********************************************/

///Distinct Substring: ds[v] = 1 + ∑ ds[w]
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

/********************************************/

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
/********************************************/

///Lexicographically k-th Substring Search:
///Depends on: call distSub(root) to precal ds[]
string ans;//do ( ans.clear() ) for each call
void klex(int cur, int k)
{
    for(int i=0; i<26; i++)
    {
        if(sa[cur].next[i] && k)
        {
            int path = ds[sa[cur].next[i]];
            if(path >= k)
            {
                ans.push_back(i+'a');
                klex(sa[cur].next[i], k-1);
                break;
            }
            else k-=path;
        }
    }
}
/********************************************/

///Smallest non-appearing substring :
int d[mx];
int dfs(int u)
{
    if(u==0)return u;
    if(d[u])return d[u];
    d[u] = 26; //change it
    for(int i=0;i<26;i++)
    {
        d[u] = min(d[u], 1+dfs(sa[u].next[i]));
    }
    return d[u];
}
string out;
void print(int u)
{
    if(u==0)return;
    for(int i=0;i<26;i++)
    {
        if(d[u] == 1 + dfs(sa[u].next[i]))
        {
            out.push_back(i+'a');
            print(sa[u].next[i]);
            return;
        }
    }
}
/********************************************/

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
/********************************************/

///Longest Common Substring of Multiple Strings
string LCS(vector<string>st)
{
    int n = st.size()-1;
    vector<int> root(n);
    for(int i=0; i<n; i++)
        root[i] = automata(st[i]);

    string T = st[n];
    vector<int>cur = root;
    int l = 0, best = 0, pos = 0;
    for(int i=0; i<T.size(); i++)
    {
        int c = T[i]-'a';///Check it
        for(int k=0; k<n; k++)
        {
            while(cur[k]!=root[k] && sa[cur[k]].next[c]==0)
            {
                cur[k] = sa[cur[k]].link;
                l = min(l, sa[cur[k]].len);
            }

        }
        bool flg = 1;
        for(int k=0; k<n; k++)
            if(sa[cur[k]].next[c]==0)
                flg = 0;
        if(flg)
        {
            for(int k=0; k<n; k++)
                cur[k] = sa[cur[k]].next[c];
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
/********************************************/

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
/********************************************/

///Smallest cyclic shift:
///first element go to the last position, abc->bca
int minshift(int cur, int l, int length)
{
    for(int i=0;i<26;i++)
    {
        if(sa[cur].next[i])
        {
            if(l+1==length)
            {
                return pos[cur];
            }
            return minshift(sa[cur].next[i],l+1,length);
        }
    }
}
int minshift(string s)
{
    int root = automata(s+s);//int automata(string s)
    int l = s.size();
    return minshift(root,0,l)-l+2;
}
/********************************************/

///Position of all occurrence of the query string
vector<int>vec[2*mx],occur;
void makeTree(int root)
{
    for(int i=root; i<=avl; i++)
        vec[sa[i].link].push_back(i);
}
void find_all_occurrence(int cur, int l)
{
    if(sa[cur].real)
        occur.push_back(pos[cur]-l+1);
    for(auto u : vec[cur])
        find_all_occurrence(u,l);
}
void firstOccurrence(int cur, string T)
{
    makeTree(cur);
    for(int i=0; i<T.size(); i++)
    {
        int c = T[i]-'a'; //check it
        if(!sa[cur].next[c])return;//not exists
        cur = sa[cur].next[c];
    }
    find_all_occurrence(cur,T.size());
}
/********************************************/
