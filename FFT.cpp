///https://toph.co/p/counting-triplets
#include<bits/stdc++.h>
#define ll long long
using namespace std;

/*
if bruteforce needed at some point,
consider eliminating zero frequency term
*/
///typedef complex<double> cpx ;
struct cpx{
	double r,i;
    cpx(){r=i=0;}
 	cpx(double real){r=real,i=0;}
 	cpx(double real,double imag){r=real,i=imag;}
 	inline double real(){return r;}
 	cpx operator + (cpx w){return cpx(r+w.r,i + w.i);}
 	cpx operator - (cpx w){return cpx(r-w.r,i - w.i);}
 	cpx operator /= (double x){r/=x,i/=x;return *this;}
 	cpx operator * (cpx w){return cpx(r*w.r-i*w.i,r*w.i+i*w.r);}
 	cpx operator *= (cpx w){return *this=cpx(r*w.r-i*w.i,r*w.i+i*w.r);}
};

const double PI = acos(-1);
void FFT(vector<cpx>&a, bool inv) //inv=true means inverse FFT
{
    int n = (int)a.size();
    for(int i=1,j=0; i<n; i++)
    {
        int bit = n >> 1;
        for( ; j>=bit; bit>>=1)
            j-=bit;
        j+=bit ;
        if(i<j)
            swap(a[i],a[j]);
    }
    for(int len=2; len<=n; len<<=1)
    {
        double ang = 2*PI/len*(inv?-1:1);
        cpx wlen(cos(ang),sin(ang));
        for(int i=0; i<n; i+=len)
        {
            cpx w(1) ;
            for(int j=0; j<len/2; j++)
            {
                cpx u=a[i+j], v=a[i+j+len/2]*w;
                a[i+j] = u+v ;
                a[i+j+len/2] = u-v;
                w*=wlen ;
            }
        }
    }
    if(inv)
    {
        for(int i=0; i<n; i++)
            a[i]/=n ;
    }
}

vector<long long>res;
void Mul(const vector<double>&a, const vector<double>&b)
{
    vector<cpx> fa(a.begin(),a.end()), fb(b.begin(),b.end());
    size_t n=1;
    while(n < max(a.size(),b.size()))
        n<<=1;
    n<<=1;
    fa.resize(n), fb.resize(n);
    FFT(fa,false), FFT(fb,false);
    for(size_t i=0; i<n; i++)
        fa[i]*=fb[i];
    FFT(fa,true);
    res.resize(n);
    for(size_t i=0; i<n; i++)
        res[i]=(long long)(round(fa[i].real()));
}

int a[100002],post[1<<16],pre[1<<16],ins[1<<16];
int main()
{
    ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tc;
    cin >> tc;
    while(tc--)
    {
        int n;
        cin >> n;
        for(int i=1; i<=n; i++)
        {
            cin >> a[i];
            post[a[i]]++;
        }
        int len=1025; // len = root(VlogV)
        int seg = n/len + (n%len!=0);
        ll ans = 0;
        for(int seg_i=0; seg_i<seg; seg_i++)
        {
            int st = seg_i*len+1;
            int ed = min(n,(seg_i+1)*len);

            for(int i=st; i<=ed; i++)
            {
                post[a[i]]--;
            }
            for(int j=st; j<=ed; j++)
            {
                for(int k=j+1; k<=ed; k++)
                {
                    int p = a[j]+a[k];
                    if(p>=0 && p<=65535)
                        ans+=post[p];//use i,j and k from post
                    p = a[k]-a[j];
                    if(p>=0 && p<=65535)
                        ans+=pre[p];//use j,k and i from pre
                    if(p>=0 && p<=65535)
                        ans+=ins[p];//use i,j,k from the segment
                }
                ins[a[j]]++;
            }
            vector<double>A,B;
            A.resize(65536);
            B.resize(65536);
            for(int i=1; i<=65535; i++)
            {
                A[65535-i]=pre[i];// here use (w-p) as here need (q-p) value instate of (p+q)
                B[i]=post[i];     // where w is the highest power
            }
            Mul(A,B);
            for(int i=st; i<=ed; i++)
            {
                ans+=res[65535+a[i]];// result collect from (w+q) instate of q
                pre[a[i]]++;
                ins[a[i]]--;
            }
        }
        cout << ans << endl;
        memset(pre,0,sizeof pre);
        memset(post,0,sizeof post);
        memset(ins,0,sizeof ins);
    }
    return 0;
}
