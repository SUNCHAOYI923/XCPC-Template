vector <int> lg (n + 1,-1);
vector <vector <int>> f (20,vector <int> (n + 1,INF));
for (int i = 1;i <= n;++i) lg[i] = lg[i >> 1] + 1;
for (int i = 1;i <= n;++i) f[0][i] = a[i];
for (int j = 1;j < 20;++j)
    for (int i = 1;i + (1 << j) - 1 <= n;++i) f[j][i] = min (f[j - 1][i],f[j - 1][i + (1 << (j - 1))]);
auto query = [&] (int l,int r) -> int {return min (f[lg[r - l + 1]][l],f[lg[r - l + 1]][r - (1 << lg[r - l + 1]) + 1]);};