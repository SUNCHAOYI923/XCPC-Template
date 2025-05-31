template <typename T>
class Dinic
{
    int n,m,s,t,cnt;
    vector <int> head,to,nxt,cur,dep;
    vector <T> val;
    int bfs () 
    {
        for (int i = 0;i <= n;++i) dep[i] = 0,cur[i] = head[i];
        queue <int> q;
        q.push (s),dep[s] = 1;
        while (!q.empty ()) 
        {
            int u = q.front ();q.pop ();
            for (int i = head[u];i;i = nxt[i]) 
            {
                int v = to[i];
                if (val[i] && !dep[v]) q.push (v),dep[v] = dep[u] + 1;
            }
        }
        return dep[t];
    }
    T dfs (int u,int t,T flow)
    {
        if (u == t) return flow;
        T ans = 0;
        for (int &i = cur[u];i && ans < flow;i = nxt[i]) 
        {
            int v = to[i];
            if (val[i] && dep[v] == dep[u] + 1) 
            {
                int x = dfs (v,t,min (val[i], flow - ans));
                if (x) val[i] -= x,val[i ^ 1] += x,ans += x;
            }
        }
        if (ans < flow) dep[u] = -1;
        return ans;
    }
    public :
    Dinic (int n,int m,int s,int t) :
        n (n),m (m),s (s),t (t),
        head (n + 1,0),cur (n + 1,0),dep (n + 1,0),
        to (m + 1,0),nxt (m + 1,0),val (m + 1,0) {cnt = 1;}
    void add (int u,int v,T w)
    {
        to[++cnt] = v;val[cnt] = w;nxt[cnt] = head[u];head[u] = cnt;
        to[++cnt] = u;val[cnt] = 0;nxt[cnt] = head[v];head[v] = cnt;
    }
    T calc () 
    {
        T ans = 0;
        while (bfs ()) 
        {
            T x;
            while ((x = dfs (s,t,INF))) ans += x;
        }
        return ans;
    }
};