#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll Z[2000008];
vector<ll>v;
void calculate(string s)
{
    ll len=s.size();
    ll l=0,r=0,i,k;
    for(i=1; i<len; i++)
    {
        if(i>r)
        {
            l=r=i;
            while(r<len && s[r-l]==s[r])
            {
                r++;
            }
            Z[i]=r-l;
            r--;
        }
        else
        {
            k=i-l;
            if(Z[k]<r-i+1)
            {
                Z[i]=Z[k];
            }
            else
            {
                l=i;
                while(r<len && s[r-l]==s[r])
                {
                    r++;
                }
                Z[i]=r-l;
                r--;
            }
        }
    }
}
void match(string s, string p)
{
    string nw=p+"#"+s;
    ll l=p.size();
    calculate(nw);
    for(ll i=0; i<nw.size(); i++)
    {
        if(Z[i]==l)
        {
            v.push_back(i-l);/// 1 indexing
        }
    }
}
int main()
{
    string str,pattern;
    getline(cin,str);
    getline(cin,pattern);
    //calculate(str);
    match(str,pattern);
    if(v.size()==0)
    {
        cout << "Not Found\n" << endl;
    }
    else
    {
        for(ll i=0; i<v.size(); i++)
        {
            cout << v[i] << " ";/// 1 indexing
        }
        cout << endl;
    }
    return 0;
}
