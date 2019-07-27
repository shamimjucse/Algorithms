///Light OJ - 1315
#include<bits/stdc++.h>
using namespace std;
int dx[] = {-1,-1,-2,-3,-2,1};
int dy[] = {-3,-2,-1,-1,1,-2};

int dp[1009][1009];
int grandy(int x, int y)
{
    if(x<0 || y<0)return -1;
    int &ret = dp[x][y];
    if(~ret)return ret;
    ret = 0;
    int ar[6];
    for(int i=0;i<6;i++)
    {
        int nx = x+dx[i];
        int ny = y+dy[i];
        ar[i] = grandy(nx,ny);
    }
    sort(ar,ar+6);
    ///First value from (0-5) which is not calculated  here
    for(int i=0;i<6;i++)
    {
        if(ret==ar[i])ret++;
    }
    return ret;
}

int main()
{
    memset(dp,-1,sizeof dp);
    int tc,t=1;
    cin >> tc;
    while(tc--)
    {
        int n, res = 0;
        cin >> n;
        for(int i=0;i<n;i++)
        {
            int p,q;
            cin >> p >> q;
            res = res^grandy(p,q);
        }
        cout << "Case " << t++ << ": ";
        if(res)cout << "Alice" << endl;
        else   cout << "Bob" << endl;
    }
    return 0;
}
