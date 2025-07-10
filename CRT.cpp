ll CRT ()
{
    //ans % a[i] = b[i] if gcd (a[i],a[j]) = 1
    ll sum = 1,ans = 0;
    for (int i = 1;i <= n;++i) sum *= a[i];
    for (int i = 1;i <= n;++i)
    {
        ll x,y,tmp = sum / a[i];
        exgcd (tmp,a[i],x,y);
        ans = (ans + tmp * x * b[i]) % sum;
    }
    return (ans + sum) % sum;
}