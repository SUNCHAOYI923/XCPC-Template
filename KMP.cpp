class KMP
{
    vector <int> fail,ans;
    void getfail (char *s) // Match a with b
    {
        int len = strlen (s);
        fail.assign (len + 1,0);
        fail[0] = -1;
        for (int i = 1;i < len;++i)
        {
            int cnt = fail[i - 1];
            while (cnt >= 0 && s[cnt + 1] != s[i]) cnt = fail[cnt];
            if (s[cnt + 1] == s[i]) ++cnt;
            fail[i] = cnt;
        }
    }
    public:
    auto get_pos (char *s,char *t)
    {
        getfail (t);
        int lens = strlen (s),lent = strlen (t),cnt = -1;
        for (int i = 0;i < lens;++i)
        {
            while (cnt >= 0 && t[cnt + 1] != s[i]) cnt = fail[cnt];
            if (t[cnt + 1] == s[i])
            {
                ++cnt;
                if (cnt + 1 == lent) ans.push_back (i - lent + 2),cnt = fail[cnt];
            }
        }
        return ans;
    }
};