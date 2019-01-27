#include<bits/stdc++.h>
#define ll long long
#define inf 9999999999999999LL
using namespace std;
ll dis[1005][1005];
void floyd_warshall(ll n)
{
    ll i,j,k;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            for(k=1;k<=n;k++)
            {
                if(dis[j][k]>dis[j][i]+dis[i][k])
                {
                    dis[j][k]=dis[j][i]+dis[i][k];
                }
            }
        }
    }
}
int main()
{
    ll i,j,m,n,p,q,c,qry,tc;
    cin >> tc;
    while(tc--)
    {
        cin >> n >> m;
        for(i=0;i<=n;i++)
        {
            for(j=0;j<=n;j++)
            {
                dis[i][j]=inf;
            }
        }
        for(i=1;i<=m;i++)
        {
            cin >> p >> q >> c;
            dis[p][q]=c;
            dis[q][p]=c;
        }
        floyd_warshall(n);
        cin >> qry;
        for(i=1;i<=qry;i++)
        {
            cin >> p >> q;
            if(dis[p][q]==inf)cout << "No Path" << endl;
            else cout << dis[p][q] << endl;
        }
    }
    return 0;
}
