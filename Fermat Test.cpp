#include <bits/stdc++.h>
using namespace std;

template<class T>inline T power(T a, T b, T m)
{
    a%=m;
    T ans=1%m;
    while(b)
    {
        if(b&1)
            ans = (ans*a)%m;
        a = (a*a)%m;
        b>>=1;
    }
    return ans;
}
template<class T>inline T gcd(T x, T y)
{
    if(!x || !y)
        return x+y;
    T t;
    while(x%y)
        t=x, x=y, y=t%y;
    return y;
}
template<class T> bool isPrime(T n, int k=100)// Try k times
{
   if(n<=1 || n==4)return false;
   if(n<=3)return true;
   while(k--)
   {
       T a = 2 + rand()%(n-4);
       if (gcd(n,a) != 1)
          return false;
       if (power(a, n-1, n) != 1)
          return false;
    }
    return true;//prime
}
int main()
{
    long long n;
    cin >> n;
    if(isPrime(n))cout << "Prime" << endl;
    else cout << "Not Prime" << endl;
    return 0;
}
///Not a good solution.
///It's 10963707205259 but the code return false
