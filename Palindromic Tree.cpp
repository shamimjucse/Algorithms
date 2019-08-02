/**************************************************************************************
    Palindrome tree. Useful structure to deal with palindromes in strings. O(N)
    This code counts number of palindrome substrings of the string.
    Based on problem 1750 from informatics.mccme.ru:
    http://informatics.mccme.ru/moodle/mod/statements/view.php?chapterid=1750
    or https://www.spoj.com/problems/NUMOFPAL
**************************************************************************************/

#include<bits/stdc++.h>
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
int cnt[mx];
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
}
long long sm = 0;
void buildTree()
{
    initTree();
    for(int i=0;i<s.size();i++)
    {
        Insert(i);
        sm+=cnt[suff];
    }
}
int main()
{
    cin >> s;
    buildTree();
    cout << sm << endl;
    return 0;
}
