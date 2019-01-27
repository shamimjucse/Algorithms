///UVALive - 4682 (XOR Sum)
#include<bits/stdc++.h>
using namespace std;
int node, trie[4000002][2];
void Insert(int x)
{
    int cur = 0;
    for(int i=31; i>=0; i--)
    {
        int bit = (x>>i)&1;
        if(!trie[cur][bit])trie[cur][bit]=node++;
        cur = trie[cur][bit];
    }
}
int MaxQuery(int x)
{
    int ret = 0, cur = 0;
    for(int i=31; i>=0; i--)
    {
        int bit = (x>>i)&1;
        if(trie[cur][bit^1])
            ret|=(1<<i),cur = trie[cur][bit^1];
        else
            cur = trie[cur][bit];
    }
    return ret;
}
int main()
{
    int i,j,m,n,sm,ans,tc;
    cin >> tc;
    while(tc--)
    {
        cin >> n;
        memset(trie,0,sizeof trie);
        sm = 0, ans = 0;
        node = 1;
        Insert(0);
        for(i=1; i<=n; i++)
        {
            cin >> m;
            sm^=m;
            Insert(sm);
            ans=max(ans,MaxQuery(sm));
        }
        cout << ans << endl;
    }
    return 0;
}
