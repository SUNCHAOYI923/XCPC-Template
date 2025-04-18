#include <bits/stdc++.h>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define pii pair <int,int>
using namespace std;
const int MAX = 2e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
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
        //w[u] 节点 u 到其父亲节点这条边上数值的数量（权值）
        //val[u] 以 u 为根的子树维护的异或和
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
    void add (int u) // 全局 +1
    {
        swap (ch[u][0],ch[u][1]);
        if (ch[u][0]) add (ch[u][0]);
        pushup (u);
    }
};