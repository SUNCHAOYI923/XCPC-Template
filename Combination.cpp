template <typename T>
class COM
{
	int n;static const int MOD = 1e9 + 7;
	vector <Z <T>> fac,inv;
	public : 
	COM (int n) : n (n),fac (n + 1),inv (n + 1)
	{
		fac[0] = inv[0] = 1;
        for (int i = 1;i <= n;++i) fac[i] = fac[i - 1] * Z <T> (i);
        inv[n] = fac[n] ^ MOD - 2;
        for (int i = n - 1;i;--i) inv[i] = inv[i + 1] * Z <T> (i + 1);
	}
    Z <T> f (int x) {return fac[x];}
    Z <T> inv_f (int x) {return inv[x];}
    Z <T> comb (int x,int y)
    {
        if (y < 0 || y > x) return Z <T> (0);
        else return fac[x] * inv[x - y] * inv[y];   
    }
    Z <T> arr (int x,int y)
    {
        if (y > x) return Z <T> (0);
        else return fac[x] * inv[x - y];   
    }
};