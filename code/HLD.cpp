class HLD
{
    public:
        vector<vector<int> > G;
        int n, rt, cdt;
		HLD() : n(0), rt(1), cdt(0) {}
        vector<int> top,dep,fa,mxs,siz,dfn;
        void dfs1(int u, int f)
        {
            siz[u] = 1;
            fa[u] = f;
            dep[u] = dep[f] + 1;
            int mx = 0;
            for(int v: G[u]) if(v != f)
            {
                dfs1(v, u);
                siz[u] += siz[v];
                if(siz[v] > mx)
                {
                    mx = siz[v];
                    mxs[u] = v;
                }
            }
        }
        void dfs2(int u, int f, int tp)
        {
            if(mxs[u]) dfs2(mxs[u], u, tp);
            top[u] = tp;
            dfn[u] = ++cdt;
            // subtree : [dfn[u], dfn[u] + siz[u] - 1]
            // chain : [dfn[top[u]], dfn[u]]
            for(int v: G[u]) if(v != f && v != mxs[u])
            {
                dfs2(v, u, v);
            }
        }
        
        HLD(vector<vector<int> > &T, int RT = 1)
        {
            G = T;
            rt = RT;
            n = int(T.size()) - 1;
            top.assign(n+1, 0);
            dep.assign(n+1, 0);
            fa.assign(n+1, 0);
            mxs.assign(n+1, 0);
            siz.assign(n+1, 0);
            dfn.assign(n+1, 0);
            dfs1(rt, 0);
            cdt = 0;
            dfs2(rt, 0, rt);
        }
        int LCA(int u, int v)
        {
            while(top[u] != top[v])
            {
                dep[top[u]] > dep[top[v]] ? u = fa[top[u]] : v = fa[top[v]];
            }
            return dep[u] > dep[v] ? v : u;
        }
};