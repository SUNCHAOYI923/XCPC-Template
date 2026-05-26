template <int MOD = 998244353>
class NTT
{
    vector <int> rev; int n = 1;
    const int P = MOD;//998244353 469762049 50000000001507329LL 4179340454199820289
    const int G = 3;
    //1945555039024054273 for G = 5
    int qpow(int x, int y)
    {
        int res = 1;
        while (y)
        {
            if (y & 1) res = 1ll * res * x % P;
            x = 1ll * x * x % P;
            y >>= 1;
        }
        return res;
    }
    void init_rev(int tot)
    {
        int L = 0; n = 1;
        while (n < tot) n <<= 1, ++L;
        rev.resize(n);
        for (int i = 0; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
    }
    void ntt(vector <int> &a, int op)
    {
        for (int i = 0; i < n; ++i) 
            if (i < rev[i]) swap (a[i] ,a[rev[i]]);
        for (int len = 1; len < n; len <<= 1) 
        {
            int wn = qpow(G, (P - 1) / (len << 1));
            if (op == -1) wn = qpow (wn, P - 2); 
            for (int i = 0; i < n; i += len << 1) 
            {
                int w = 1;
                for(int j = 0; j < len; ++j) 
                {
                    int u = a[i + j] % P, v = 1ll * a[i + j + len] * w % P;
                    a[i + j] = (0ll + u + v) % P;
                    a[i + j + len] = (0ll + u - v + P) % P;
                    w = 1ll * w * wn % P;
                }
            }
        }
        if (op == -1)
        {
            int inv_n = qpow(n, P - 2);
            for (auto &x : a) x = 1ll * x * inv_n % P;
        }
    }
    public:
    vector <int> Conv(vector <int> a, vector <int> b)
    {
        int tot = (int)a.size() + (int)b.size() - 1;
        init_rev(tot);
        a.resize(n); b.resize(n);
        ntt(a, 1); ntt(b, 1);
        for (int i = 0; i < n; ++i) a[i] = 1ll * a[i] * b[i] % P;
        ntt(a, -1); a.resize(tot);
        return a;
    }
    vector <int> Inv(vector <int> a, int m)
    {
        int inv = qpow(a[0], P - 2);
        vector <int> b{inv};
        for (int len = 2; (len >> 1) < m; len <<= 1) 
        {
            int sz = min((int)a.size(), len);
            vector <int> f(a.begin(), a.begin() + sz);
            init_rev(len << 1);
            f.resize(n);
            vector <int> h = b; h.resize(n);
            ntt(f, 1); ntt (h, 1);
            for (int i = 0; i < n; ++i) 
                h[i] = 1ll * h[i] * (2ll - 1ll * f[i] * h[i] % P + P) % P;
            ntt(h, -1);
            b.assign (h.begin(), h.begin() + min(len, m));
        }
        b.resize (m);
        return b;
    }
    pair <vector <int>, vector <int>> Divmod(vector <int> a, vector <int> b)
    {
        int n_sz = a.size(), m_sz = b.size();
        if (n_sz < m_sz) return {{0},a};
        int dq = n_sz - m_sz + 1;
        vector <int> ra = a, rb = b;
        reverse(ra.begin(), ra.end()); reverse(rb.begin(), rb.end());
        ra.resize(dq); rb.resize(dq);
        vector <int> inv_rb = Inv(rb, dq);
        vector <int> q = Conv(ra, inv_rb);
        q.resize(dq);
        reverse(q.begin(), q.end());
        vector <int> qb = Conv(q, b);
        vector <int> r(m_sz - 1);
        for (int i = 0; i < m_sz - 1; ++i)
            r[i] = (0ll + a[i] - (i < (int)qb.size() ? qb[i] : 0) + P) % P;
        return {q,r};
    }
    vector <int> Sqrt(vector <int> a, int m) // b[0] = 1
    {
        vector <int> b{1};
        int inv2 = qpow(2, P - 2);
        for (int len = 2; (len >> 1) < m; len <<= 1) 
        {
            int sz = min((int)a.size(), len);
            vector <int> f(a.begin(), a.begin() + sz);
            vector <int> inv_b = Inv(b, len);
            init_rev(len << 1);
            f.resize(n); inv_b.resize(n);
            ntt(f, 1); ntt(inv_b, 1);
            for (int i = 0; i < n; ++i) 
                f[i] = 1ll * f[i] * inv_b[i] % P;
            ntt(f, -1);
            b.resize(len);
            for (int i = 0; i < len; ++i) 
                b[i] = 1ll * (b[i] + f[i]) % P * inv2 % P;
        }
        b.resize(m);
        return b;
    }
};