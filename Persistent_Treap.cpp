namespace PFHQ//Interval Copy
{
    #include<bits/stdc++.h>
    #define rep(a,b,c) for(register int c=(a);c<=(b);++c)
    using namespace std;
    const int Mod=1e9+7,INF=0x3f3f3f3f,N=4e6+5;
    inline int read()
    {
        int res=0;char ch=getchar();while(ch<'0'||ch>'9')ch=getchar();
        while(ch<='9'&&ch>='0')res=res*10+(ch^48),ch=getchar();return res;
    }
    inline int add(int &x,int y){x=((x+y>=Mod)?(x+y-Mod):(x+y));}
    struct FHQ{int l,r,siz,val,sum,tag[3];}t[N];
    int a[N],cnt,Root,top,n,m,T1,T2,T3,T4,T5;
    inline int Node(int val)
    {
        t[++cnt].siz=1;t[cnt].sum=t[cnt].val=val;t[cnt].tag[0]=INF;
        t[cnt].l=t[cnt].r=t[cnt].tag[1]=t[cnt].tag[2]=0;return cnt;
    }
    inline int copy(int x){t[++cnt]=t[x];return cnt;}
    inline void update(int x)
    {
        t[x].siz=t[t[x].l].siz+t[t[x].r].siz+1;
        t[x].sum=((t[t[x].l].sum+t[t[x].r].sum)%Mod+t[x].val)%Mod;
    }
    inline void push2(int x){swap(t[x].l,t[x].r);t[x].tag[2]^=1;}
    inline void push1(int x,int k){add(t[x].val,k);add(t[x].tag[1],k);t[x].sum=
    (t[x].sum+1ll*t[x].siz*k%Mod)%Mod;}
    inline void push0(int x,int k)
    {t[x].tag[1]=0;t[x].tag[0]=t[x].val=k;t[x].sum=1ll*t[x].siz*k%Mod;}
    inline void pushdown(int cur)
    {
        if(t[cur].tag[0]!=INF||t[cur].tag[1]||t[cur].tag[2])
        {
            if(t[cur].l) t[cur].l = copy(t[cur].l);
            if(t[cur].r) t[cur].r = copy(t[cur].r);
        }
        if(t[cur].tag[0]!=INF)
        {
            if(t[cur].l) push0(t[cur].l,t[cur].tag[0]);
            if(t[cur].r) push0(t[cur].r,t[cur].tag[0]);
            t[cur].tag[0] = INF;
        }
        if(t[cur].tag[1])
        {
            if(t[cur].l) push1(t[cur].l,t[cur].tag[1]);
            if(t[cur].r) push1(t[cur].r,t[cur].tag[1]);
            t[cur].tag[1] = 0;
        }
        if(t[cur].tag[2]){if(t[cur].l)push2(t[cur].l);if(t[cur].r)push2(t[cur].r);t[cur].tag[2]=0;}
    }
    inline int merge(int x,int y)
    {
        if(!x||!y)return x+y;pushdown(x);pushdown(y);
        if(rand()%(t[x].siz+t[y].siz)<t[x].siz){x=copy(x);t[x].r=merge(t[x].r,y);update(x);return x;}
        y=copy(y);t[y].l=merge(x,t[y].l);update(y);return y;
    }
    inline void split(int cur,int k,int &x,int &y)
    {
        if(!cur){x=y=0;return;} pushdown(cur);
        if(t[t[cur].l].siz>=k)y=copy(cur),split(t[y].l,k,x,t[y].l),update(y);
        else x=copy(cur),split(t[x].r,k-t[t[cur].l].siz-1,t[x].r,y),update(x);
    }
    inline void build(int l,int r,int &cur)
    {
        int mid=(l+r)>>1;cur=Node(a[mid]);
        if(l<mid)build(l,mid-1,t[cur].l);
        if(r>mid)build(mid+1,r,t[cur].r);update(cur);
    }
    inline void change(int l,int r,int k)
    {
        split(Root,l-1,T1,T2);split(T2,r-l+1,T2,T3);
        T2=copy(T2);push0(T2,k);Root=merge(merge(T1,T2),T3);
    }
    inline void modify(int l,int r,int k)
    {
        split(Root,l-1,T1,T2);split(T2,r-l+1,T2,T3);
        T2=copy(T2);push1(T2,k);Root=merge(merge(T1,T2),T3);
    }
    inline void Copy(int l1,int r1,int l2,int r2)//swap
    {
        if(l1>l2)swap(l1,l2),swap(r1,r2);
        split(Root,l1-1,T1,T2);split(T2,r1-l1+1,T2,T3);
        split(T3,l2-r1-1,T3,T4);split(T4,r2-l2+1,T4,T5);
        Root=merge(merge(merge(merge(T1,T4),T3),T2),T5);
    }
    inline void paste(int l1,int r1,int l2,int r2)//copy
    {
        bool flag = 0;if(l1>l2)swap(l1,l2),swap(r1,r2),flag=1;
        split(Root,l1-1,T1,T2);split(T2,r1-l1+1,T2,T3);
        split(T3,l2-r1-1,T3,T4);split(T4,r2-l2+1,T4,T5);
        if(flag) T2=copy(T4);else T4=copy(T2);
        Root=merge(merge(merge(merge(T1,T2),T3),T4),T5);
    }
    inline int query(int l,int r)
    {
        split(Root,l-1,T1,T2);split(T2,r-l+1,T2,T3);
        int res=t[T2].sum;Root=merge(merge(T1,T2),T3);return res;
    }
    inline void dfs(int cur)
    {
        pushdown(cur);if(t[cur].l)dfs(t[cur].l);
        a[++top]=t[cur].val;if(t[cur].r)dfs(t[cur].r);
    }
    inline void reverse(int l,int r)
    {
        split(Root,l-1,T1,T2);split(T2,r-l+1,T2,T3);
        T2=copy(T2);push2(T2);Root=merge(merge(T1,T2),T3);
    }
    int main()
    {
        srand(time(0));
        n=read();m=read();rep(1,n,i)a[i]=read();build(1,n,Root);rep(1,m,i)
        {
            int opt=read(),l1=read(),r1=read(),l2,r2;
            switch(opt)
            {
                case 1: printf("%d\n",query(l1,r1));break;
                case 2: change(l1,r1,read());break;
                case 3: modify(l1,r1,read());break;
                case 4: l2=read();r2=read();paste(l1,r1,l2,r2);break;
                case 5: l2=read();r2=read();Copy(l1,r1,l2,r2);break;//swap
                case 6: reverse(l1,r1);break;
            }
            if(cnt>N-1000000)dfs(Root),top=Root=cnt=0,build(1,n,Root);    }
        top=0;dfs(Root);rep(1,n,i)printf("%d ",a[i]);return 0;
    }
}