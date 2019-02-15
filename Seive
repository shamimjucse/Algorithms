#include<bits/stdc++.h>
#define ll long long
#define MX 1000000
using namespace std;

vector<ll>prime;
bool vis[MX+2];//1 for prime
void prime_seive()
{
    memset(vis,true,sizeof(vis));
    vis[0]=vis[1]=false;
    for(int i=4; i<=MX; i+=2) vis[i]=false;
    for(int i=3; i*i<=MX; i+=2)
        if(vis[i]) for(int j=i*i; j<=MX; j+=i+i) vis[j]=false;
    prime.push_back(2);
    for(int i=3;i<=MX;i+=2) if(vis[i]) prime.push_back(i);
}
ll prime_chek(ll a)
{
    prime_seive();
    if(a==1) return 1;
    else if(a==2) return 0;
    else if(a%2==0) return 1;
    else for(int i=1;i<prime.size()&&(prime[i]*prime[i]<=a);i++) if(a%prime[i]==0) return 1;
    return 0;
}

int main()
{
    prime_seive();
    cout << prime.size() << endl;
    return 0;
}
