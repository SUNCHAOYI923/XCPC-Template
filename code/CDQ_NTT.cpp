F[0] = 1;
auto cdq = [&] (auto self, int l, int r) -> void
{
    if (l == r) return;
    int mid = (l + r) >> 1;
    self(self, l, mid);
    // It handles k in [l, mid] and i in [mid+1, r].
    vector <int> A(mid - l + 1), B(r - l + 1);
    for (int i = l; i <= mid; ++i) A[i - l] = F[i];
    for (int i = 0; i <= r - l; ++i) B[i] = G[i];
    // C[i-l] = sum(A[t] * B[i-l-t]) = sum(F[k] * G[i-k], k = l..mid)
    auto C = calc.Conv(A, B); 
    for (int i = mid + 1; i <= r; ++i) F[i] = (F[i] + C[i - l]) % MOD;
    self(self, mid + 1, r);
};
cdq(cdq, 0, n - 1);