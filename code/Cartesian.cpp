//heap-order(root is min) on values and BST-order on keys
stack <int> s;
vector <int> L(n + 1, 0), R(n + 1, 0);
vector <int> ql(n + 1, 0), qr(n + 1, 0);
for (int i = 1; i <= n; ++i)
{
    int la = -1;
    while (!s.empty() && a[s.top()] > a[i]) la = s.top(), s.pop();
    if (!s.empty()) R[s.top()] = i;
    if (la != -1) L[i] = la;
    s.push(i);
}
int Rt = 0;
while (!s.empty()) Rt = s.top(), s.pop();
auto dfs = [&](auto self, int u, int l, int r)->void
{
    ql[u] = l; qr[u] = r;
    if(L[u])self(self, L[u], l, u - 1);
    if(R[u])self(self, R[u], u + 1, r);
};
dfs(dfs, Rt, 1, n);