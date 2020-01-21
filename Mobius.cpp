/**
mob[n] = +1, if n has odd number of distinct prime factor
mob[n] = -1, if n has even number of distinct prime factor
mob[n] = 0, if n has a prime factor more than one time

Depend on problem +1 / -1 value can be interchange

Example:
    mob(n) = 0 , if n has one or more repeated prime factor
    mob(n) = 1 , if n=1
    mob(n) = (-1)^k , if n is a product of k distinct prime
Here, mob[n] = -1, if n has odd number of distinct prime factor
and vice-versa
*/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000'005;

int mobius[maxn];
void precallMobius(int n = 1000'000)
{
    mobius[1] = 1;
    for(int i=1; i<=n; i++)
    {
        for(int j=i+i; j<=n; j+= i)
        {
            mobius[j] -= mobius[i];
        }
    }
}

//Using linear sieve technique
vector<int>prime;
bool is_composite[maxn];
int mob[maxn];
void calculateMobius(int n = 1000'000)
{
    mob[1] = 1;
    for(int i=2; i<=n; i++)
    {
        if(!is_composite[i])
        {
            prime.push_back(i);
            mob[i] = -1;
        }
        for(int j=0; j<prime.size() && i*prime[j]<=n; j++)
        {
            is_composite[i * prime[j]] = true;
            if(i % prime[j] == 0)
            {
                mob[i * prime[j]] = 0;
                break;
            }
            else
            {
                mob[i * prime[j]] = mob[i] * mob[prime[j]];
            }
        }
    }
}

int main()
{
    precallMobius();
    //calculateMobius();
    for(int i=1; i<=20; i++)
    {
        cout<<i<<" = "<<mobius[i]<<endl;
    }
}
