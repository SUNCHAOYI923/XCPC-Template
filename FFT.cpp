using cd = complex <double>;
class FFT
{
    const double Pi = acos (-1);
    vector <int> rev;int n = 1;
    void fft (vector <cd> &a,int op)
    {
        for (int i = 0;i < n;++i) 
            if (i < rev[i]) swap (a[i],a[rev[i]]);
        for (int len = 1;len < n;len <<= 1) 
        {
            cd wn (cos (Pi / len),op * sin (Pi / len));
            for (int i = 0;i < n;i += len << 1) 
            {
                cd w (1);
                for(int j = 0;j < len;++j) 
                {
                    cd u = a[i + j],v = a[i + j + len] * w;
                    a[i + j] = u + v;a[i + j + len] = u - v;
                    w *= wn;
                }
            }
        }
        if (op == -1) {for (auto &x : a) x /= n;}
    }
    public :
    vector <double> conv (vector <cd> a,vector <cd> b)
    {
        int L = 0,tot = (int)a.size () + (int)b.size () - 1;n = 1;
        while (n < tot) n <<= 1,++L;
        rev.resize (n);a.resize (n);b.resize (n);
        for (int i = 0;i < n;++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
        fft (a,1);fft (b,1);
        for (int i = 0;i < n;++i) a[i] = a[i] * b[i];
        fft (a,-1);
        vector <double> ans (tot);
        for (int i = 0;i < tot;++i) ans[i] = a[i].real ();
        return ans;
    }
};