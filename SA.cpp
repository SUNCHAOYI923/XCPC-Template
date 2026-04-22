struct SA
{
    string s;
    vector <int> sa,rk,ht;
    // all 0-base including sa
    // suffix order 
    // rank of suffix i
    // LCP(sf[i], sf[i+1])
    vector <int> tmp;
    int n;
    SA (string &t) {init (t);}
    inline void tSort (int m)
    {
        vector<int> tmp1 (m + 1, 0);
        for (int i = 0;i < n;++i) ++tmp1[rk[tmp[i]]];
        for (int i = 1;i <= m;++i) tmp1[i] += tmp1[i - 1];
        for (int i = n - 1;i >= 0;--i) sa[--tmp1[rk[tmp[i]]]] = tmp[i];
    }
    inline void init (string &t)
    {
        s = t;n = s.size ();
        sa.assign (n,0);rk.assign (n,0);ht.assign (n,0);tmp.assign (n,0);
        for (int i = 0;i < n;++i) rk[i] = s[i],tmp[i] = i;
        int m = 127;tSort (m);
        for (int k = 1,p = 0;p < n;k <<= 1)
        {
            p = 0;
            for (int i = n - k;i < n;++i) tmp[p++] = i;
            for (int i = 0;i < n;++i) 
                if (sa[i] >= k) tmp[p++] = sa[i] - k;
            tSort (m);
            vector <int> old_rk = rk;
            rk[sa[0]] = p = 1;
            for (int i = 1;i < n;++i)
            {
                int a = sa[i],b = sa[i - 1];
                if (old_rk[a] == old_rk[b] && (a + k < n ? old_rk[a + k] : 0) == (b + k < n ? old_rk[b + k] : 0))
                    rk[a] = p;
                else
                    rk[a] = ++p;
            }
            m = p;
            if (p == n) break;
        }
        for (int i = 0;i < n;++i) --rk[i];
        int h = 0;
        for (int i = 0;i < n;++i)
        {
            if (rk[i] == 0) continue;
            int j = sa[rk[i] - 1];
            while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;
            ht[rk[i] - 1] = h;
            if (h > 0) --h;
        }
    }
    inline void clear ()
    {
        s.clear ();sa.clear ();rk.clear ();ht.clear ();tmp.clear ();
        n = 0;
    }
    inline int size () const {return n;}
    inline int operator[] (int p) const {return sa[p];}
};