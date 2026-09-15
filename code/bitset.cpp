class Bitset{
    int n,m;
    vector<uint64_t>a;

    static inline uint64_t rev(uint64_t x){
        x=((x&0x5555555555555555ULL)<<1)|((x>>1)&0x5555555555555555ULL);
        x=((x&0x3333333333333333ULL)<<2)|((x>>2)&0x3333333333333333ULL);
        x=((x&0x0f0f0f0f0f0f0f0fULL)<<4)|((x>>4)&0x0f0f0f0f0f0f0f0fULL);
        x=((x&0x00ff00ff00ff00ffULL)<<8)|((x>>8)&0x00ff00ff00ff00ffULL);
        x=((x&0x0000ffff0000ffffULL)<<16)|((x>>16)&0x0000ffff0000ffffULL);
        return (x<<32)|(x>>32);
    }

    inline void fix(){if(n&63)a.back()&=((1ULL<<(n&63))-1);}
    //set i>=n to zero

public:
    class Ref{
        uint64_t&x,m;
    public:
        Ref(uint64_t&x,uint64_t m):x(x),m(m){}
        Ref&operator=(bool v){if(v)x|=m;else x&=~m;return *this;}
        Ref&operator=(const Ref&v){return *this=bool(v);}
        operator bool()const{return x&m;}
        Ref&flip(){x^=m;return *this;}
    };

    Bitset(int n=0):n(n),m((n+63)>>6),a(m){}

    Ref operator[](int p){return Ref(a[p>>6],1ULL<<(p&63));}
    bool operator[](int p)const{return (a[p>>6]>>(p&63))&1;}
    bool test(int p)const{return (*this)[p];}

    Bitset&set(){
        fill(a.begin(),a.end(),~0ULL);
        fix();return *this;
    }
    Bitset&set(int p,bool v=1){(*this)[p]=v;return *this;}
    Bitset&reset(){fill(a.begin(),a.end(),0);return *this;}
    Bitset&reset(int p){(*this)[p]=0;return *this;}

    Bitset&flip(){
        for(auto&x:a)x=~x;
        fix();return *this;
    }
    Bitset&flip(int p){a[p>>6]^=1ULL<<(p&63);return *this;}

    bool any()const{
        for(auto x:a)if(x)return 1;
        return 0;
    }
    bool none()const{return !any();}

    int count()const{
        int s=0;
        for(auto x:a)s+=__builtin_popcountll(x);
        return s;
    }

    int size()const{return n;}

    Bitset&operator&=(const Bitset&b){
        for(int i=0;i<m;i++)a[i]&=b.a[i];
        return *this;
    }
    Bitset&operator|=(const Bitset&b){
        for(int i=0;i<m;i++)a[i]|=b.a[i];
        return *this;
    }
    Bitset&operator^=(const Bitset&b){
        for(int i=0;i<m;i++)a[i]^=b.a[i];
        return *this;
    }

    Bitset&operator<<=(int k){
        if(k>=n)return reset();
        int q=k>>6,r=k&63;
        if(q){
            for(int i=m-1;i>=q;i--)a[i]=a[i-q];
            for(int i=0;i<q;i++)a[i]=0;
        }
        if(r){
            for(int i=m-1;i;i--)a[i]=(a[i]<<r)|(a[i-1]>>(64-r));
            a[0]<<=r;
        }
        fix();return *this;
    }

    Bitset&operator>>=(int k){
        if(k>=n)return reset();
        int q=k>>6,r=k&63;
        if(q){
            for(int i=0;i+q<m;i++)a[i]=a[i+q];
            for(int i=m-q;i<m;i++)a[i]=0;
        }
        if(r){
            for(int i=0;i+1<m;i++)a[i]=(a[i]>>r)|(a[i+1]<<(64-r));
            a[m-1]>>=r;
        }
        return *this;
    }

    Bitset&reverse(){
        for(int i=0,j=m-1;i<=j;i++,j--){
            uint64_t x=rev(a[i]);
            a[i]=rev(a[j]);
            a[j]=x;
        }
        if(n&63){
            int r=n&63,s=64-r;
            for(int i=0;i+1<m;i++)a[i]=(a[i]>>s)|(a[i+1]<<r);
            a[m-1]>>=s;
        }
        fix();return *this;
    }
    Bitset&operator+=(const Bitset&b){
	    uint64_t c=0;
	    for(int i=0;i<m;i++){
	        uint64_t x=a[i],y=b.a[i];
	        a[i]=x+y+c;
	        c=(a[i]<x)||(c&&a[i]==x);
	    }
	    fix();
	    return *this;
	}
	
	Bitset&operator-=(const Bitset&b){
	    uint64_t c=0;
	    for(int i=0;i<m;i++){
	        uint64_t x=a[i],y=b.a[i];
	        a[i]=x-y-c;
	        c=(x<y)||(c&&x==y);
	    }
	    fix();
	    return *this;
	}
    friend Bitset operator&(Bitset x,const Bitset&y){return x&=y;}
    friend Bitset operator|(Bitset x,const Bitset&y){return x|=y;}
    friend Bitset operator^(Bitset x,const Bitset&y){return x^=y;}
    friend Bitset operator<<(Bitset x,int k){return x<<=k;}
    friend Bitset operator>>(Bitset x,int k){return x>>=k;}
    friend Bitset operator~(Bitset x){return x.flip();}
};
/*
_Find_first() : the first 1
_Find_next(p) : the position of the first 1 after p (not included p)
*/