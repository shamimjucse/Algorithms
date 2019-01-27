#include<bits/stdc++.h>
#define ll long long
#define mod 1000000000
using namespace std;
ll dimen;
struct matrix
{
    ll arr[2][2];
};
//void print(matrix a)
//{
//    for(ll i=0; i<dimen; i++)
//    {
//        for(ll j=0; j<dimen; j++)
//        {
//            cout << a.arr[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
//}
matrix operator*(matrix a, matrix b)
{
    matrix ans;
    for(ll i=0; i<dimen; i++)
    {
        for(ll j=0; j<dimen; j++)
        {
            ans.arr[i][j]=0;
            for(ll k=0; k<dimen; k++)
            {
                ans.arr[i][j]=(ans.arr[i][j]+(a.arr[i][k]*b.arr[k][j]))%mod;
            }
        }
    }
    return ans;
}
matrix Big_MOD(matrix a, ll n)
{
    matrix ans=a;
    while(n>0)
    {
        if(n&1)
        {
            ans=ans*a;
        }
        a=a*a;
        n/=2;
    }
    return ans;
}
int main()
{
    ll n,k,l,p;
    while(cin >> n >> k >> l)
    {
        n/=5;
        dimen=2;

        matrix base;
        base.arr[0][0]=k%mod;
        base.arr[0][1]=l%mod;
        base.arr[1][0]=1;
        base.arr[1][1]=0;

        matrix ans=Big_MOD(base,n-1);
        //print(ans);
        p=(ans.arr[0][0]%1000000);

        printf("%06lld\n",p);
    }
    return 0;
}
