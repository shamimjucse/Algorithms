///https://codeforces.com/contest/1195/problem/E
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int g[9000002],ar[3002][3002],ans[3002][3002];
void solution(int n, int m, int a, int b)
{
    int tmp[n+2][m+2];
    for(int i=1;i<=n;i++)
    {
        deque<int>dq;
        for(int j=1;j<=m;j++)
        {
            while(!dq.empty() && j-dq.front()+1 > b)
                dq.pop_front();
            while(!dq.empty() && ar[i][j]<ar[i][dq.back()])
                dq.pop_back();
            dq.push_back(j);
            tmp[i][j] = ar[i][dq.front()];
        }
    }
    for(int j=1;j<=m;j++)
    {
        deque<int>dq;
        for(int i=1;i<=n;i++)
        {
            while(!dq.empty() && i-dq.front()+1 > a)
                dq.pop_front();
            while(!dq.empty() && tmp[i][j]<tmp[dq.back()][j])
                dq.pop_back();
            dq.push_back(i);
            ans[i][j] = tmp[dq.front()][j];
        }
    }
}
int main()
{
    int i,j,n,m,a,b;
    int x,y,z;
    cin >> n >> m >> a >> b >> g[0] >> x >> y >> z;
    for(i=1;i<=n*m;i++)
    {
        g[i] = (1LL*g[i-1]*x+y)%z;
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            ar[i][j]=g[(i-1)*m+j-1LL];
        }
    }
    solution(n,m,a,b);
    ll sm = 0;
    for(i=a;i<=n;i++)
    {
        for(j=b;j<=m;j++)
        {
            sm+=ans[i][j];
        }
    }
    cout << sm << endl;
    return 0;
}
