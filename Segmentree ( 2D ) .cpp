#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[505][505],ar[3*502][3*502],n;
void build_y(ll px, ll sx, ll ex, ll py, ll sy, ll ey)
{
    if(sy==ey)
    {
        if(sx==ex) ar[px][py] = a[sx][sy];
        else ar[px][py]=max(ar[2*px][py],ar[2*px+1][py]);
        return;
    }
    ll mid = (sy+ey)>>1;
    build_y(px, sx, ex, 2*py, sy, mid);
    build_y(px, sx, ex, 2*py+1, mid+1, ey);
    ar[px][py]=max(ar[px][2*py],ar[px][2*py+1]);
}
void build_x(ll p, ll s, ll e)
{
    if(s!=e)
    {
        ll mid = (s+e)>>1;
        build_x(2*p, s, mid);
        build_x(2*p+1, mid+1, e);
    }
    build_y(p, s, e, 1, 1, n);
}
void update_y(ll px, ll sx, ll ex, ll py, ll sy, ll ey, ll y)
{
    if(sy==ey)
    {
        if(sx==ex) ar[px][py]=a[sx][sy];
        else ar[px][py]=max(ar[2*px][py],ar[2*px+1][py]);
        return;
    }
    ll mid=(sy+ey)>>1;
    if(mid>=y)update_y( px,sx,ex,2*py,sy,mid,y);
    else update_y( px,sx,ex,2*py+1,mid+1,ey,y);
    ar[px][py]=max(ar[px][2*py],ar[px][2*py+1]);
}
void update_x(ll p, ll s, ll e, ll x, ll y)
{
    if(s!=e)
    {
        ll mid=(s+e)>>1;
        if(mid>=x)update_x(2*p,s,mid,x,y);
        else update_x(2*p+1,mid+1,e,x,y);
    }
    update_y(p,s,e,1,1,n,y);
}
ll query_y(ll px, ll sx, ll ex, ll py, ll sy, ll ey, ll y1, ll y2)
{
    if(sy>=y1 && ey<=y2)
    {
        return ar[px][py];
    }
    ll mid = (sy+ey)>>1;
    if(mid>=y2)query_y(px,sx,ex,2*py,sy,mid,y1,y2);
    else if(mid<y1)query_y(px,sx,ex,2*py+1,mid+1,ey,y1,y2);
    else
    {
        ll q1=query_y(px,sx,ex,2*py,sy,mid,y1,mid);
        ll q2=query_y(px,sx,ex,2*py+1,mid+1,ey,mid+1,y2);
        return max(q1,q2);
    }
}
ll query_x(ll p, ll s, ll e, ll x1, ll x2, ll y1, ll y2)
{
    if(s>=x1 && e<=x2)
    {
        return query_y(p,s,e,1,1,n,y1,y2);
    }
    ll mid = (s+e)>>1;
    if(mid>=x2)return query_x(2*p,s,mid,x1,x2,y1,y2);
    else if(mid<x1)return query_x(2*p+1,mid+1,e,x1,x2,y1,y2);
    else
    {
        ll q1 = query_x(2*p,s,mid,x1,mid,y1,y2);
        ll q2 = query_x(2*p+1,mid+1,e,mid+1,x2,y1,y2);
        return max(q1,q2);
    }
}
int main()
{
    ll i,j,k,m,tc,t=1,f;
    ll x1,x2,y1,y2;
    scanf("%lld",&tc);
    while(tc--)
    {
        scanf("%lld %lld",&n,&m);
        for(i=1; i<=n; i++)
        {
            for(j=1; j<=n; j++)
            {
                scanf("%lld",&a[i][j]);
            }
        }
        build_x(1,1,n);
        printf("Case %lld:\n",t++);
        for(i=1; i<=m; i++)
        {
            scanf("%lld",&f);
            if(f==1)
            {
                scanf("%lld %lld %lld %lld",&x1,&y1,&x2,&y2);
                k = query_x(1,1,n,x1,x2,y1,y2);
                printf("%lld\n",k);
            }
            else
            {
                scanf("%lld %lld %lld",&x1,&y1,&k);
                a[x1][y1] = k;
                update_x(1,1,n,x1,y1);
            }
        }
    }
    return 0;
}
