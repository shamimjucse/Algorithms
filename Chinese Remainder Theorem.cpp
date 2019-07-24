#include<bits/stdc++.h>
using namespace std;
template<class T> T egcd(T a, T b, T &x, T &y)///return ax+by=gcd(a,b)
{
    if(b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    T x1, y1;
    T g = egcd(b, a%b, x1, y1);
    x = y1, y = x1-(a/b)*y1;
    return g;
}
///Chinese remainder theorem:
/** Works for non-coprime moduli.Returns -1 if solution does not exist or input
 is invalid.Otherwise, returns x, where x is the solution unique to mod L */

typedef __int128 INT;///Test first for support __int128
template<class T> T chinese_remainder_theorem( vector<T> M, vector<T> A )
{
    /**return x,L such that x%M[i]=A[i] and L is such number where x is unique*/
    if(A.size() != M.size())
        return -1; /** Invalid input*/
    int n = A.size();
    INT a1 = A[0];
    INT m1 = M[0];
    /** Initially x = a_0 (mod m_0)*/
    /** Merge the solution with remaining equations */
    for ( int i = 1; i < n; i++ )
    {
        INT a2 = A[i];
        INT m2 = M[i];
        INT g = __gcd(m1, m2);
        if ( a1 % g != a2 % g )
            return -1; /** No solution exists*/
        /** Merge the two equations*/
        INT p, q;
        egcd(m1/g, m2/g, p, q);
        INT mod = (m1 / g) * m2; /** LCM of m1 and m2*/
        /** We need to be careful about overflow, but I did not bother about overflow here to keep the code simple.*/
        INT x = (a1*   (((m2/g)*q)%mod) + a2* (((m1/g)*p) %mod ) ) % mod;
        /** Merged equation*/
        a1 = x;
        if (a1 < 0)
            a1 += mod; /** Result is not suppose to be negative*/
        m1 = mod;
    }
    return a1==0 ? m1 : a1;
}
