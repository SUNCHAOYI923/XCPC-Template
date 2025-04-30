template <typename T>
class Basis
{
    int n,lg;
    vector <T> p;
    public :
    Basis (int n,int lg) : n (n),lg (lg),p (lg + 2,0) {}
    void modify (T x)
    {
        for (int i = lg - 1;~i;--i)
        {
            if (!((1ll << i) & x)) continue;
            if (!p[i]) {p[i] = x;break;}
            else x ^= p[i]; 
        }
    }
    T query ()
    {
        T ans = 0;
        for (int i = lg - 1;~i;--i)
            if ((ans ^ p[i]) > ans) ans ^= p[i];
        return ans;
    }
};