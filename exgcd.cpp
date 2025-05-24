//ax + by = gcd (a,b) 
//x = x0 + b / gcd (a,b) * k
//y = y0 - a / gcd (a,b) * k
ll exgcd (ll a,ll b,ll &x,ll &y) // |x| min
{
    if (!b) {x = 1;y = 0;return a;}
    ll d = exgcd (b,a % b,x,y),tmp = x;
    x = y;y = tmp - (a / b) * y;
    return d;//gcd
}