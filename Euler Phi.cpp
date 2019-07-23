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
