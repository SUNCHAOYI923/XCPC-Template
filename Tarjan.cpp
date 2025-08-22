class Tarjan
{
    int n,m,cnt,times,scc_cnt;
    vector <int> head,to,nxt,low,scc,dfn;
    stack <int> s;
    void tarjan (int u)
    {
        low[u] = dfn[u] = ++times;
        s.push (u);
        for (int i = head[u];i;i = nxt[i])
        {
            int v = to[i];
            if (!dfn[v])
            {
                tarjan (v,i);
                low[u] = min (low[u],low[v]);
            }
            else if (i != (la ^ 1) && !scc[v]) low[u] = min (low[u],dfn[v]);
        }
        if (low[u] == dfn[u])
        {
            ++scc_cnt;
            while (1)
            {
                int x = s.top ();s.pop ();
                scc[x] = scc_cnt;
                if (x == u) break;
            }
        } 
    }
    public:
    Tarjan (int n,int m) : 
        n (n),m (m),head (n + 2,0),low (n + 1,0),dfn (n + 1,0),scc (n + 1,0),
        to (2 * m + 2,0),nxt (2 * m + 2,0) {cnt = 1;times = scc_cnt = 0;}
    void add (int u,int v) // Note that the bidirectional edges
    {
        to[++cnt] = v;nxt[cnt] = head[u];head[u] = cnt;
        to[++cnt] = u;nxt[cnt] = head[v];head[v] = cnt;
    }
    auto calc ()
    {
        for (int i = 1;i <= n;++i)
            if (!dfn[i]) tarjan (i,-1);
        return scc;
    }
};