///Light OJ - 1314
#include<bits/stdc++.h>
#define ll long long
#define MX 100010
using namespace std;
char txt[MX];
int L,RA[MX],tRA[MX],SA[MX],tSA[MX],a[MX];
void countingSort(int k)
{
    int i,sm,p=max(300,L),q;
    memset(a,0,sizeof a);
    for(i=0; i<L; i++)a[i+k<L?RA[i+k]:0]++;
    for(sm=0,i=0; i<p; i++)q=a[i],a[i]=sm,sm+=q;
    for(i=0; i<L; i++)tSA[a[SA[i]+k<L?RA[SA[i]+k]:0]++]=SA[i];
    for(i=0; i<L; i++)SA[i]=tSA[i];
}
void constructSA()///SA[] is 0 indexing
{
    int i,k,r;
    for(i=0; i<L; i++) RA[i]=txt[i], SA[i]=i;
    for(k=1; k<L; k <<= 1)
    {
        countingSort(k), countingSort(0);
        tRA[SA[0]] = r = 0;
        for(i=1; i<L; i++)tRA[SA[i]]=
                (RA[SA[i]]==RA[SA[i-1]]&&RA[SA[i]+k]==RA[SA[i-1]+k])?r:++r;
        for(i=0; i<L; i++)RA[i]=tRA[i];
        if(RA[SA[L-1]]==L-1) break;
    }
}
int b[MX],LCP[MX],tLCP[MX];
void computeLCP()
{
    int i,l;
    b[SA[0]] = -1;
    for(i=1; i<L; i++) b[SA[i]] = SA[i-1];
    for(l=0,i=0; i<L; i++)
    {
        if(b[i]==-1)
        {
            tLCP[i]=0;
            continue;
        }
        while(txt[i+l]==txt[b[i]+l])l++;
        tLCP[i] = l, l = max(l-1,0);
    }
    for(i=0; i<L; i++) LCP[i]=tLCP[SA[i]];
}
void print_SA()
{
    for(int i=0; i<L; i++) printf("%2d\t%s\n", SA[i], txt + SA[i]);
    for(int i=0; i<L; i++) printf("%2d\t%d\n", SA[i], LCP[i]);
}
int main()
{
    int i,j,k,l,r,n,m,tc,t=1;
    scanf("%d",&tc);
    while(tc--)
    {
        cin >> txt;
        L = strlen(txt)+1;
        scanf("%d %d",&m,&n);
        constructSA();
        computeLCP();
        //print_SA();
        int sm = 0;
        for(i=0; i<L; i++)
        {
            k = L-(SA[i]+1);
            r = min(n,k);
            l = max(LCP[i]+1,m);
            if(l<=r) sm+=(r-l+1);
        }
        printf("Case %d: %d\n",t++,sm);
    }
    return 0;
}
