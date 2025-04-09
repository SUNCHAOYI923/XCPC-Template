class Matching
{
    int l,r;//the number of left/right side points
    vector <vector <int>> ve;
    vector <int> vis,op;
    bool dfs (int u)
    {
        for (auto v : ve[u])
        {
            if (vis[v]) continue;
            vis[v] = 1;
            if (!op[v] || dfs (op[v])) {op[v] = u;return true;}
        }
        return false;
    }
    
    public:
    Matching (int l,int r) : l (l),r (r),vis (r + 1,0),op (r + 1,0),ve (l + 1) {}
    void add (int u,int v) {ve[u].push_back (v);}
    int calc ()
    {
        int ans = 0;
        for (int i = 1;i <= l;++i)
        {
            vis.assign (r + 1,0);
            if (dfs (i)) ++ans;
        }
        return ans;
    }
};