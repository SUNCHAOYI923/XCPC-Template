class Dinic
{
    typedef long long ll;
    static const int N=1e6+10,M=4e6+10;
    static const ll INF=4e18;
    int cgt,head[N],des[M],nxt[M],dep[N],que[N],H,T,h2[N];
    ll cap[M];
    inline ll dfs(const int &u,ll in=INF)
    {
        if(u==t)return in;ll out=0;
        for(int &i=h2[u];i;i=nxt[i])
        {
            int v=des[i];
            if(cap[i]&&dep[v]==dep[u]+1)
            {
                ll tmp=dfs(v,min(in,cap[i]));
                out+=tmp;cap[i]-=tmp;cap[i^1]+=tmp;
                if(!(in-=tmp))break;
            }
        }
        return out?out:dep[u]=0;
    }
    inline bool bfs()
    {
        memset(dep+1,0,n*sizeof(ll));
        dep[que[H=T=0]=s]=1;
        while(H<=T)
        {
            int u=que[H++];
            for(int i=head[u];i;i=nxt[i])if(cap[i])
            {
                int v=des[i];
                if(!dep[v])dep[que[++T]=v]=dep[u]+1;
            }
        }
        return dep[t];
    }
    public:
        int n,s,t;
        inline void Init(const int &sz=0)
        {
            memset(head+1,0,n*sizeof(ll));
            cgt=1;n=sz;
        }
        inline ll Max_Flow(const int &ss,const int &tt)
        {
            s=ss;t=tt;ll ans=0;
            while(bfs())
            {
                memcpy(h2+1,head+1,n*sizeof(ll));
                ans+=dfs(s,INF);
            }
            return ans;
        }
        inline bool ins(const int &x,const int &y,const ll &w)
        {
            if(x>n||y>n||x<1||y<1)return false;
            nxt[++cgt]=head[x];des[head[x]=cgt]=y;cap[cgt]=w;
            nxt[++cgt]=head[y];des[head[y]=cgt]=x;cap[cgt]=0;
            return true;
        }
        inline int newNode(){return ++n;}
}a;


namespace MCMF
{
    typedef long long Val_Type;typedef long long Cap_Type;
    const Val_Type INF_v=4e18;const Cap_Type INF_c=4e18; 
    const int N=1e6+10,M=2e6+10;int head[N],des[M],nxt[M],cgt=1;Cap_Type cap[M];Val_Type val[M];
    template<typename T> inline T Abs(T x){return x<0?-x:x;} 
    inline void ins(const int &x,const int &y,const int &c,const Val_Type &w)
    {
        nxt[++cgt]=head[x];des[head[x]=cgt]=y;cap[cgt]=c;val[cgt]=w;
        nxt[++cgt]=head[y];des[head[y]=cgt]=x;cap[cgt]=0;val[cgt]=-w;
    }
    int que[20000010],H,T;Val_Type dis[N],mnc;int s,t,S;bool inq[N];
    inline bool spfa()
    {
        for(int i=0;i<=S+2;++i)dis[i]=INF_v;dis[que[H=T=0]=s]=0;
        while(H<=T)
        {
            int u=que[H++];inq[u]=false;for(int i(head[u]);i;i=nxt[i])
                {int v=des[i];if(cap[i]&&dis[v]>dis[u]+val[i]){dis[v]=dis[u]+val[i];if(!inq[v])inq[que[++T]=v]=true;}}
        }
        return dis[t]<INF_v;
    }
    inline Cap_Type dfs(const int &u=s,Cap_Type in=INF_c)
    {
        if(u==t)return in;Cap_Type out=0;inq[u]=true;
        for(int i(head[u]);i;i=nxt[i])
        {
            int v=des[i];if(cap[i]&&!inq[v]&&dis[v]==(dis[u]+val[i]))
            {
                Cap_Type tmp=dfs(v,cap[i]<in?cap[i]:in);mnc+=val[i]*tmp;
                cap[i]-=tmp;cap[i^1]+=tmp;out+=tmp;if(!(in-=tmp))break;
            }
        }
        if(!out)dis[u]=4e18;inq[u]=false;return out;
    }
    inline Cap_Type dinic(){Cap_Type res=0;while(spfa())res+=dfs();return res;}
    inline void Clear(){memset(head,0,(S+2)*sizeof(head[0]));cgt=1;S=0;mnc=0;}
}
using MCMF::ins;using MCMF::s;using MCMF::t;using MCMF::S;using MCMF::dinic;using MCMF::mnc;