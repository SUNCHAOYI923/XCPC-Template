class DCC
{
    public:
    struct Edge {int to,nxt;};
    vector <Edge> G;
    vector <int> head,dfn,low,col;
    vector <bool> cut;
    stack <int> stk;
    int cnt,cct,n;
    void init (int nn = 0)
    {
        G.assign (2,{0,0});
        n = nn;head.assign (n + 1,0);
    }
    void dfs (int u,int f = -1)
    {
         dfn[u] = low[u] = ++cnt;
        int ch = 0;
        for (int i = head[u];i;i = G[i].nxt) 
        if (i != f)
        {
            int v = G[i].to;
            if (dfn[v] < dfn[u]) stk.push (i >> 1);
            if (!dfn[v])
            {
                dfs (v,i ^ 1);++ch;
                low[u] = min (low[u],low[v]);
                if (low[v] >= dfn[u])
                {
                    int I = 0;
                    ++cct;cut[u] = true;
                    do
                    {
                        assert (!stk.empty ());
                        I = stk.top ();stk.pop ();
                        col[I] = cct;
                    }
                    while (I != (i >> 1));
                }
            }
            else if (dfn[v] < low[u]) low[u] = dfn[v];
        }
        if (f == -1 && ch == 1) cut[u] = false;
    }
    void tarjan ()
    {
        cnt = cct = 0;
        col.assign (G.size () >> 1,0);
        dfn.assign (n + 1,0);
        low.assign (n + 1,0);
        cut.assign (n + 1,false);
        while (!stk.empty ()) stk.pop ();
        for (int i = 1;i <= n;++i) if (!dfn[i]) dfs (i);
    }
    void insert (int u,int v)
    {
        G.push_back ({v,head[u]});head[u] = G.size () - 1;
        G.push_back( {u,head[v]});head[v] = G.size () - 1;
    }
    void insert (vector <vector <int>> &G1)
    {
        for (unsigned u = 1;u < G1.size ();++u)
            for (int v : G1[u]) insert (u,v);
    }
    bool operator [] (const int &x) const {return cut[x];}
};