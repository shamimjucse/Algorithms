///https://codeforces.com/problemset/problem/348/C
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define MX 100005
#define sq 318
using namespace std;
vector<int>heavy,vc[MX];
int a[MX],comon[sq][MX],vis[MX],ct;
ll sm[MX],up_hv[MX],up_lgt[MX];
int main()
{
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int n,m,i,j,k,qry,p,q;
    cin >> n >> m >> qry;
    for(i=1;i<=n;i++)
    {
        cin >> a[i];
    }
    for(i=1;i<=m;i++)
    {
        cin >> p;
        if(p>sq)heavy.pb(i);
        for(j=1;j<=p;j++)
        {
            cin >> q;
            sm[i]+=a[q];
            vc[i].push_back(q);
        }
    }
    // pre-proces
    for(i=0;i<heavy.size();i++)
    {
        ct++;
        p = heavy[i];
        for(j=0;j<vc[p].size();j++)
        {
            vis[vc[p][j]] = ct;
        }
        for(j=1;j<=m;j++)
        {
            for(k=0;k<vc[j].size();k++)
            {
                q = vc[j][k];
                if(vis[q]==ct)
                {
                    comon[i][j]++;
                }
            }
        }
    }
    // query
    while(qry--)
    {
        string s;
        cin >> s;

        // update
        if(s=="+")
        {
            cin >> p >> q;
            // heavy
            if(vc[p].size()>sq)up_hv[p]+=q;
            //light
            else
            {
                // for light
                for(i=0;i<vc[p].size();i++)
                {
                    up_lgt[vc[p][i]]+=q;
                }
                // for heavy
                for(i=0;i<heavy.size();i++)
                {
                    sm[heavy[i]]+=comon[i][p]*q;
                }
            }
        }
        // get result
        else
        {
            cin >> p;
            ll sum = sm[p];
            for(i=0;i<heavy.size();i++)
            {
                sum+=up_hv[heavy[i]]*comon[i][p];
            }
            if(vc[p].size()<=sq)
            {
                for(i=0;i<vc[p].size();i++)
                {
                    sum+=up_lgt[vc[p][i]];
                }
            }
            cout << sum << endl;
        }
    }
    return 0;
}
