class AC
{
    int n,m,cnt;//m total len
    vector <vector <int>> tr;vector <int> val;
    public :
    Trie (int n,int m) : n (n),m (m),tr (m + 1,vector <int> (26,0)),val (m + 1),fail (m + 1) {cnt = 1;}
    void insert (char *s)
    {
        int n = strlen (s + 1),u = 1;
        for (int i = 1;i <= N;++i)
        {
            if (!tr[u][s[i] - 'a']) tr[u][s[i] - 'a'] = ++cnt;
            u = tr[u][s[i] - 'a'];
        }
        ++val[u];
    }
    void build ()
    {
        for (int i = 0;i < 26;++i) tr[0][i] = 1;
        queue <int> q;q.push (1);
        while (!q.empty ())
        {
            int u = q.front ();q.pop ();
            for (int i = 0;i < 26;++i)
            {
                if (!tr[u][i]) tr[u][i] = tr[fail[u]][i];
                else fail[tr[u][i]] = tr[fail[u]][i],q.push (tr[u][i]);
            }
        }
    }
    int query (char *s)
    {
        int n = strlen (s + 1),u = 1,res = 0;
        for (int i = 1;i <= n;++i)
        {
            u = tr[u][s[i] - 'a'];
            for (int j = u;j && val[j] != -1;j = fail[j]) res += val[j],val[j] = -1;
        }
        return res;
    }
};
/*  s :
a
aa
aa
aaa
t :
aaaa 
ans : 4  */