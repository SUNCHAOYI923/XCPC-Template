template <typename T,int MOD = 1000000007>
class COM
{
    int n;
    vector <Z <T,MOD>> fac,inv;
    public : 
    COM (int n) : n (n),fac (n + 1),inv (n + 1)
    {
        fac[0] = inv[0] = 1;
        for (int i = 1;i <= n;++i) fac[i] = fac[i - 1] * Z <T,MOD> (i);
        inv[n] = fac[n] ^ (MOD - 2);
        for (int i = n - 1;i;--i) inv[i] = inv[i + 1] * Z <T,MOD> (i + 1);
    }
    Z <T,MOD> f (int x) {return fac[x];}
    Z <T,MOD> inv_f (int x) {return inv[x];}
    Z <T,MOD> comb (int x,int y)
    {
        if (y < 0 || y > x) return Z <T,MOD> (0);
        else return fac[x] * inv[x - y] * inv[y];   
    }
    Z <T,MOD> arr (int x,int y)
    {
        if (y > x) return Z <T,MOD> (0);
        else return fac[x] * inv[x - y];   
    }
};