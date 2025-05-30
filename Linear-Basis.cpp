template <typename T>
class Basis
{
    int n,lg;
    vector <T> p,ex,nw;
    public :
    Basis (int n,int lg) : n (n),lg (lg),p (lg + 1,0),nw (lg + 1,0) {}
    void modify (T x)
    {
        for (int i = lg;~i;--i)
        {
            if (!((1ll << i) & x)) continue;
            if (!p[i]) {p[i] = x;break;}
            else x ^= p[i]; 
        }
    }
    T get_max ()
    {
        T ans = 0;
        for (int i = lg;~i;--i)
            if ((ans ^ p[i]) > ans) ans ^= p[i];
        return ans;
    }
    T get_min ()
    {
        T ans = 0;int cnt = 0;
        for (int i = 0;i <= lg;++i) cnt += p[i] > 0;
        if (cnt < n) return 0;
        for (int i = 0;i <= lg;++i)
            if (p[i] > 0) return p[i];
    }
    void change ()
    {
        for (int i = 0;i <= lg;++i) nw[i] = p[i];
        for (int i = 0;i <= lg;++i)
            for (int j = i - 1;~j;--j)
                if (nw[i] >> j & 1) nw[i] ^= nw[j];
        for (int i = 0;i <= lg;++i)
            if (nw[i]) ex.push_back (i);
    }
    T get_min_k (T k)
    {
        int sz = (int)ex.size ();
        if (sz < n) --k; // element 0
        if (k > (1ll << sz) - 1) return -1;
        T ans = 0;
        for (int j = 0;j < sz;++j)
            if (k >> j & 1) ans ^= nw[ex[j]];
        return ans;
    }
};