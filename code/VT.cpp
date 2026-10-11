typedef long long ll;
typedef pair <int, ll> pil;

class VT
{
    int n = 0, lg = 0;
    vector <int> dfn, out;
    vector <ll> dis;
    vector <vector <int>> f;
    bool anc(int u, int v) const
    {
        return dfn[u] <= dfn[v] && dfn[v] <= out[u];
    }
    int lca(int u, int v) const
    {
        if (anc(u, v)) return u;
        if (anc(v, u)) return v;
        for (int j = lg - 1; j >= 0; --j)
            if (!anc(f[j][u], v)) u = f[j][u];
        return f[0][u];
    }
    public:
    // G[1..n]: undirected weighted tree; G[0] unused.
    // Root at 1. O(n log n) time / space, no recursion.
    void init(const vector <vector <pil>> &G)
    {
        n = max(0, (int)G.size() - 1);
        lg = 1;
        while ((1LL << lg) <= n) ++lg;
        dfn.assign(n + 1, 0); out.assign(n + 1, 0);
        dis.assign(n + 1, 0);
        f.assign(lg, vector <int> (n + 1, 1));
        if (!n) return;
        int timer = 0;
        vector <int> st = {1};
        while (!st.empty())
        {
            int u = st.back(); st.pop_back();
            if (u < 0) {out[-u] = timer; continue;}
            dfn[u] = ++timer;
            for (int j = 1; j < lg; ++j)
                f[j][u] = f[j - 1][f[j - 1][u]];
            st.push_back(-u);
            for (auto [v, w] : G[u])
                if (v != f[0][u])
                {
                    f[0][v] = u; dis[v] = dis[u] + w;
                    st.push_back(v);
                }
        }
    }
    // Replaces v with unique keys + LCAs in DFS order.
    // ans[i] <-> original vertex v[i], i is 0-based.
    // Undirected edges; ans.size() == v.size().
    // Empty keys -> empty tree; otherwise root is 0.
    // Root distances and compressed edge sums must fit in ll.
    // k input keys: O(k log k + k log n) time, O(k) space.
    vector <vector <pil>> getVT(vector <int> &v)
    {
        if (v.empty()) return {};
        auto cmp = [&](int a, int b) {return dfn[a] < dfn[b];};
        sort(v.begin(), v.end(), cmp);
        v.erase(unique(v.begin(), v.end()), v.end());
        int k = (int)v.size();
        for (int i = 1; i < k; ++i)
            v.push_back(lca(v[i - 1], v[i]));
        sort(v.begin(), v.end(), cmp);
        v.erase(unique(v.begin(), v.end()), v.end());
        int m = (int)v.size();
        vector <vector <pil>> ans(m);
        vector <int> st = {0};
        for (int i = 1; i < m; ++i)
        {
            while (!anc(v[st.back()], v[i]))
                st.pop_back();
            int p = st.back();
            ll w = dis[v[i]] - dis[v[p]];
            ans[p].push_back({i, w});
            ans[i].push_back({p, w});
            st.push_back(i);
        }
        return ans;
    }
};
