vector<int> add(vector<int> &f,vector<int> &g)
{
    int fn=int(f.size())-1,gn=int(g.size())-1;
    vector<int> Q(fn+gn+1,-INF);
    int sf=0,tf=fn,sg=0,tg=gn;
    while(sf<=fn&&f[sf]==-INF)++sf;
    while(tf>=sf&&f[tf]==-INF)--tf;
    while(sg<=gn&&g[sg]==-INF)++sg;
    while(tg>=sg&&g[tg]==-INF)--tg;
    if(sf>tf||sg>tg)return Q;
    rep(0,fn+gn,k)
    {
        int L=max(sf,k-tg),R=min(tf,k-sg);
        if(L<=R)Q[k]=max(f[L]+g[k-L],f[R]+g[k-R]);
    }
    return Q;
}