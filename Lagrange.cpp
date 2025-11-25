ll Lagrange (ll num)
{
    ll ans = 0;
    for (int i = 1;i <= n;++i)
    {
        ll p = y[i] % MOD,q = 1;
        for (int j = 1;j <= n;++j)
        {
            if (i == j) continue;
            p = p * (num - x[j]) % MOD;
            q = q * (x[i] - x[j]) % MOD;
        }
        ans = (ans + p * qpow (q,MOD - 2) % MOD + MOD) % MOD;
    }
    return ans;
}