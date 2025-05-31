vector <vector <double>> a (n + 1,vector <double> (n + 2)); // n * (n + 1)
for (int i = 1;i <= n;++i)
{
    int p = cur,ok = 0;
    while (p <= n)
    {
        if (a[p][i] != 0) {ok = 1;break;}
        ++p;
    }
    if (!ok) continue;
    for (int j = i;j <= n + 1;++j) swap (a[p][j],a[cur][j]);
    for (int j = n + 1;j >= i;--j) a[cur][j] /= a[cur][i];
    for (int j = 1;j <= n;++j)
    {
        if (j == cur) continue;
        for (int k = n + 1;k >= i;--k) a[j][k] -= a[cur][k] * a[j][i];
    }
    ++cur; 
}
if (cur <= n) puts ("No Solution"); //0 solution or infinte solutions
else {for (int i = 1;i <= n;++i) printf ("%.6lf\n",a[i][n + 1]);}    