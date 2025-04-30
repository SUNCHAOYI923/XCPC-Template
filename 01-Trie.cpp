class Trie
{
    int n,cnt;
    vector <vector <int>> ch;
    vector <int> val,w;
    public :
    Trie (int n,int lg) : n (n),val (2 * lg * n + 1,0),w (2 * lg * n + 1,0),ch (2 * lg * n + 1,vector <int> (2,0)) {cnt = 1;}
    void pushup (int u)
    {
        w[u] = val[u] = 0;
        //w[u] Number of values (weights) on the edge between node u and its parent node
        //val[u] XOR sum maintained by the subtree rooted at u
        if (ch[u][0]) w[u] ^= w[ch[u][0]],val[u] ^= val[ch[u][0]] << 1;
        if (ch[u][1]) w[u] ^= w[ch[u][1]],val[u] ^= (val[ch[u][1]] << 1) | w[ch[u][1]];
    }
    void modify (int &u,int v,int dep)
    {
        if (!u) u = ++cnt;
        w[u] ^= 1;
        if (dep < 0) return ;
        modify (ch[u][v & 1],v >> 1,dep - 1);
        pushup (u);
    }
    void erase (int u,int v,int dep)
    {
        if (!u) return ;
        w[u] ^= 1;
        if (dep < 0) return ;
        erase (ch[u][v & 1],v >> 1,dep - 1);
        pushup (u);
    }
    void add (int u) // add 1 in [1,n]
    {
        swap (ch[u][0],ch[u][1]);
        if (ch[u][0]) add (ch[u][0]);
        pushup (u);
    }
};