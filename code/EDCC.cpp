class EDCC
{
    public:
    struct Edge {int to, nxt;};
    vector <Edge> G;
    vector <int> head, dfn, low, scc;
    vector <bool> cut;
    vector <vector <int>> T;
    stack <int> stk;
    int n, cnt, tot;
    // EDCC g(n); g.insert(u, v); g.init();
    // Vertices, components and inserted edges are 1-based.
    EDCC(int nn = 0)
    {
        n = nn; cnt = tot = 0;
        G.assign(2, {0, 0});
        head.assign(n + 1, 0);
    }
    void insert(int u, int v)
    {
        G.push_back({v, head[u]}); head[u] = G.size() - 1;
        G.push_back({u, head[v]}); head[v] = G.size() - 1;
    }
    void dfs(int u, int f = -1)
    {
        dfn[u] = low[u] = ++cnt;
        stk.push(u);
        for (int i = head[u]; i; i = G[i].nxt)
        if (i != f) // Skip only the reverse parent edge.
        {
            int v = G[i].to;
            if (!dfn[v])
            {
                dfs(v, i ^ 1);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u]) cut[i >> 1] = true;
            }
            else if (dfn[v] < low[u]) low[u] = dfn[v];
        }
        if (low[u] == dfn[u])
        {
            int v; ++tot;
            do
            {
                v = stk.top(); stk.pop();
                scc[v] = tot;
            }
            while (v != u);
        }
    }
    // O(n + m). T is a forest if the graph is disconnected.
    // scc[u]: component of u; cut[i]: is inserted edge i a bridge?
    void init()
    {
        cnt = tot = 0;
        dfn.assign(n + 1, 0);
        low.assign(n + 1, 0);
        scc.assign(n + 1, 0);
        cut.assign(G.size() >> 1, false);
        while (!stk.empty()) stk.pop();
        for (int i = 1; i <= n; ++i) if (!dfn[i]) dfs(i);
        T.assign(tot + 1, {});
        for (int i = 2; i < (int)G.size(); i += 2)
        if (cut[i >> 1])
        {
            int u = scc[G[i ^ 1].to], v = scc[G[i].to];
            T[u].push_back(v); T[v].push_back(u);
        }
    }
};
