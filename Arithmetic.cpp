template <typename T,int MOD = 1000000007>
class Z
{
    T x;
    Z <T,MOD> qpow (Z x,T y)
    {
        Z <T,MOD> res (1);
        while (y)
        {
            if (y & 1) res *= x;
            x *= x;
            y >>= 1;
        }
        return res;
    }
    public :
    Z () : x(0) {}
    Z (T x) : x (x) {}
    Z & operator = (T o) {x = o;return *this;}
    Z & operator += (Z o) {x = (x + o.x + MOD) % MOD;return *this;}
    Z & operator -= (Z o) {x = (x - o.x + MOD) % MOD;return *this;}
    Z & operator *= (Z o) {x = 1ll * o.x * x % MOD;return *this;}
    Z & operator ^= (Z o) {x = qpow (x,o.x).x;return *this;}
    Z & operator /= (Z o) {*this *= o ^ (MOD - 2);return *this;}
    friend Z operator + (Z x,Z y) {return x += y;}
    friend Z operator - (Z x,Z y) {return x -= y;}
    friend Z operator * (Z x,Z y) {return x *= y;}
    friend Z operator / (Z x,Z y) {return x /= y;}
    friend Z operator ^ (Z x,Z y) {return x ^= y;}
    friend bool operator == (Z x,Z y) {return x.x == y.x;}
    friend bool operator != (Z x,Z y) {return x.x != y.x;}
    friend istream& operator >> (istream& is, Z& o) {T val;is >> val;o = Z(val);return is;}
    friend ostream& operator << (ostream &os, const Z &z) {return os << z.x;}
};