int Manacher (char *s)
{
    int n = strlen (s),cnt = 0,r = 0,mid = 0,ans = 0;
    vector <char> a (2 * n + 5);vector <int> p (2 * n + 5);
    a[++cnt] = '!';a[++cnt] = '#';
    for (int i = 0;i < n;++i) a[++cnt] = s[i],a[++cnt] = '#';
    a[++cnt] = '~';
    for (int i = 2;i < cnt;++i)
    {
        if (i <= r) p[i] = min (r - i + 1,p[mid * 2 - i]);
        else p[i] = 1;
        while (a[i - p[i]] == a[i + p[i]]) ++p[i];
        if (i + p[i] > r) r = i + p[i] - 1,mid = i;
        ans = max (ans,p[i]); 
    }
    return ans - 1;
}