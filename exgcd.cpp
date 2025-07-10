ll exgcd (ll a,ll b,ll &x,ll &y)
{
    if (!b) {x = 1;y = 0;return abs (a);}
    ll d = exgcd (b,(a % b + b) % b,y,x);
    y -= a / b * x;
    return d;
}