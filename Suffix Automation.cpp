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
    int root = New();
    last = root;
    for(int i=0;i<s.size();i++)
    {
        Insert(root, s[i]);
    }
    return root;
}

int cnt[2*mx];
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
