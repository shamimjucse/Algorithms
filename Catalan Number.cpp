///Using Binomial Coefficient
///C(n) = binomial(2n,n)/(n+1) = (2n)!/(n!(n+1)!)
///1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786,....
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll CN[1002];
template<class T>T binomialCoeff(T n, T k)
{
    T res = 1;
    if(k>n-k)k=n-k;
    for(int i=0;i<k;i++)
    {
        res*=(n-i);
        res/=(i+1);
    }
    return res;
}
template<class T>T catalan(T n)///Takes O(n) time
{
    T cn = binomialCoeff(2*n,n);
    return cn/(n+1);
}
int main()
{
    for(ll i=0;i<=1000;i++)
        CN[i]=catalan(i);
    for(ll i=0;i<=1000;i++)
        cout << CN[i] << " ";
    cout << endl;
    return 0;
}
