template <unsigned long long base = 13331>
class Hash
{
    using u64 = unsigned long long;
    vector <u64> pw,hsh;
    public:
    Hash (char *s)
    {
        int n = strlen (s);
        pw.assign (n,0),hsh.assign (n,0);
        pw[0] = 1;hsh[0] = 0;
        for (int i = 1; i <= n;++i) pw[i] = pw[i - 1] * base,hsh[i] = hsh[i - 1] * base + s[i - 1];
    }
    u64 get (int l,int r) {return hsh[r] - hsh[l - 1] * pw[r - l + 1];}
    u64 link (int l1,int r1,int l2,int r2) {return get (l1,r1) * pw[r2 - l2 + 1] + get (l2,r2);}
    bool same (int l1,int r1,int l2,int r2) {return get (l1,r1) == get (l2,r2);}
};