struct Trie 
{
    int n,m,cnt;//m total len
    vector <vector <int>> ch;
    vector <int> vis;
    public :
    Trie (int n,int m) : n (n),m (m),ch (m,vector <int> (26,0)),vis (m) {cnt = 0;}
    void insert (char *s)
    {
        int u = 0,len = strlen (s);
        for (int i = 0;i < len;++i) m
        {
            int c = s[i] - 'a';
            if (!ch[u][c]) ch[u][c] = ++cnt;
            u = ch[u][c];
        }
        ++vis[u];
    }
    int query (char *s) 
    {  
        int u = 0,len = strlen (s);
        for (int i = 0;i < len;++i) 
        {
            int c = s[i] - 'a';
            if (!ch[u][c]) return 0;
            u = ch[u][c];
        }
        return vis[u];
    }
};