/// Light OJ - 1255 - Substring Frequency
#include<bits/stdc++.h>
#define MX 1000010
using namespace std;
int lps[MX];
void Preprocess(string P)
{
    int i=0,j=-1,l=P.size();
    lps[0]=-1;
    while(i < l)
    {
        while(j>=0 && P[i]!=P[j]) j=lps[j];
        lps[++i] = ++j;
    }
}
int kmpSearch(string T, string P)
{
    Preprocess(P);
    int i=0, j=0, cnt=0, l=T.size();
    while(i < l)
    {
        while (j >= 0 && T[i] != P[j]) j=lps[j];
        i++, j++;
        if(j == P.size())cnt++, j=lps[j];
    }
    return cnt;
}
int main()
{
    string txt,patn;
    int i,j,tc,ans,t=1;
    cin >> tc;
    while(tc--)
    {
        cin >> txt >> patn;
        ans = kmpSearch(txt,patn);
        cout << "Case " << t++ << ": " << ans << endl;
    }
    return 0;
}
