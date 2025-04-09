class SPFA
{
    int n,m,cnt;
    vector <int> head,to,nxt,val,vis,times;
    vector <ll> dis;

    public:
    SPFA (int n,int m) : 
        n (n),m (m),times (n + 1,0),vis (n + 1,0),head (n + 1,0),dis (n + 1,INF),
        to (2 * m + 1,0),nxt (2 * m + 1,0),val (2 * m + 1,0) {cnt = 0;}
    void add (int u,int v,int w)
    {
        to[++cnt] = v;val[cnt] = w;nxt[cnt] = head[u];head[u] = cnt;
        to[++cnt] = u;val[cnt] = v;nxt[cnt] = head[v];head[v] = cnt;
    }
    vector <ll> calc (int s) 
    {
        queue <int> q;
        for (int i = 1;i <= n;++i) vis[i] = 0,dis[i] = INF;
        dis[s] = 0,vis[s] = 1;q.push (s);
        while (!q.empty()) 
        {
            int u = q.front ();
            q.pop (),vis[u] = 0;
            for (int i = head[u];i;i = nxt[i])
            {
                int v = to[i];
                if (dis[v] > dis[u] + val[i]) 
                {
                    dis[v] = dis[u] + val[i];
                    times[v] = times[u] + 1;
                    if (times[v] >= n) return {-1};//Negative Cycle
                    if (!vis[v]) q.push (v),vis[v] = 1;
                }
            }
        }
        return vector <ll> (dis.begin () + 1,dis.end ());
    }
};