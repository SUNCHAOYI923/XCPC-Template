#include <bits/stdc++.h>
using namespace std;
constexpr int MAX = 1e5 + 5;
constexpr int MOD = 1e9 + 7;
constexpr int INF = 0x3f3f3f3f;
using i64 = long long;
using u64 = unsigned long long;
using pii = pair <int, int>;
inline int read()
{
    int s = 0; int f = 1;
    char ch = getchar();
    while ((ch < '0' || ch > '9') && ch != EOF)
    {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * f;
}
inline void write(int x)
{
    if (x < 0) {putchar ('-'); write(-x); return;}
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
int main()
{
    //freopen(".in", "r", stdin);
    //freopen(".out", "w", stdout);
    return 0;
}