#include <bits/stdc++.h>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define pii pair <int,int>
using namespace std;
const int MAX = 1e5 + 5;
const int MOD = 1e9 + 7;
char s[200];
inline int read ();
inline void output ();
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
    {
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
    {
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
inline void output (int x)
{
    if (x < 0) putchar ('-');
    x = (x > 0) ? x : -x;
    int cnt = 0;
    while (x)
    {
        s[cnt++] = x % 10 + '0';
        x /= 10;
    }
    while (cnt) putchar (s[--cnt]);
}