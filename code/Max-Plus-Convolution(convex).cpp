inline vector<ll> mul(const vector<ll> &f,const vector<ll> &g)
{
    int fn=int(f.size())-1,gn=int(g.size())-1;
    int qn=fn+gn;
    vector<ll> Q(qn+1,-INF);
    int sf=0,tf=fn,sg=0,tg=gn;
    while(sf<=fn&&f[sf]==-INF)++sf;
    while(tf>=sf&&f[tf]==-INF)--tf;
    while(sg<=gn&&g[sg]==-INF)++sg;
    while(tg>=sg&&g[tg]==-INF)--tg;
    if(sf>tf||sg>tg)return Q;
    int i=sf,j=sg;
    if(i+j>qn)return Q;
    Q[i+j]=f[i]+g[j];
    while(i+j<qn&&(i<tf||j<tg))
    {
        if(j==tg||(i<tf&&f[i+1]-f[i]>=g[j+1]-g[j]))++i;
        else ++j;
        Q[i+j]=f[i]+g[j];
    }
    return Q;
}