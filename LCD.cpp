//Total Length of Chains is O(n)
//Each merge will eliminate 1 node of the shorter chains
const int N = 1e6 + 10;
long long F[N];//f[rt][i]: the sum of nodes at distance exactly i from rt
//e.g. the sum of the nodes with distance =i
int mxs[N], dep[N], mxd[N];
long long a[N];
vector<int> G[N];
int n, rt;
void dfs(int u = 1, int fa = 0)
{
    dep[u] = dep[fa] + 1;
    int mx = -1;
    mxd[u] = dep[u];
    for(int v: G[u]) if(v != fa)
    {
        dfs(v, u);
        mxd[u] = max(mxd[u], mxd[v]);
        if(mxd[v] > mx)
        {
            mx = mxd[v];
            mxs[u] = v;
        }
    }
}
void DP(int u = 1, int fa = 0, long long *f = F)
{
    f[0] += a[u];
    long long *tmp = f + (mxd[u] - dep[u]) + 1;
    for(int v : G[u]) if(v != fa)
    {
        if(v != mxs[u])
        {
            long long *fv = tmp;
            DP(v, u, fv);
            for(int i = 0; i <= mxd[v] - dep[v]; ++i)
            {
                f[i + 1] += fv[i];
                fv[i] = 0;
            }
        }
        else
        {
            DP(v, u, f + 1);
        }
    }
}