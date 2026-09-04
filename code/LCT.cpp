const int N = 1e5 + 10;
struct Splay {
    int s[2] = {0, 0};
    int fa = 0;
    int sum = 0;
    int vl = 0;
    bool tg = false;
} t[N];
int n;
// Check whether x is not the root of its auxiliary tree.
// isSon(x) == false : is Root
inline bool isSon(const int &x) {return t[t[x].fa].s[0] == x || t[t[x].fa].s[1] == x;}
inline void rev(const int &x) {if (!x) return;swap(t[x].s[0], t[x].s[1]);t[x].tg ^= 1;}
inline void update(const int &x) {t[x].sum = t[t[x].s[0]].sum ^ t[t[x].s[1]].sum ^ t[x].vl;}
inline void pushdown(const int &x) {if (!t[x].tg) return;t[x].tg = false;rev(t[x].s[0]);rev(t[x].s[1]);}

// Rotate x in its auxiliary tree.
inline void rotate(const int &x) {
    int y = t[x].fa;
    int z = t[y].fa;
    bool k = (t[y].s[1] == x);
    if (isSon(y)) t[z].s[t[z].s[1] == y] = x;
    int w = t[x].s[k ^ 1];
    t[x].s[k ^ 1] = y;
    t[y].s[k] = w;
    if (w) t[w].fa = y;
    t[x].fa = z;
    t[y].fa = x;
    update(y);
    update(x);
}
int sk[N], tp;
// Splay x and push all lazy tags on the path to x.
inline void splay(const int x) {
    tp = 1;
    sk[tp] = x;
    while (isSon(sk[tp])) {
        ++tp;
        sk[tp] = t[sk[tp - 1]].fa;
    }
    while (tp) pushdown(sk[tp--]);
    while (isSon(x)) {
        int y = t[x].fa;
        if (isSon(y)) {
            bool zigZig = (t[y].s[0] == x) == (t[t[y].fa].s[0] == y);
            rotate(zigZig ? y : x);
        }
        rotate(x);
    }
    update(x);
}

// Expose the preferred path from x to the origin-tree root.
inline void access(int x) {
    for (int y = 0; x; x = t[y = x].fa) {
        splay(x);
        t[x].s[1] = y;
        update(x);
    }
}

// Make x the root of its original tree.
inline void makeRt(const int &x) {
    access(x);
    splay(x);
    rev(x);
}

// Find the represented-tree root containing x.
inline int fndRt(int x) {
    access(x);
    splay(x);
    while (t[x].s[0]) {
        pushdown(x);
        x = t[x].s[0];
    }
    splay(x);
    return x;
}

// Expose the path from x to y in y's auxiliary tree. (Exactly x->y, Rooted at y)
inline void split(const int &x, const int &y) {
    makeRt(x);
    access(y);
    splay(y);
}

// Link the trees containing x and y.
inline void lnk(const int &x, const int &y) {
    makeRt(x);
    if (fndRt(y) != x) t[x].fa = y;
}

// Cut the edge x-y if it exists.
inline void cut(const int &x, const int &y) {
    makeRt(x);
    if (fndRt(y) == x && t[y].fa == x && !t[y].s[0]) {
        t[y].fa = t[x].s[1] = 0;
        update(x);
    }
}

// Modify the value stored at x.
inline void modify(const int &x, const int &value) {
    access(x);
    splay(x);
    t[x].vl = value;
    update(x);
}