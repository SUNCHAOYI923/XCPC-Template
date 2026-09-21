inline vector<int> add(vector<int> &f,vector<int> &g)
{
    int fn=int(f.size())-1,gn=int(g.size())-1;
    vector<int> Q(fn+gn+1,-INF);
    int sf=0,sg=0;
    while(sf<=fn&&f[sf]==-INF)++sf;
    while(sg<=gn&&g[sg]==-INF)++sg;
    if(sf>fn||sg>gn)return Q;
    rep(0,fn+gn,k)
    {
        int L=max(sf,k-gn),R=min(fn,k-sg);
        if(L<=R)Q[k]=max(f[L]+g[k-L],f[R]+g[k-R]);
    }
    return Q;
}