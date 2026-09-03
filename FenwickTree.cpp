inline void add(int *t,int p,int v){while(p<=n)t[p]+=v,p+=(p&-p);}
inline int qry(int *t,int p){int res=0;while(p)res+=t[p],p^=(p&-p);return res;}
inline int qry(int *t,int k)//return n+1 if all satisfy
{
    int p=0,tot=0;
    for(int i=20;~i;--i)if((p|1<<i)<=n&&tot+t[p|(1<<i)]<k)tot+=t[p|=(1<<i)];
    return p+1;
}