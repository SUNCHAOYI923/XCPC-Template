template <typename T>
class Diameter
{
    int n,p;
    vector <T> dis;
    vector <vector <pair <int,T>>> ve;
    void dfs(int u,int fa) 
    {
        for (const auto& [v,w] : ve[u]) 
        {
            if (v == fa) continue;
            dis[v] = dis[u] + w;
            if (dis[v] > dis[p]) p = v;
            dfs(v,u);
        }
    }

    public:
    Diameter (int n) : n(n),ve(n + 1) {}
    void add (int u,int v,T w) {ve[u].push_back ({v,w});ve[v].push_back ({u,w});}
    T calc ()
    {
        dis.assign (n + 1,0);
        p = 1;dfs (1,0);
        dis[p] = 0;dfs (p,0);
        return dis[p];
    }
};