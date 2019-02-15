///SPOJ - SUBXOR
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int node,trie[1000000][2][2];
void Insert(int x)
{
    int cur = 0;
    for(int i=21; i>=0; i--)
    {
        int bit = (x>>i)&1;
        if(!trie[cur][bit][0])
            trie[cur][bit][0]=++node;
        trie[cur][bit][1]++;
        cur = trie[cur][bit][0];
    }
}
int Query(int x, int k)
{
    int flg = 0;
    int ret = 0, cur = 0;
    for(int i=21; i>=0; i--)
    {
        int bit = (x>>i)&1;
        int chek= (k>>i)&1;
        if(chek)
        {
            ret+= trie[cur][bit][1];
            cur = trie[cur][bit^1][0];
            if(cur==0) return ret;
        }
        else
        {
            cur = trie[cur][bit][0];
            if(cur==0) return ret;
        }
    }
    return ret;
}
int main()
{
    int i,j,n,m,k,sm,tc;
    cin >> tc;
    while(tc--)
    {
        cin >> n >> k;
        memset(trie,0,sizeof trie);
        sm = 0;
        ll ans = 0;
        node = 0;
        Insert(0);
        for(i=1; i<=n; i++)
        {
            cin >> m;
            sm^=m;
            ans+=Query(sm,k);
            Insert(sm);
        }
        cout << ans << endl;
    }
    return 0;
}
