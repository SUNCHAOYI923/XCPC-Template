const double eps = 1e-8;
int dcmp (double x) {return x < -eps ? -1 : (x > eps ? 1 : 0);}
struct Point 
{
    double x,y;
    Point (double x = 0,double y = 0) : x (x),y (y) {}
    bool operator == (const Point& p) const {return dcmp (x - p.x) == 0 && dcmp (y - p.y) == 0;}
};
typedef Point Vector;
Vector operator + (Vector A,Vector B) {return Vector (A.x + B.x,A.y + B.y);}
Vector operator - (Vector A,Vector B) {return Vector (A.x - B.x,A.y - B.y);}
Vector operator * (Vector A,double k) {return Vector (A.x * k,A.y * k);} 
Vector operator / (Vector A,double k) {return Vector (A.x / k,A.y / k);} 

double dot (Vector A,Vector B) {return A.x * B.x + A.y * B.y;} 
double dis (Point A,Point B) {return sqrt ((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));} 
double cross (Vector A,Vector B) {return A.x * B.y - A.y * B.x;} // A -> B counter-clockwise if cross (A,B) > 0
double len (Point A)  {return sqrt (A.x * A.x + A.y * A.y);}
double angle (Vector A,Vector B) {return acos (dot (A,B) / (len (A) * len (B)));}
Vector proj (Vector A,Vector B) {return A * (dot (A,B) / dot (A,A));} //project onto A
Point foot (Point P,Point A,Point B) {Vector AP = P - A,AB = B - A;return A + proj (AB,AP);} //foot
Point reflect (Point P,Point A,Point B) {Point F = foot (P,A,B);return F * 2 - P;} //symmetry point
Point rotate (Point P,double theta) {return (Point){P.x * cos (theta) - P.y * sin (theta),P.x * sin (theta) + P.y * cos (theta)};}
bool on_line (Point P,Point A,Point B) {return dcmp (cross (P - A,B - A)) == 0;}
bool on_seg (Point P,Point A,Point B) {return on_line (P,A,B) && dcmp (dot (P - A,P - B)) <= 0;} //judge whether on segment AB
double dis_seg (Point P,Point A,Point B)
{
	if (dcmp (dot (B - A,P - A)) < 0) return dis (P,A);
	if (dcmp (dot (A - B,P - B)) < 0) return dis (P,B);
	return fabs (cross (P - A,P - B)) / dis (A,B);
}
Point inter (Point A,Point B,Point C,Point D) {return A + (B - A) * cross (C - A,D - C) / cross (B - A,D - C);}
bool pd_ll_inter (Point A,Point B,Point C,Point D) {return dcmp (cross (B - A,D - C)) != 0;} // line - line
bool pd_ls_inter (Point A,Point B,Point C,Point D) {return on_line (inter (A,B,C,D),C,D);} //The intersection of AB(line) and CD (line) is on the CD (seg).
bool pd_ss_inter (Point A,Point B,Point C,Point D) // seg - seg
{
	double c1 = cross (B - A,C - A),c2 = cross (B - A,D - A);
    double d1 = cross (D - C,A - C),d2 = cross (D - C,B - C);
    if (dcmp (c1) * dcmp (c2) < 0 && dcmp (d1) * dcmp (d2) < 0) return true;
    if (dcmp(c1) == 0 && on_seg (C,A,B)) return true;
    if (dcmp(c2) == 0 && on_seg (D,A,B)) return true;
    if (dcmp(d1) == 0 && on_seg (A,C,D)) return true;
    if (dcmp(d2) == 0 && on_seg (B,C,D)) return true;
    return false;
}

double area (vector <Point> P)
{
    int n = P.size ();
    double res = 0;
    for (int i = 0;i < n;++i) res += cross (P[i],P[(i + 1) % n]);
    return res / 2.0;
}
bool is_convex (vector <Point> P)
{
    int n = P.size ();
    for(int i = 0;i < n - 1;++i) 
        if (dcmp (cross (P[i + 1] - P[i],P[(i + 2) % n] - P[i])) < 0) return false;
    return true;
}
int in_Poly (vector <Point> P,Point A)
{
    int cnt = 0,n = P.size ();
    for (int i = 0;i < n;++i)
    {
        int j = (i + 1) % n;
        if (on_seg (A,P[i],P[j])) return 2;// on the edge
        if (A.y >= min (P[i].y,P[j].y) && A.y < max (P[i].y,P[j].y)) // the intersection is on the right
            cnt += dcmp (((A.y - P[i].y) * (P[j].x - P[i].x) / (P[j].y - P[i].y) + P[i].x) - A.x) > 0;
    }
    return cnt & 1;
}
vector <Point> convex_hull (vector <Point> P) // strict convex hull (<= 0)
{
    int n = P.size ();
    sort (P.begin (),P.end (),[] (Point &x,Point &y) {return x.x == y.x ? x.y < y.y : x.x < y.x;});
    vector <Point> hull;
    vector <int> vis (n + 1,0),id (n + 1,0);
    hull.resize (n + 1);
    int k = 0;
    for (int i = 0;i < n;++i) 
    {
        while (k >= 2 && dcmp (cross (hull[k - 1] - hull[k - 2],P[i] - hull[k - 2])) <= 0) vis[id[--k]] = 0;
        id[k] = i,hull[k++] = P[i];vis[i] = 1;
    }
    for (int i = n - 2,t = k;i >= 0;--i) 
    {
        if (vis[i]) continue;
        while (k > t && dcmp (cross (hull[k - 1] - hull[k - 2],P[i] - hull[k - 2])) <= 0) vis[id[--k]] = 0;
        id[k] = i,hull[k++] = P[i];vis[i] = 1;
    }
    hull.resize (k - (k > 2));
    return hull;
}
double diameter (vector <Point> P)
{
    int n = P.size ();
    if (n <= 1) return 0;
    if (n == 2) return len (P[1] - P[0]);
    double res = 0;
    for (int i = 0,j = 2;i < n;++i)
    {
        while (dcmp (cross (P[(i + 1) % n] - P[i],P[j] - P[i]) - cross (P[(i + 1) % n] - P[i],P[(j + 1) % n] - P[i])) <= 0) j = (j + 1) % n;
        res = max (res,max (len (P[j] - P[i]),len (P[j] - P[(i + 1) % n])));
    }
    return res;
}