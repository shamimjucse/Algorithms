#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll P[10002];
ll longestPalindrome(string s)
{
    string st = "@";
    for(ll i=0;i<s.size();i++)
    {
        st+='#';
        st+=s[i];
    }
    st+="#$";
    for(ll i=0;i<=st.size();i++)P[i]=0;
    ll c = 0, r = 0;
    for(ll i=1;i<st.size()-1;i++)
    {
        ll i_Miror = 2*c-i;
        if(r > i) P[i]=min(r-i, P[i_Miror]);
        while(st[i+1+P[i]]==st[i-1-P[i]])
        {
            P[i]++;
        }
        if(i+P[i]>r)
        {
            c=i;
            r=i+P[i];
        }
    }
    ll len=0,id=0;
    for(ll i=1;i<st.size()-1;i++)
    {
        if(P[i]>len)
        {
            len=P[i];
            id=i;
        }
    }
    //return s.substr((id-1-len)/2,len);
    return len;
}
int main()
{
    ll i,j,p,tc,k;
    string s;
    cin >> tc;
    while(tc--)
    {
        cin >> s;
        p=longestPalindrome(s);
        cout << p << endl;
    }
    return 0;
}
