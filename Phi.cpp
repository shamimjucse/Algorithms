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

/*
Few properties of phi function :
    a). phi(p) = p - 1. Where p is prime. All the numbers from 1 to p - 1 are coprime to p.
    b). phi(a * b) = phi(a) * phi(b) where a and b are coprime.
    c). phi(p^k) = p^k - p^(k - 1). Note that here ^ denotes power. Here all the numbers from 1 to p^k are 
    coprime to p^k except all the multiples of p, which are exactly p^(k -1).
*/
