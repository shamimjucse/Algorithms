///Light OJ - 1127 ( Complexity O(2^(n/2)*n*log(n))
#include<bits/stdc++.h>
using namespace std;
vector<int> bitmask(vector<int>v, int w)
{
    vector<int> res;
    int l = v.size();
    for(int i=1;i<(1<<l);i++)
    {
        int fg = 0, sm = 0;
        for(int j=0;j<l;j++)
        {
            if(i&(1<<j))
            {
                if(sm<=w-v[j])///Careful about overflow
                {
                    sm+=v[j];
                }
                else
                {
                    fg = 1;
                    break;
                }
            }
        }
        if(!fg)res.push_back(sm);
    }
    return res;
}
int main()
{
    int tc,t=1;
    cin >> tc;
    while(tc--)
    {
        int n,w;
        cin >> n >> w;
        vector<int>lft,rgt;
        for(int i=1;i<=n/2;i++)
        {
            int p;
            cin >> p;
            lft.push_back(p);
        }
        for(int i=n/2+1;i<=n;i++)
        {
            int p;
            cin >> p;
            rgt.push_back(p);
        }
        lft = bitmask(lft,w);
        rgt = bitmask(rgt,w);

        int ans = lft.size()+rgt.size()+1;
        sort(rgt.begin(),rgt.end());
        for(int i=0;i<lft.size();i++)
        {
            ans+=upper_bound(rgt.begin(),rgt.end(),w-lft[i])-rgt.begin();
        }
        cout << "Case " << t++ << ": " << ans << "\n";
    }
    return 0;
}
