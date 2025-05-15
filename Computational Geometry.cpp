class Vector
{
    double x,y;
    public : 
    using Point = Vector;
    Vector (double x = 0,double y = 0) : x (x),y (y) {}
    double getX () const {return x;}
    double getY () const {return y;}
    Vector operator + (const Vector &A) const {return Vector (x + A.x,y + A.y);}
    Vector operator - (const Vector &A) const {return Vector (x - A.x,y - A.y);}
    Vector operator * (double k) const {return Vector (x * k,y * k);}
    Vector operator / (double k) const {return Vector (x / k,y / k);}
    Vector proj (const Vector &A) const {return A * (this -> dot (A) / A.dot (A));}//project onto A
    double dot (const Vector &A) const {return x * A.x + y * A.y;} 
    double cross (const Vector &A) const {return x * A.y - y * A.x;} 
    double len () const {return sqrt (x * x + y * y);}
    double calc (const Vector &A) {return sqrt ((A.x - x) * (A.x - x) + (A.y - y) * (A.y - y));} 
    double angle (const Vector &A) const {return acos (this -> dot (A) / (this -> len () * A.len ()));}
    Point foot (const Point &A,const Point &B) const //垂足
    {
        Vector AP = *this - A,AB = B - A;
        return A + AP.proj (AB);
    }
    Point reflect (const Point &A,const Point &B) const //对称点
    {
        Point F = this -> foot (A, B);
        return F * 2 - *this;
    }
};