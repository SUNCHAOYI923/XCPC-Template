struct Trie 
{
    int n,m,cnt; // m 总长度
    vector <vector <int>> ch;
    vector <int> vis;
    public :
    Trie (int n,int m) : n (n),m (m),ch (m,vector <int> (26,0)),vis (n) {cnt = 0;}
    void insert (char *s)
    {
        int u = 1,len = strlen (s + 1);
        for (int i = 1;i <= len;++i) 
        {
            int c = s[i] - 'a';
            if (!ch[u][c]) ch[u][c] = ++cnt;  // 如果没有，就添加结点
            u = ch[u][c];
        }
        ++vis[u];
    }
    int query (char *s) 
    {  
        int u = 1,len = strlen (s + 1);
        for (int i = 1;i <= len;++i) 
        {
            int c = s[i] - 'a';
            if (!ch[u][c]) return 0;
            u = ch[u][c];
        }
        return vis[u];
    }
};