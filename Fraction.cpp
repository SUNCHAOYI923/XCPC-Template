template <typename T>
class Frac
{
    T p,q; // p / q
    void reduce ()
    {
        assert (q != 0);
        T g = gcd (p,q);
        p /= g,q /= g;
        if (q < 0) p = -p,q = -q;
    }
    public :
    Frac (T p = 0, T q = 1) : p (p),q (q) {assert (q != 0);reduce ();}
    T get_p () {return p;}
    T get_q () {return q;}
    double get_val () {return 1.0 * p / q;}
    Frac operator + (const Frac &o) {return Frac (p * o.q + o.p * q,q * o.q);}
    Frac operator - (const Frac &o) {return Frac (p * o.q - o.p * q,q * o.q);}
    Frac operator * (const Frac &o) {return Frac (p * o.p,q * o.q);}
    Frac operator / (const Frac &o) {return Frac (p * o.q,q * o.p);}
    Frac& operator += (const Frac &o) {*this = *this + o;return *this;}
    Frac& operator -= (const Frac &o) {*this = *this - o;return *this;}
    Frac& operator *= (const Frac &o) {*this = *this * o;return *this;}
    Frac& operator /= (const Frac &o) {*this = *this / o;return *this;}
    Frac operator -() {return Frac (-p,q);}
    bool operator >= (const Frac &o) {return p * o.q >= o.p * q;}
    bool operator > (const Frac &o) {return p * o.q > o.p * q;}
    bool operator == (const Frac &o) {return p * o.q == o.p * q;}
    bool operator <= (const Frac &o) {return !(*this > o);}
    bool operator < (const Frac &o) {return !(*this >= o);}
    bool operator != (const Frac &o) {return !(*this == o);}
};