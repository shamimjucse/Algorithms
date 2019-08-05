ll phi[mx];
void computeTotientPhi(int N)
{
    phi[1] = 1 ;
    for(int i=2; i<=N; i++)
    {
        if(phi[i]==0)
        {
            phi[i] = i-1 ;
            for(int j=i+i; j<=N; j+=i)
            {
                if(phi[j]==0)
                    phi[j] = j ;
                phi[j] = phi[j] - phi[j]/i ;
            }
        }
    }
}

/******************************/
for(int i=0; i<=MX; i++)
    phi[i]=i;
for(int i=2; i<=MX; i++)
{
    if(not v[i])
    {
        for(int j=i; j<=MX; j+=i)
        {
            v[j]=1;
            phi[j]-=phi[j]/i;
        }
    }
}
/******************************/
