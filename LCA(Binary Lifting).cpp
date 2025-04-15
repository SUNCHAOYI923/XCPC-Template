class LCA 
{
    static constexpr int lg = 20;
    int n;
    vector <int> dep;
    vector <vector <int>> f,ve;

    public:
    LCA (int n) : n (n),ve (n + 1),dep (n + 1),f (n + 1,vector <int> (lg + 1,0)) {}
    void add (int u,int v) {ve[u].push_back (v);ve[v].push_back (u);}
    void pre (int u,int fa)
    {
        f[u][0] = fa;dep[u] = dep[fa] + 1;
        for (int i = 0;i < lg;++i) f[u][i + 1] = f[f[u][i]][i];
        for (auto v : ve[u])
            if (v != fa) pre (v,u);
    }
    int query (int u,int v) 
    {
        if (dep[u] < dep[v]) swap (u,v);
        for (int i = lg;~i;--i)
        {
            if (dep[f[u][i]] >= dep[v]) u = f[u][i];
            if (u == v) return u;
        }
        for (int i = lg;~i;--i)
            if (f[u][i] != f[v][i]) u = f[u][i],v = f[v][i]; 
        return f[u][0];
    }
};