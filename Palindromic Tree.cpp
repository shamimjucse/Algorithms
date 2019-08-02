/**************************************************************************************
    Palindrome tree. Useful structure to deal with palindromes in strings. O(N)
    This code counts number of palindrome substrings of the string.
    Based on problem 1750 from informatics.mccme.ru:
    http://informatics.mccme.ru/moodle/mod/statements/view.php?chapterid=1750
    or https://www.spoj.com/problems/NUMOFPAL
**************************************************************************************/

#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int mx = 100005;
struct Node
{
    int len,link,next[26];
};
string s;
Node tr[mx];
int node; /// node 1 - root with len -1, node 2 - root with len 0
int suff; /// max suffix palindrome
inline int New()
{
    node++;
    tr[node].len = 0, tr[node].link = 0;
    memset(tr[node].next, 0, sizeof tr[node].next);
    return node;
}
int cnt[mx],occ[mx];
inline bool Insert(int pos)
{
    int cur = suff, curlen = 0;
    int c = s[pos]-'a'; ///check it
    while(true) ///Finding maximum length palindromic suffix
    {
        curlen = tr[cur].len;
        if (pos-1-curlen>=0 && s[pos-1-curlen]==s[pos])
            break;
        cur = tr[cur].link;
    }
    if(tr[cur].next[c]) ///Existing node
    {
        suff = tr[cur].next[c];
        return false;
    }

    suff = New();
    tr[node].len = tr[cur].len + 2;
    tr[cur].next[c] = node;
    if(tr[node].len == 1) ///Single character, connected with root
    {
        tr[node].link = 2;
        cnt[node] = 1;
        return true;
    }
    while(true)///Finding suffix link
    {
        cur = tr[cur].link;
        curlen = tr[cur].len;
        if(pos-1-curlen>=0 && s[pos-1-curlen]==s[pos])
        {
            tr[node].link = tr[cur].next[c];
            break;
        }
    }
    cnt[node] = 1 + cnt[tr[node].link];
    return true;
}
void initTree()
{
    node = 2, suff = 2;
    tr[1].len = -1, tr[1].link = 1;
    tr[2].len = 0, tr[2].link = 1;
    memset(tr[1].next,0,sizeof tr[1].next);
    memset(tr[2].next,0,sizeof tr[2].next);
    memset(cnt,0,sizeof cnt);
    memset(occ,0,sizeof occ);
}
long long totalpalindreme = 0;
void buildTree()
{
    initTree();
    for(int i=0;i<s.size();i++)
    {
        Insert(i),occ[suff]++;
        totalpalindreme+=cnt[suff];
    }
}
ll countPalindromes()
{
    ll sum = 0;
    for(int i=node;i>2;i--)
    {
        occ[tr[i].link]+=occ[i];
        sum+=occ[i];
    }
    return sum;
}
int main()
{
    cin >> s;
    buildTree();
    //cout << totalpalindreme << endl;
    cout << countPalindromes() << endl;
    return 0;
}

/********************************************************************/
///Simple code

#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int mx = 300005;
int tr[mx][26], node;
int len[mx], link[mx],suff;
string s; /// 1-indexed
int cnt[mx],occ[mx];
inline void Insert(int p)
{
    while(s[p - len[suff] - 1] != s[p])
        suff = link[suff];
    int x = link[suff], c = s[p] - 'a';
    while(s[p - len[x] - 1] != s[p])
        x = link[x];
    if(!tr[suff][c])
    {
        tr[suff][c] = ++node;
        len[node] = len[suff] + 2;
        link[node] = (len[node] == 1) ? 2 : tr[x][c];
        cnt[node]+=1 + cnt[link[node]];
    }
    suff = tr[suff][c];
    occ[suff]++;
}
void initTree()
{
    node = 2, suff = 2;
    len[1] = -1, link[1] = 1;
    len[2] = 0, link[2] = 1;
    memset(tr,0,sizeof tr);
    memset(cnt,0,sizeof cnt);
    memset(occ,0,sizeof occ);
}
ll totalpalindreme = 0;
void buildTree()
{
    initTree();
    s = "#" + s;
    for(int i=1;i<s.size();i++)
    {
        Insert(i);
        totalpalindreme+=cnt[suff];
    }
}
ll countPalindromes()
{
    ll sum = 0;
    for(int i=node;i>2;i--)
    {
        occ[link[i]]+=occ[i];
        sum+=occ[i];
    }
    return sum;
}
int main()
{
    cin >> s;
    buildTree();
    cout << totalpalindreme << endl;
    //cout << countPalindromes() << endl;
    return 0;
}

