#include<bits/stdc++.h>
#define eps 1e-12
using namespace std;
double mat[202][202],ans[202];

int GaussianElimination(int n)
{
    int i,j,k,row;
    for(j=0;j<n-1;j++)
    {
        row = j;
        for(i=j+1;i<n;i++)
        {
            if(fabs(mat[i][j])>fabs(mat[row][j]))
            {
                row = i;
            }
        }
        for(k=j;k<=n;k++)
        {
            double tmp=mat[j][k];
            mat[j][k]=mat[row][k];
            mat[row][k] = tmp;
        }
        for(i=j+1;i<n;i++)
        {
            for(k=n;k>=j;k--)
            {
                if(fabs(mat[j][j])<eps)continue;
                mat[i][k]-=mat[j][k]*mat[i][j]/mat[j][j];
            }
        }
    }
    if(fabs(mat[n-1][n-1])<eps)
    {
        if(fabs(mat[n-1][n-1]-mat[n-1][n])<eps)
        {
            return 1;
        }
        return -1;
    }
    for(j=n-1;j>=0;j--)
    {
        double sum = 0.0;
        for(k=j+1;k<n;k++)
        {
            sum+=mat[j][k]*ans[k];
        }
        ans[j]=(mat[j][k]-sum)/mat[j][j];
    }
    return 0;
}
int main()
{
    int i,j,n,m,p,q,tc;
    cin >> tc;
    while(tc--)
    {
        cin >> n;
        for(i=0;i<n;i++)
        {
            for(j=0;j<=n;j++)
            {
                cin >> mat[i][j];
            }
        }
        if(!GaussianElimination(n))
        {
            for(i=0;i<n;i++)
            {
                cout << "x" << i << " : ";
                cout << fixed << setprecision(5) << ans[i] << endl;
            }
        }
        else if(GaussianElimination(n)==-1)
        {
            cout << "No solution exists" << endl;
        }
        else
        {
            cout << "Many solution exists" << endl;
        }

        memset(mat,0,sizeof mat);
    }
    return 0;
}
