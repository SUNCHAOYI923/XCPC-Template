#include<bits/stdc++.h>
using namespace std;

template<int N>
class Bitset{
    static_assert(N>0,"N must be positive");
    static constexpr int M=(N+63)>>6;
    static constexpr uint64_t LM=(N&63)?((1ULL<<(N&63))-1):0xffffffffffffffffULL;
    uint64_t a[M];
    static inline uint64_t rev(uint64_t x){
        x=((x&0x5555555555555555ULL)<<1)|((x>>1)&0x5555555555555555ULL);
        x=((x&0x3333333333333333ULL)<<2)|((x>>2)&0x3333333333333333ULL);
        x=((x&0x0f0f0f0f0f0f0f0fULL)<<4)|((x>>4)&0x0f0f0f0f0f0f0f0fULL);
        x=((x&0x00ff00ff00ff00ffULL)<<8)|((x>>8)&0x00ff00ff00ff00ffULL);
        x=((x&0x0000ffff0000ffffULL)<<16)|((x>>16)&0x0000ffff0000ffffULL);
        return (x<<32)|(x>>32);
    }
    inline void fix(){a[M-1]&=LM;}
public:
    class Ref{
        uint64_t &x,m;
    public:
        Ref(uint64_t &x,uint64_t m):x(x),m(m){}
        Ref&operator=(bool v){if(v)x|=m;else x&=~m;return *this;}
        Ref&operator=(const Ref&v){return *this=bool(v);}
        operator bool()const{return x&m;}
        Ref&flip(){x^=m;return *this;}
    };
    Bitset(){reset();}
    Bitset(unsigned long long x){reset();a[0]=x;fix();}
    Ref operator[](int p){return Ref(a[p>>6],1ULL<<(p&63));}
    bool operator[](int p)const{return (a[p>>6]>>(p&63))&1;}
    bool test(int p)const{return (*this)[p];}
    Bitset&set(){memset(a,0xff,sizeof(a));fix();return *this;}
    Bitset&reset(){memset(a,0,sizeof(a));return *this;}
    Bitset&flip(){for(int i=0;i<M;i++)a[i]=~a[i];fix();return *this;}
    bool any()const{for(int i=0;i<M;i++)if(a[i])return 1;return 0;}
    bool all()const{for(int i=0;i+1<M;i++)if(a[i]!=0xffffffffffffffffULL)return 0;return a[M-1]==LM;}
    int count()const{int s=0;for(int i=0;i<M;i++)s+=__builtin_popcountll(a[i]);return s;}
    constexpr int size()const{return N;}
    int find_first()const{for(int i=0;i<M;i++)if(a[i])return (i<<6)+__builtin_ctzll(a[i]);return N;}
    int find_next(int p)const{
        if(++p>=N)return N;
        int i=p>>6;
        uint64_t x=a[i]&(~0ULL<<(p&63));
        if(x)return (i<<6)+__builtin_ctzll(x);
        for(++i;i<M;i++)if(a[i])return (i<<6)+__builtin_ctzll(a[i]);
        return N;
    }
    Bitset&operator&=(const Bitset&b){for(int i=0;i<M;i++)a[i]&=b.a[i];return *this;}
    Bitset&operator|=(const Bitset&b){for(int i=0;i<M;i++)a[i]|=b.a[i];return *this;}
    Bitset&operator^=(const Bitset&b){for(int i=0;i<M;i++)a[i]^=b.a[i];return *this;}
    Bitset&operator<<=(int k){
        if(k>=N)return reset();
        int q=k>>6,r=k&63;
        if(q){
            for(int i=M-1;i>=q;i--)a[i]=a[i-q];
            for(int i=0;i<q;i++)a[i]=0;
        }
        if(r){
            for(int i=M-1;i;i--)a[i]=(a[i]<<r)|(a[i-1]>>(64-r));
            a[0]<<=r;
        }
        fix();return *this;
    }
    Bitset&operator>>=(int k){
        if(k>=N)return reset();
        int q=k>>6,r=k&63;
        if(q){
            for(int i=0;i+q<M;i++)a[i]=a[i+q];
            for(int i=M-q;i<M;i++)a[i]=0;
        }
        if(r){
            for(int i=0;i+1<M;i++)a[i]=(a[i]>>r)|(a[i+1]<<(64-r));
            a[M-1]>>=r;
        }
        return *this;
    }
    Bitset&reverse(){
        for(int i=0,j=M-1;i<=j;i++,j--){uint64_t x=rev(a[i]);a[i]=rev(a[j]);a[j]=x;}
        if(N&63){int r=N&63,s=64-r;for(int i=0;i+1<M;i++)a[i]=(a[i]>>s)|(a[i+1]<<r);a[M-1]>>=s;}
        fix();return *this;
    }
    friend Bitset operator&(Bitset x,const Bitset&y){return x&=y;}
    friend Bitset operator|(Bitset x,const Bitset&y){return x|=y;}
    friend Bitset operator^(Bitset x,const Bitset&y){return x^=y;}
    friend Bitset operator<<(Bitset x,int k){return x<<=k;}
    friend Bitset operator>>(Bitset x,int k){return x>>=k;}
    friend Bitset operator~(Bitset x){return x.flip();}
    friend bool operator==(const Bitset&x,const Bitset&y){
        for(int i=0;i<M;i++)if(x.a[i]!=y.a[i])return 0;
        return 1;
    }
    friend bool operator!=(const Bitset&x,const Bitset&y){return !(x==y);}
    string to_string()const{
        string s(N,'0');
        for(int i=0;i<N;i++)if((*this)[i])s[N-1-i]='1';
        return s;
	}
    friend ostream&operator<<(ostream&out,const Bitset&b){return out<<b.to_string();}
};
//forbid : use a[i] as int, must bool(a[i]) or if(a[i]) but no if(a[i]+a[j]) 