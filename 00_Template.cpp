///**************************************//
///          Md: Shamim Imtiaz           //
///  Jahangirnagar University(45 Batch)  //
///     LightOJ-37238,Timus-253658KP     //
///   UVA-S_azad,CF&Others-shamimjucse   //
///                                      //
///**************************************//

#include<bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

/*-----------------------------*/

#define  READ   freopen("C:\\Users\\shami\\Desktop\\input.txt","r",stdin)
#define  WRITE  freopen("C:\\Users\\shami\\Desktop\\output.txt","w",stdout)
#define  _IO    ios_base::sync_with_stdio(0); cin.tie(0);cout.tie(0);

#define MX      200000000000LL
#define mod     1000000007LL
#define eps     0.000000001
#define inf     999999999999999LL
#define pi      2*acos(0.00)

#define D       double
#define ld      long double
#define ll      long long int
#define ul      unsigned int
#define ull     unsigned long long int

#define F       first
#define S       second
#define FF      first.first
#define FS      first.second
#define SF      second.first
#define SS      second.second

#define cl(v)         v.clear()
#define SZ(s)         s.size()
#define pb(a)         push_back(a)
#define mk(a,b)       make_pair(a,b)
#define all(v)        v.begin(),v.end()
#define allcl(i,n,v)  for(int i=0;i<=n;i++)v[i].clear()

#define cn1(a)        cin >> a
#define cn2(a,b)      cin >> a >> b
#define cn3(a,b,c)    cin >> a >> b >> c

#define nl            cout << endl
#define co(s)         cout << s
#define co1(a)        cout << a
#define TC            "Case " << t++ << ": "
#define co2(a,b)      cout << a << " " << b
#define co3(a,b,c)    cout << a << " " << b << " " << c

#define sc            scanf
#define sc1(a)        scanf("%lld",&a)
#define sc2(a,b)      scanf("%lld%lld",&a,&b)
#define sc3(a,b,c)    scanf("%lld%lld%lld",&a,&b,&c)
#define scu1(a)       scanf("%llu",&a)
#define scu2(a,b)     scanf("%llu%llu",&a,&b)
#define scu3(a,b,c)   scanf("%llu%llu%llu",&a,&b,&c)
#define sci1(a)       scanf("%d",&a)
#define sci2(a,b)     scanf("%d%d",&a,&b)
#define sci3(a,b,c)   scanf("%d%d%d",&a,&b,&c)
#define scd1(a)       scanf("%lf",&a)
#define scd2(a,b)     scanf("%lf%lf",&a,&b)
#define scd3(a,b,c)   scanf("%lf%lf%lf",&a,&b,&c)

#define pf          printf
#define pfnl        printf("\n")
#define pftc        printf("Case %lld: ",t++)
#define pf1(a)      printf("%lld",a)
#define pf2(a,b)    printf("%lld %lld",a,b)
#define pfi1(a)     printf("%d",a)
#define pfi2(a,b)   printf("%d %d",a,b)
#define pfu1(a)     printf("%llu",a)
#define pfu2(a,b)   printf("%llu %llu",a,b)

#define w1(a)       while(scanf("%lld",&a)==1)
#define w2(a,b)     while(scanf("%lld%lld",&a,&b)==2)
#define w3(a,b,c)   while(scanf("%lld%lld%lld",&a,&b,&c)==3)
#define wi1(a)      while(scanf("%d",&a)==1)
#define wi2(a,b)    while(scanf("%d%d",&a,&b)==2)
#define wu1(a)      while(scanf("%llu",&a)==1)
#define wu2(a,b)    while(scanf("%llu%llu",&a,&b)==2)
#define wd1(a)      while(scanf("%lf",&a)==1)
#define wd1(a)      while(scanf("%lf%lf",&a,&b)==2)

#define mem0(a)     memset(a,0,sizeof a)
#define mem1(a)     memset(a,-1,sizeof a)

#define fr(i,l,r)   for(int i=l;i<=r;i++)
#define frr(i,l,r)  for(i=r;i>=l;i--)
#define fr0(i,n)    for(int i=0; i<n; i++)
#define fr1(i,n)    for(int i=1; i<=n; i++)
#define frr0(i,n)   for(int i=n-1;i>=0;i--)
#define frr1(i,n)   for(int i=n;i>0;i--)

/*-----------------------------*/

///Move 4,8,bishop
ll p4[]= {-1,1,0,0};
ll q4[]= {0,0,1,-1};
ll p8[]= {-1,1,0,0,-1,1,-1,1};
ll q8[]= {0,0,1,-1,1,1,-1,-1};
ll dr[]= {2, 2, -2, -2, 1, -1, 1, -1};
ll dc[]= {1,-1,  1, -1, 2,  2,-2, -2};

/////bit
//ll bit[1000005],_n,_len;
//void update(ll i, ll val)  {while(i<=_n){bit[i]+=val;i+=(i&(-i));}}
//ll query(ll i)             {ll sum=0;while(i>0){sum+=bit[i];i-=(i&(-i));}return sum;}
//ll select(ll k)            {ll i,p,h=0;for(i=_len;i>=0;i--){p=1<<i;if(p+h>_n) continue;if(bit[p+h]<k){h+=p;k-=bit[h];}}return h+1;}

/////geometri_basic
//struct Point{double x,y;};
//struct StateLine{double x,y,c;};
//StateLine line(Point A, Point B)    {StateLine L;L.x=A.y-B.y;L.y=B.x-A.x;L.c=A.x*B.y-B.x*A.y;return L;}
//StateLine lombo_line(Point A, Point B)
//{Point M;M.x=(A.x+B.x)/2.00;M.y=(A.y+B.y)/2.00;StateLine L;L.x=A.x-B.x;L.y=A.y-B.y;L.c=M.x*B.x-M.x*A.x+M.y*B.y-M.y*A.y;return L;}
//Point cordinate(StateLine A, StateLine B)
//{Point P;P.x=(A.y*B.c-B.y*A.c)/(A.x*B.y-B.x*A.y);P.y=(B.x*A.c-A.x*B.c)/(A.x*B.y-B.x*A.y);return P;}
//double Distance(Point A, Point B)   {return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));}

/////Ordered Set
//typedef tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update>order_set;
//typedef tree<pair<ll,ll>,null_type,less<pair<ll,ll>>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;
////*st.find_by_order(x) && st.order_of_key(x)
//typedef trie<string,null_type,trie_string_access_traits<>,pat_trie_tag,trie_prefix_search_node_update>prefix_trie;
////auto range = st.prefix_range(string) && (auto it=range.first;it!=range.second;it++)

/////gcd/bigmod
//ll gcd(ll a, ll b)              {if(b>a)gcd(b,a);return ((b==0)?a:gcd(b,a%b));}
//ll lcm(ll a, ll b)              {ll p=(a*b)/(gcd(a,b));return p;}
//ll BigMod(ll a,ll b,ll m)       {if(!b)return 1;ll ans = BigMod(a, b/2, m);ans = (ans*ans)%m;if(b&1) ans = (ans*a)%m;return ans;}
//ll Mod_inv(ll a, ll m)          {return BigMod(a,m-2,m);}
//ll sum(ll a, ll b, ll m)        {return a>=m-b?a-(m-b):a+b;}
//ll multiply(ll a, ll b, ll m)   {ll ans=0;if(b>a)swap(a,b);while(b){if(b&1)ans=sum(ans,a,m);b>>=1;a=sum(a,a,m);}return ans;}

/*-----------------------------*/

//ll a[1000005],b[1000005];
//vector<ll>v,v1,v2;
//map<ll,ll>mp;
//priority_queue<ll>pq;
string s,s1,s2;
int main()
{
    ll i,j,k;
    ll l,m,n,c,d,p,q,r;
    ll cs=0,tc,t=1,flg,f,sm;
    //while(cin >> n)
    cin >> tc;
    while(tc--)
	{
//		cin >> n;
//		for(i=0;i<n;i++)
//		{
//			cin >> a[i];
//		}
	}
    return 0;
}
