template <typename T>
class EK
{
    int n,m,s,t,cnt;
    vector <int> head,to,nxt,vis,pre,edge;
    vector <T> val;
    bool bfs ()
    {
        queue <T> q;
        for (int i = 1;i <= n;++i) vis[i] = 0,pre[i] = edge[i] = -1;
        vis[s] = 1;q.push (s);
        while (!q.empty ())
        {
            int u = q.front ();q.pop ();
            for (int i = head[u];i;i = nxt[i])
            {
                int v = to[i];
                if (!vis[v] && val[i])
                {	
                    pre[v] = u;edge[v] = i;vis[v] = 1;
                    q.push (v);
                    if (v == t) return 1; 
                }
            }
        }
        return 0;
    }
    
    public :
    EK (int n,int m,int s,int t) : 
        n (n),m (m),s (s),t (t),
        vis (n + 1,0),head (n + 1,0),pre (n + 1,-1),edge (n + 1,-1),
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
            T mn = INF;
            for (int i = t;i != s;i = pre[i]) mn = min (mn,val[edge[i]]);
            for (int i = t;i != s;i = pre[i]) val[edge[i]] -= mn,val[edge[i] ^ 1] += mn;
            ans += mn; 
        }
        return ans;
    }
};