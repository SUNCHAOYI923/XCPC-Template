class NTT
{
    vector <int> rev;int n = 1;
    const int P = 1004535809;//998244353 469762049
    const int G = 3;
    int qpow (int x,int y)
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
    void ntt (vector <int> &a,int op)
    {
        for (int i = 0;i < n;++i) 
            if (i < rev[i]) swap (a[i],a[rev[i]]);
        for (int len = 1;len < n;len <<= 1) 
        {
            int wn = qpow (3,(P - 1) / (len << 1));
            if (op == -1) wn = qpow (wn,P - 2); 
            for (int i = 0;i < n;i += len << 1) 
            {
                int w = 1;
                for(int j = 0;j < len;++j) 
                {
                    int u = a[i + j],v = 1ll * a[i + j + len] * w % P;
                    a[i + j] = (0ll + u + v) % P;
                    a[i + j + len] = (0ll + u - v + P) % P;
                    w = 1ll * w * wn % P;
                }
            }
        }
        if (op == -1)
        {
            int inv_n = qpow (n,P - 2);
            for (auto &x : a) x = 1ll * x * inv_n % P;
        }
    }
    public :
    vector <int> conv (vector <int> a,vector <int> b)
    {
        int L = 0,tot = (int)a.size () + (int)b.size () - 1;n = 1;
        while (n < tot) n <<= 1,++L;
        rev.resize (n);a.resize (n);b.resize (n);
        for (int i = 0;i < n;++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
        ntt (a,1);ntt (b,1);
        for (int i = 0;i < n;++i) a[i] = 1ll * a[i] * b[i] % P;
        ntt (a,-1);a.resize (tot);
        return a;
    }
};