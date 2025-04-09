class Topo
{
    int n;
    vector <int> deg;
    vector <vector <int>> ve;

    public:
    Topo (int n) : n (n),ve (n + 1),deg (n + 1,0) {}
    void add (int u,int v)
    {
        ve[u].push_back (v);
        ++deg[v];
    }
    vector <int> calc ()
    {
        queue <int> q;
        vector <int> lst;
        for (int i = 1;i <= n;++i) 
            if (!deg[i]) q.push (i);
        while (!q.empty ())
        {
            int u = q.front ();q.pop ();
            lst.push_back (u);
            for (auto v : ve[u])
            {
                --deg[v];
                if (!deg[v]) q.push (v);
            }
        }
        return lst;
    }
};