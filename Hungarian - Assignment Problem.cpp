///UVa - 10746
///Algoritm Complexity : O(n^3),correctly O(n^2*m)
#include<bits/stdc++.h>
#define T double //solution type
using namespace std;

const int mx = 502;
const T inf = 1e9;
T hun[mx][mx];
T hungarian(int n, int m)
{
    vector<T> u(n+1), v(m+1);
    vector<int> p(m+1), way(m+1);
    for(int i=1; i<=n; ++i)
    {
        p[0] = i;
        int j0 = 0;
        vector<T> minv(m+1, inf);
        vector<char> used(m+1, false);
        do
        {
            used[j0] = true;
            int i0 = p[j0], j1;
            T delta = inf;
            for (int j=1; j<=m; ++j)
            {
                if(!used[j])
                {
                    T cur = hun[i0][j]-u[i0]-v[j];
                    if(cur < minv[j]) minv[j] = cur,  way[j] = j0;
                    if(minv[j] < delta) delta = minv[j],  j1 = j;
                }
            }
            for(int j=0; j<=m; ++j)
            {
                if(used[j]) u[p[j]] += delta,  v[j] -= delta;
                else minv[j] -= delta;
            }
            j0 = j1;
        }
        while(p[j0] != 0);
        do
        {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        }
        while (j0);
    }
    T ret=0;
    for(int i=1;i<=m;i++)
        ret+=hun[p[i]][i];
    return ret;
}

int main()
{
    int n,m;
    while(cin >> n >> m && (n||m))
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                cin >> hun[i][j];
            }
        }
        double k = hungarian(n,m);
        double ans = k/(double)n + 1e-6;
        cout<<fixed<<setprecision(2)<<ans<<endl;
    }
    return 0;
}
