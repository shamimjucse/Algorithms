#include<bits/stdc++.h>
using namespace std;

const int maxn = 1000'005;

int phi[maxn];
void computeTotientPhi(int n = 1000'000)
{
    phi[1] = 1;
    for(int i=2; i<=n; i++)
    {
        if(phi[i]==0)
        {
            phi[i] = i-1 ;
            for(int j=i+i; j<=n; j+=i)
            {
                if(phi[j]==0)phi[j] = j;
                phi[j] = phi[j] - phi[j]/i ;
            }
        }
    }
}

/******************************/
bool vis[maxn];
void calculatePhi(int n = 1000'000)
{
    for(int i=0; i<=n; i++)phi[i] = i;
    for(int i=2; i<=n; i++)
    {
        if(not vis[i])
        {
            for(int j=i; j<=n; j+=i)
            {
                vis[j] = 1;
                phi[j]-=phi[j]/i;
            }
        }
    }
}
/******************************/
vector<int>prime;
bool is_composite[maxn];
void eulerPhi(int n = 1000'000)
{
    phi[1] = 1;
    for(int i=2; i<=n; i++)
    {
        if(!is_composite[i])
        {
            prime.push_back(i);
            phi[i] = i-1; ///i is prime
        }
        for(int j=0; j<prime.size() && i*prime[j]<=n; j++)
        {
            is_composite[i*prime[j]] = 1;
            if(i%prime[j] == 0)
            {
                phi[i*prime[j]] = phi[i] * prime[j]; ///prime[j] divides i
                break;
            }
            else
            {
                phi[i*prime[j]] = phi[i] * phi[prime[j]]; ///prime[j] does not divide i
            }
        }
    }
}
/*******************************/

int main()
{
    computeTotientPhi();
    //calculatePhi();
    //eulerPhi();

    for(int i=1;i<=100;i++)
    {
        cout << i << " = " << phi[i] << endl;
    }
}


/*
Few properties of phi function :
    a). phi(p) = p - 1. Where p is prime. All the numbers from 1 to p - 1 are coprime to p.
    b). phi(a * b) = phi(a) * phi(b) where a and b are coprime.
    c). phi(p^k) = p^k - p^(k - 1). Note that here ^ denotes power. Here all the numbers from 1 to p^k are 
    coprime to p^k except all the multiples of p, which are exactly p^(k -1).
*/
