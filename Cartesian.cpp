//heap-order on values and BST-order on keys
for (int i = 1;i <= n;++i)
{
    int p = top;
    while (p && a[s[p]] > a[i]) --p;
    if (p) R[s[p]] = i;
    if (p < top) L[i] = s[p + 1];
    s[++p] = i;top = p;
}