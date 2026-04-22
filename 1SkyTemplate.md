# 个人码风规定

**不用奇怪的define！**

**少用神秘的位运算！**

**拒绝各种邪教码风！**

## 基础模板

```cpp
#include <bits/stdc++.h>
#define INF 0x7fffffff
#define MAXN 200010
#define LL long long
using namespace std;

int main() {
	
    return 0;
}
```

## 常用变量名

大小写敏感

```cpp
T // 样例数
a b c // 单变量
x y z // for循环索引（不良习惯）
i j k // 比较少用到
u v w // 节点和权重
n m // 节点个数/数组大小一类
l r // 左右边界
s // 字符串
q // 队列
st // 栈
ch // 字符
s[MAXN] // 数组
vis[MAXN] // 图论 是否到达过
e[MAXN] // 图论 边
t[MAXN] // 树（偶尔用）
d[MAXN] // 距离，或表示权重
dp[MAXN] // 动态规划
vector <int> g[MAXN] // 图论（邻接表）

tf // bool判断
ans // 答案
inp // 纯输入用
cnt // 计数
dis // 距离
tmp // 临时存储
MOD // 取模大数
maxn minn // 最大最小值

struct node{} // 节点
```

## 缩进/空格/函数名

**所有函数/if/for等语句大括号不换行** 
**能加空格尽量加，除非忍不住**
**驼峰命名法** 尽量不用下划线

```cpp
// 驼峰命名法
int isNumber(int a) { // 大括号不换行
    for(int x = 1; x <= n; x++) {
        if(a == 114514) {
            cout << "AAAAAAAAAAAAAH" << endl;
            return 1919810;
        }
        else a += b; // 省略大括号
    }

    for(int x = 1; x <= m; x++)
        if(a >= INF) cout << "N/A" << endl;
    // 有时候会这样写两层省略大括号
	// 已纠正这种不良习惯
}
```

*关于索引：其实我一般数组、图论都是从 $1$ 到 $n$，但是有时候会出现字符串等特殊情况就用 $0 $到 $n-1$

# 常用模板

## 基础算法

### 快读/快写

实际几乎没用过，打比赛基本不卡常，大数据IO用`scanf`/`printf`够了

```cpp
int read() {
    int a = 0, f = 1; char ch;
    ch = getchar();
    while(ch > '9' || ch < '0'){if(ch == '-') f = -f;ch = getchar();}
    while(ch <= '9' && ch >= '0'){a = a * 10 + ch - 48;ch = getchar();}
    return a * f;
}

void write(int a) {
	if(a < 0) {putchar('-'); a = -a;}
	if(a > 9) {write(a/10); putchar(a % 10 + '0');}
	else putchar(a + '0');
	return; 
}
```

像我这种喜欢用`cin`/`cout`的，建议补上这个关闭流同步：
```cpp
cin.tie(nullptr);
ios::sync_with_stdio(false);
```

### 二分答案

最基础最重要的算法之一
实际使用主要需要设计二分条件，即half函数

这里给一个例子：
在一个排好序的数组 $s$ 里面寻找整数 $a$ 的位置，时间复杂度 $O(log(n))$

```cpp
int s[MAXN];

bool halfCheck(int mid, int a) {
    return s[mid] >= a;
}

int binarySearch(int l, int r, int a) {
    int re;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(halfCheck(mid, a)) {
            r = mid - 1;
            re = mid;
        }
        else l = mid + 1;
    }
    return re;
}
```

### 快速排序

不会真的有人不用STL的`sort`，还自己写快排吧（

```cpp
int s[MAXN];

void fastSort(int l, int r) {
	if(l >= r) return;
	int i = l, j = r;
	while(i < j) {
		while(s[j] >= s[l] && i < j) j--;
		while(s[i] <= s[l] && i < j) i++;
		swap(s[i], s[j]);
	}
	swap(s[l], s[i]);
	fastSort(l, i - 1);
	fastSort(i + 1, r);
}
```

## 数学

### 快速幂

可以在 $O(\log n)$ 的时间复杂度里求出 $a^n \bmod m$

```cpp
LL fastPow(LL a, LL n, LL m = MOD) {
	LL ans = 1;
	while(n) {
		if(n & 1) ans *= a, ans %= m;
		a *= a, a %= m, n >>= 1;
	}
	return ans % m;
}
```

### GCD 欧几里得算法

求a和b的最大公约数

```cpp
int gcd(int a, int b) {
	if(!b) return a;
	else return gcd(b, a % b);
}
```
（其实STL有函数`__gcd(a, b)`）

### EXGCD 扩展欧几里得算法

在求得 $a$ 和 $b$ 的最大公约数的同时，能找到整数 $x$ 和 $y$，满足贝祖等式
$$
ax + by = \gcd(a, b)
$$

```cpp
void exgcd(int a, int b, int &x, int &y) {
	if(!b) x = 1, y = 0;
    else exgcd(b, a % b, y, x), y -= a / b * x;
}
```

对于不定方程
$$
ax+by = p
$$
1. 如果 $p$ 不是 $\gcd(a,b)$ 的倍数，此不定方程没有整数解
2. 如果 $p$ 是其倍数，则有无穷多解：
$$
x = x_0 + k\left(\frac{b}{\gcd(a,b)}\right) \\\ 
y = y_0 - k\left(\frac{a}{\gcd(a,b)}\right)
$$

### 逆元

单个逆元的式子（根据费马小定理推导），快速幂直接算
$$
a^{-1} \equiv a^{m-2} \pmod{m}
$$

```cpp
LL modinv(LL a) {
    return fastPow(a, MOD-2, MOD);
}
```

用 $O(n)$ 的时间求 $1$ 到 $n$ 对模 $m$ 的逆元
$$
ax \equiv 1 \pmod{m}
$$

```cpp
int n, m, inv[MAXN];

inv[1] = 1;
for(int x = 2; x <= n; x++) inv[x] = (inv[m % x] * (m-m/x)) % m;
```

#### 有理数取余

其实就是逆元
$$
\frac{a}{b} \equiv a \cdot b^{m-2} \pmod{m}
$$

### 分数

封装好的分数结构体，重载了加减乘除，所有计算在模`MOD`意义下进行

```cpp
struct Fraction {
    LL p, q; // p / q, 所有计算在模意义下
    Fraction(LL _p = 0, LL _q = 1) {
        if (_q < 0) _p = -_p, _q = -_q;
        _p %= MOD; _q %= MOD;
        if (_p < 0) _p += MOD;
        if (_q < 0) _q += MOD;
        p = _p;
        q = _q;
    }

    Fraction operator+(const Fraction &b) const {
        LL np = (p * b.q % MOD + b.p * q % MOD) % MOD;
        LL nq = (q * b.q) % MOD;
        return Fraction(np, nq);
    }

    Fraction operator-(const Fraction &b) const {
        LL np = (p * b.q % MOD - b.p * q % MOD + MOD) % MOD;
        LL nq = (q * b.q) % MOD;
        return Fraction(np, nq);
    }

    Fraction operator*(const Fraction &b) const {
        LL np = (p * b.p) % MOD;
        LL nq = (q * b.q) % MOD;
        return Fraction(np, nq);
    }

    Fraction operator/(const Fraction &b) const {
        LL np = (p * b.q) % MOD;
        LL nq = (q * b.p) % MOD;
        return Fraction(np, nq);
    }

    LD toLD() const {
        return (LD)p / (LD)q;
    }

    LL value() const { // 模意义下的值
        return (p % MOD) * modinv(q) % MOD;
    }

    Fraction norm() {
        LL g = __gcd(p, q);
        p /= g;
        q /= g;
        return Fraction(p, q);
    }
};

int main() {
    Fraction a(114, 514), b(0, 1);
    a = a + b;
    a.norm();
    cout << a.p << " " << a.q << endl;
    return 0;
}
```

### CRT 中国剩余定理

用于解以下一元线性同余方程组
$$
\begin{cases}
x \equiv a_1 \pmod{m_1} \\\ 
x \equiv a_2 \pmod{m_2} \\\ 
\ \ \ \vdots \\\ 
x \equiv a_n \pmod{m_n}
\end{cases}
$$
**所有模数 $m_i$ 互质**

注意配合前面的exgcd使用

考虑到实际情况一般答案会很大，建议开`long long`

```cpp
LL CRT(LL n, LL *m, LL *a) {
    LL N = 1, ans = 0;
    for(LL x = 1; x <= n; x++) N *= m[x];
    for(LL x = 1; x <= n; x++) {
        LL b = N / m[x], ny, tmp;
        exgcd(b, m[x], ny, tmp);
        ans = (ans + b * (ny < 0 ? ny + m[x] : ny) * a[x]) % N;
    }
    return ans;
}

LL a[MAXN], m[MAXN];
```

### EXCRT 扩展中国剩余定理

还是解上面的同余方程组，但是模数可以不互质

```cpp
LL EXCRT(LL n, LL *m, LL *a) {
    ILL M = 1, A = 0, x, y;
    for(int i = 1; i <= n; i++) {
        exgcd(M, m[i], x, y);
        LL gd = gcd(M, m[i]);
        x = (A-a[i]) / gd * x;
        A = A - M * x;
        M = m[i] / gd * M;
        A = (A % M + M) % M;
    }
    LL ans = (A % M + M) % M;
    return ans;
}

LL a[MAXN], m[MAXN];
```

### 组合数

#### 常用式子

定义：
$$
\binom{n}{k} = C(n, k) = \frac{n!}{k!(n-k)!}
$$

Pascal恒等式：
$$
\binom{n}{k} = \binom{n-1}{k} + \binom{n-1}{k-1}
$$

二项式定理：
$$
(a+b)^n = \sum_{k=0}^n \binom{n}{k} a^{n-k} b^k
$$

当 $a = b = 1$ 时，有：
$$
\sum_{k=0}^n \binom{n}{k} = 2^n
$$

#### 模数是质数时

可以用阶乘+逆元快速计算

```cpp
LL fac[MAXN+1], invfac[MAXN+1];

void initC() {
    fac[0] = 1;
    for(int i = 1; i <= MAXN; i++) fac[i] = fac[i-1] * i % MOD;
    invfac[MAXN] = fastPow(fac[MAXN], MOD - 2, MOD);
    for(int i = MAXN - 1; i >= 0; i--) invfac[i] = invfac[i+1] * (i+1) % MOD;
}

LL C(LL n, LL k) {
    if(k < 0 || k > n) return 0;
    return fac[n] * invfac[k] % MOD * invfac[n - k] % MOD;
}
```

#### Lucas 卢卡斯定理

模数不是质数时，可以用卢卡斯定理
$$
\binom{n}{k} \equiv 
\binom{\lfloor n/p \rfloor}{\lfloor k/p \rfloor}
\binom{n \bmod p}{k \bmod p}
\pmod{p}
$$

适用于 $n,k$ 很大（$\approx 10^{18}$）但 $p$ 较小（$\approx 10^6$）的情况

```cpp
LL Cmodp(LL n, LL k, LL p) {
    if(k > n) return 0;
    LL res = 1;
    for(LL i = 1; i <= k; i++) {
        res = res * (n - i + 1) % p;
        res = res * fastPow(i, p - 2, p) % p;
    }
    return res;
}

LL LucasC(LL n, LL k, LL p) {
    if(k == 0) return 1;
    return LucasC(n/p, k/p, p) * Cmodp(n%p, k%p, p) % p;
}
```

### 容斥原理

对于多个集合 $A_1, A_2, \cdots, A_n$ 有：

$$
\begin{align*}
\left| \bigcup_{i=1}^n A_i \right| 
&= \sum_{i=1}^n \left| A_i \right| - \sum_{1 \leq i < j \leq n} \left| A_i \cap A_j \right| + \\\ 
& \sum_{1 \leq i < j < k \leq n} \left| A_i \cap A_j \cap A_k \right| + \cdots + (-1)^{n-1} \left| A_1 \cap A_2 \cap \cdots \cap A_n \right| \\\ 
&= \sum_{k=1}^n (-1)^{k-1} \left( \sum_{1 \leq i_1 < i_2 < \cdots < i_k \leq n } \left| A_{i_1} \cap A_{i_2} \cap \cdots \cap A_{i_k} \right| \right) \\\ 
&= \sum_{k=1}^n (-1)^{k-1} \left( \sum_{1 \leq i_1 < i_2 < \cdots < i_k \leq n } \left| \bigcap_{j=1}^k A_{i_j} \right| \right)
\end{align*}
$$

### 线性代数

#### 矩阵快速幂

给定一个 $n \times n$ 的矩阵 $A$，还有次数 $k$ ，能快速算出 $A^k \bmod M$ ，时间复杂度 $O(n^3 \log k)$ ，适合用于加速 $n$ 比较小，但次数 $k$ 比较大的矩阵幂运算，经常用于优化递推DP式子

```cpp
const LL MOD = 1e9+7;

// re = i * j (Matrix)
void matrixTimes(LL i[MAXN][MAXN], LL j[MAXN][MAXN], LL re[MAXN][MAXN], int n)
{
    LL a[MAXN][MAXN] = {};
    for(int x = 1; x <= n; x++)
        for(int y = 1; y <= n; y++)
            for(int z = 1; z <= n; z++)
                a[x][y] = (a[x][y] + (i[x][z] * j[z][y]) % MOD) % MOD;
    for(int x = 1; x <= n; x++)
        for(int y = 1; y <= n; y++) re[x][y] = a[x][y];
}

void matrixFastPow(LL A[MAXN][MAXN], int n, LL k)
{
    LL I[MAXN][MAXN] = {};
    for(int x = 1; x <= n; x++) I[x][x] = 1;
    while(k > 0) {
        if(k & 1) matrixTimes(I, A, I, n);
        matrixTimes(A, A, A, n);
        k >>= 1;
    }
    for(int x = 1; x <= n; x++)
        for(int y = 1; y <= n; y++) A[x][y] = I[x][y];
}
```

#### 矩阵优化DP

##### 一维数组，多层状态

假设递推是
$$
f_n = a_1 f_{n-1} + a_2 f_{n-2} + \cdots + a_k f_{n-k}
$$
尝试构造矩阵乘法
$$
\begin{bmatrix}
f_n \\\ 
f_{n-1} \\\ 
f_{n-2} \\\ 
\vdots \\\ 
f_{n-k+1}
\end{bmatrix} = 
\begin{bmatrix}
a_1 & a_2 & a_3 & \cdots & a_{k-1} & a_k \\\ 
1 & 0 & 0 & \cdots & 0 & 0 \\\ 
0 & 1 & 0 & \cdots & 0 & 0 \\\ 
0 & 0 & 1 & \cdots & 0 & 0 \\\ 
\vdots & \vdots & \vdots & \ddots & \vdots & \vdots \\\ 
0 & 0 & 0 & \cdots & 1 & 0
\end{bmatrix} ^ {n-k}
\begin{bmatrix}
f_{k} \\\ 
f_{k-1} \\\ 
f_{k-2} \\\ 
\vdots \\\ 
f_{1}
\end{bmatrix}
$$
算出来第一行那个元素就是 $f_n$

##### 二维数组，单层状态

形如
$$
\begin{cases}
f_{i,1} = a_{1,1} f_{i-1,1} + a_{1,2} f_{i-1,2} + \cdots + a_{1,k} f_{i-1,k} \\\ 
f_{i,2} = a_{2,1} f_{i-1,1} + a_{2,2} f_{i-1,2} + \cdots + a_{2,k} f_{i-1,k} \\\ 
\ \ \vdots \\\ 
f_{i,k} = a_{k,1} f_{i-1,1} + a_{k,2} f_{i-1,2} + \cdots + a_{k,k} f_{i-1,k}
\end{cases}
$$

可以尝试构造矩阵乘法
$$
\begin{bmatrix}
f_{n,1} & f_{n,2} & \cdots & f_{n,k}
\end{bmatrix}=
\begin{bmatrix}
f_{1,1} & f_{1,2} & \cdots & f_{1,k}
\end{bmatrix}
\cdot
\begin{bmatrix}
a_{1,1} & a_{2,1} & \cdots & a_{k,1} \\\ 
a_{1,2} & a_{2,2} & \cdots & a_{k,2} \\\ 
\vdots & \vdots & \ddots & \vdots \\\ 
a_{1,k} & a_{2,k} & \cdots & a_{k,k}
\end{bmatrix} ^ {n-1}
$$

#### 高斯消元

解 $n$ 元一次线性方程组，时间复杂度 $O(n^3)$

```cpp
int n;
double a[MAXN][MAXN], b[MAXN];
double ans[MAXN];

// -1: 无解，0: 无穷解，1: 唯一解
int Gauss() {
    for (int i = 1; i <= n; i++) a[i][n + 1] = b[i];
    int r = 1;
    for(int c = 1; c <= n; c++) {
        int t = r;
        for(int i = r; i <= n; i++)
            if(fabs(a[i][c]) > fabs(a[t][c])) t = i;
        if(fabs(a[t][c]) < eps) continue;
        for(int j = c; j <= n + 1; j++) swap(a[t][j], a[r][j]);
        for(int j = n + 1; j >= c; j--) a[r][j] /= a[r][c];
        for(int i = r + 1; i <= n; i++)
            if (fabs(a[i][c]) > eps)
                for (int j = n + 1; j >= c; j--) a[i][j] -= a[r][j] * a[i][c];
        r++;
    }
    for(int i = r; i <= n; i++) {
        bool allZero = true;
        for(int j = 1; j <= n; j++)
            if (fabs(a[i][j]) > eps) { allZero = false; break; }
        if(allZero && fabs(a[i][n + 1]) > eps) return -1;
    }
    if(r > n) {
        for(int i = n; i >= 1; i--) {
            ans[i] = a[i][n + 1];
            for (int j = i + 1; j <= n; j++) ans[i] -= a[i][j] * ans[j];
        }
        return 1;
    }
    return 0;
}
```

#### 线性基

线性基可以维护一个数组里任意几个数异或的最大值 / 最小值 / 查询是否存在 / 第 $k$ 大的值 / 查询排名。

```cpp
const int W = 60;
LL s[MAXN], p[MAXN];
bool hasZero;

// 插入线性基集合
void insert(LL a) {
    if(a == 0) {
        hasZero = true;
        return;
    }
    for(int i = W; i >= 0; i--) {
        if(!(a >> i)) continue;
        if(!p[i]) {
            p[i] = a;
            break;
        }
        a ^= p[i];
    }
}

// 查询能否异或出这个值
bool askxor(LL a) {
    for(int i = W; i >= 0; i--) {
        if(a >> i) a ^= p[i];
    }
    return a == 0;
}

// 查询异或可得到的最大值
LL getmax() {
    LL re = 0;
    for(int i = W; i >= 0; i--) {
        re = max(re, re ^ p[i]);
    }
    return re;
}

// 查询异或可得到的最小值（0 特殊）
LL getmin() {
    if(hasZero) return 0;
    for(int i = 0; i <= W; i++) {
        if(p[i]) {
            return p[i];
        }
    }
    return 0;
}
```

### 斐波那契数（递归数）与卡特兰数

#### 递归数

考虑非负整数 $n$ 上的递归关系：
$$
F_n = 
\begin{cases}
f_0 & \text{if } n = 0 \\\ 
f_1 & \text{if } n = 1 \\\ 
a \cdot F_{n-1} + b \cdot F_{n-2} & \text{otherwise}
\end{cases}
$$

可以得到通项公式：
$$
F_n = \frac{k^n(f_1 - m f_0) - m^n(f_1 - k f_0)}{k-m} \\\ 
\\\ 
m, k = \frac{a \pm \sqrt{a^2+4b}}{2}
$$

#### 卡特兰数

常用于二叉树、括号匹配、多边形三角划分等问题

$$
\begin{align*}
f_n &= \sum_{i=0}^{n-1}f_i \cdot f_{n-i+1} \\\ 
    &= \frac{C_{2n}^n}{n+1} \\\ 
	&= C_{2n}^n - C_{2n}^{n-1}
\end{align*}
$$

### 素数相关

#### 质因数分解

能在 $O(\sqrt{n})$ 的时间复杂度下求出 $n$ 的质因数分解

```cpp
void Factorize(LL n, vector<int> &factors, map<int,int> &primeCnt) {
    for(LL i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            factors.push_back((int)i);
            while (n % i == 0) {
                primeCnt[(int)i]++;
                n /= i;
            }
        }
    }
    if(n > 1) {
        factors.push_back((int)n);
        primeCnt[(int)n]++;
    }
}
```

#### 欧拉线性筛素数

能在 $O(n)$ 的时间复杂度下快速筛出 $1$ 到 $n$ 的所有素数

```cpp
bool isPrime[MAXN];
int Prime[MAXN];

// 筛到 n
void EulerPrime(int n) {
    int cnt = 0;
    memset(isPrime, true, sizeof(isPrime));
    isPrime[1] = 0;
    for(int x = 2; x <= n; x++) {
        if(isPrime[x]) Prime[++cnt] = x;
        for(int y = 1; y <= cnt && x*Prime[y] <= n; y++) {
            isPrime[x*Prime[y]] = false;
            if(x % Prime[y] == 0) break;
        }
    }
}
```

#### 威尔逊定理

$p$ 为素数 $\Leftrightarrow (p-1)! \equiv -1 \pmod p$

#### 费马小定理

若 $p$ 为素数，则：
$$
a^p \equiv a \pmod p
$$

特殊形式：

若 $p$ 为素数，$a$ 为正整数，且 $a$ 和 $p$ 互质，则：
$$
a^{p-1} \equiv 1 \pmod p
$$

#### 欧拉函数和定理

欧拉函数：对于正整数 $n$，欧拉函数 $\phi(n)$ 是小于等于 $n$ 中与 $n$ 互质的数的数目，计算公式：

$$
\phi(n) = n \prod_{i=1}^k \left(1-\frac{1}{p_i}\right)
$$

其中，$p_i$ 是 $n$ 的质因子，而且**只计算一次**

前置定理：

- 若 $p$ 为素数，则：$\phi(p) = p-1$
- 若 $p$ 为素数，其幂次 $p^a$，则：$\phi(p^a) = (p-1) \cdot p^{a-1}$
- 若 $a$ 与 $b$ 互质，则：$\phi(ab) = \phi(a) \cdot \phi(b)$

欧拉定理：

若 $a$ 与 $m$ 互质，则:

$$
a^{\phi(m)} \equiv 1 \pmod m
$$

可以在 $O(n)$ 的时间复杂度下算出 $\phi(1)$ 到 $\phi(n)$，也可以用 $O(\sqrt{n})$ 的复杂度单次算出 $\phi(n)$
```cpp
int phi[MAXN], prime[MAXN];
bool isComposite[MAXN];
int tot = 0;

// 算 1 到 n
void EulerFunctionAll(int n) {
    phi[1] = 1;
    for(int x = 2; x <= n; x++) {
        if(!isComposite[x]) {
            prime[tot++] = x;
            phi[x] = x - 1; // 质数：φ(p)=p-1
        }
        for(int y = 0; y < tot && 1LL * x * prime[y] <= n; y++) {
            int p = prime[y];
            isComposite[x * p] = true;
            if (x % p == 0)
            {
                phi[x * p] = phi[x] * p;
                break;
            }
            else phi[x * p] = phi[x] * (p - 1);
        }
    }
} // 结果存在 phi 数组里

// 单次计算
int EulerFunction(int n) {
    int re = n;
    for(int x = 2; x*x <= n; x++) {
        if(n % x == 0) {
            re = re / x * (x-1);
            while(n % x == 0) n /= x;
        }
    }
    if(n > 1) re = re / n * (n-1);
    return re;
}
```

#### BSGS 大步小步算法

能在 $O(\sqrt{p})$ 的时间内求出形如
$$
a^x \equiv b \pmod p
$$
的高次同余方程的解 $x$，或给出无解

```cpp
// 求解 a^x = b (mod p)
LL BSGS(LL a, LL b, LL p) {
    map <LL, LL> hash;
    hash.clear();
    b %= p;
    LL t = sqrt(p)+1;
    for(LL i = 0; i < t; i++) {
        hash[b*fastPow(a, i, p)%p] = i;
    }
    a = fastPow(a, t, p);
    if(!a) return b == 0 ? 1 : -1;
    for(LL i = 0; i <= t; i++) {
        LL val = fastPow(a, i, p);
        LL j = hash.find(val) == hash.end() ? -1 : hash[val];
        if(j >= 0 && i*t-j >= 0) return i*t-j;
    }
    return -1; // No Solution
}
```

#### 莫比乌斯反演

给定函数 $F(n)$ 和 $f(n)$ 定义在非负整数集合上，并满足条件：
$$
F(n) = \sum_{d|n} f(d)
$$
则有结论：
$$
f(n) = \sum_{d|n}\mu(d)F\left(\frac{n}{d}\right)
$$

其中，莫比乌斯函数
$$
\mu(n) = 
\begin{cases}
1 & n = 1 \\\ 
0 & n\text{ 含有平方因子} \\\ 
(-1)^k & k\text{ 是 }n\text{ 不同的质因子个数}
\end{cases}
$$
也就是说，$n>1$ 的时候，如果能分解成 $k$ 个不同的质因数直接相乘，那么函数值为 $(-1)^k$，否则为 $0$。比如 $\mu(10) = 1$，$\mu(12) = 0$
其有两个性质：
1. 对于任意正整数 $n$ 有：$\sum_{d|n} \mu(d) = \begin{cases}1 & n = 1 \\\ 0 & n > 1\end{cases}$
2. 对于任意正整数 $n$ 有：$\sum_{d|n} \frac{\mu(d)}{d} = \frac{\phi(n)}{n}$

可以在 $O(n)$ 的时间复杂度下算出 $\mu(1)$ 到 $\mu(n)$
```cpp
bool vis[MAXN];
int mu[MAXN], prime[MAXN];

void MobiusFunctionAll(int n) {
    mu[1] = 1;
    int cnt = 0;
    for(int x = 2; x < n; x++) {
        if(!vis[x]) {
            prime[cnt++] = x;
            mu[x] = -1;
        }
        for(int y = 0; y < cnt && x*prime[y] < n; y++) {
            vis[x*prime[y]] = true;
            if(x % prime[y]) mu[x*prime[y]] = -mu[x];
            else {
                mu[x*prime[y]] = 0;
                break;
            }
        }
    }
}
```

### 多项式

#### 拉格朗日插值

经过 $n$ 个不同的点可以唯一地确定一个 $n-1$ 次多项式 $y=f(x)$，有拉格朗日插值公式可以在 $O(n^2)$ 的时间内求出 $f(x) \bmod M$
$$
f(k) = \sum_{i=1}^{n} f(x_i) \prod_{j \not= i} \frac{k-x_j}{x_i-x_j}
$$

```cpp
LL n, xx[MAXN], f[MAXN];

LL LagrangeIn(LL k) {
    LL re = 0;
    for(int i = 1; i <= n; i++) {
        LL p = f[i] % MOD, q = 1ll;
        for(int j = 1; j <= n; j++) {
            if(i == j) continue;
            p = p * (k - xx[j]) % MOD;
            q = q * (xx[i] - xx[j]) % MOD;
        }
        re = (re + (p * fastPow(q, MOD-2, MOD)) % MOD) % MOD;
    }
    if(re < 0) re += MOD;
    return re;
}
```

没用的板子之用拉格朗日插值法 $O(n^3)$ 解多项式系数

```cpp
vector <LL> LagrangeInCoef() {
    vector <LL> re (n+1, 0);
    for(int i = 0; i <= n; i++) {
        LL denom = 1;
        for(int j = 0; j <= n; j++) {
            if(i == j) continue;
            denom = denom * ((xx[i] - xx[j] + MOD) % MOD) % MOD;
        }
        denom = fastPow(denom, MOD-2, MOD);
        vector <LL> poly = {1};
        for(int j = 0; j <= n; j++) {
            if(i == j) continue;
            vector <LL> newPoly(poly.size()+1, 0);
            for(int k = 0; k < poly.size(); k++) {
                newPoly[k] = (newPoly[k] - poly[k] * xx[j]) % MOD;
                if(newPoly[k] < 0) newPoly[k] += MOD;
                newPoly[k+1] = (newPoly[k+1] + poly[k]) % MOD;
            }
            poly.swap(newPoly);
        }
        LL coeff = f[i] * denom % MOD;
        for(int j = 0; j <= n; j++) {
            re[j] = (re[j] + poly[j] * coeff) % MOD;
        }
    }
    return re;
}
```

#### 多项式乘法

给定一个 $n$ 次多项式 $F(x)$ ，和一个 $m$ 次多项式 $G(x)$ ，求出 $F(x) \times G(x)$

**FFT**

```cpp
int l, r[MAXN];
int limit = 1;

vector <complex <double>> FFT(vector <complex <double>> F, int type) {
    for(int i = 0; i < limit; i++) 
        if(i < r[i]) swap(F[i], F[r[i]]);
    for(int mid = 1; mid < limit; mid <<= 1) {
        complex <double> Wn(cos(Pi/mid), type*sin(Pi/mid));
        for(int R = mid<<1, j = 0; j < limit; j += R) {
            complex <double> w(1, 0);
            for(int k = 0; k < mid; k++, w = w*Wn) {
                complex <double> x = F[j+k], y = w*F[j+mid+k];
                F[j+k] = x + y;
                F[j+mid+k] = x - y;
            }
        }
    }
    return F;
}

vector <complex <double>> polyMulFFT(vector <complex <double>> A, vector <complex <double>> B) {
    limit = 1, l = 0;
    int n = A.size()-1, m = B.size()-1;
	while(limit <= n + m) limit <<= 1, l++;
    A.resize(limit+1);
    B.resize(limit+1);
	for(int i = 0; i < limit; i++) r[i] = (r[i>>1]>>1)|((i&1)<<(l-1)) ;
	A = FFT(A, 1); 
    B = FFT(B, 1);
    vector <complex <double>> C(limit+1);
	for(int i = 0; i < limit; i++) C[i] = A[i] * B[i];
	C = FFT(C, -1);
	for(int i = 0; i <= n + m; i++) C[i] = (int)(C[i].real()/limit + 0.5);
    return C;
}
```

**NTT**

```cpp
int l, r[MAXN];
int limit = 1;

vector <LL> NTT(vector <LL> F, int type) {
    for(int i = 0; i < limit; i++) 
        if(i < r[i]) swap(F[i], F[r[i]]);
    for(int mid = 1; mid < limit; mid <<= 1) {
        LL Wn = fastPow(G, (MOD-1)/(mid<<1));
        if(type == -1) Wn = fastPow(Wn, MOD-2);
        for(int R = mid<<1, j = 0; j < limit; j += R) {
            LL w = 1;
            for(int k = 0; k < mid; k++, w = w*Wn % MOD) {
                LL x = F[j+k], y = w*F[j+mid+k] % MOD;
                F[j+k] = (x+y) % MOD;
                F[j+mid+k] = (x-y+MOD) % MOD;
            }
        }
    }
    if(type == -1) {
        LL inv = fastPow(limit, MOD-2);
        for(int i = 0; i < limit; i++) F[i] = F[i]*inv % MOD;
    }
    return F;
}

vector <LL> polyMulNTT(vector <LL> A, vector <LL> B) {
    limit = 1, l = 0;
    int n = A.size()-1, m = B.size()-1;
	while(limit <= n + m) limit <<= 1, l++;
    A.resize(limit+1);
    B.resize(limit+1);
	for(int i = 0; i < limit; i++) r[i] = (r[i>>1]>>1)|((i&1)<<(l-1)) ;
	A = NTT(A, 1); 
    B = NTT(B, 1);
    vector <LL> C(limit+1);
	for(int i = 0; i < limit; i++) C[i] = A[i]*B[i] % MOD;
	C = NTT(C, -1);
    return C;
}
```

## 图论

我是邻接表享受者😎
没有特殊说明默认全都是邻接表建图

### 最短路

#### SPFA

有向/无向图单源最短路，能求出st到任意一个点的最短路（无负环），时间复杂度最坏 $O(nm)$ ，但实际上会比较快

如果有负环需要加一个cnt数组用于记录入队次数，SPFA里面里判断负环的方法是：**记录每个节点入队的次数，如果某个点入队次数超过 $n$（点数），说明存在负环**

```cpp
struct node {
    int v, dis;
};

vector <node> g[MAXN];

int n, m, d[MAXN]; // 需要初始化d[i] = INF
bool vis[MAXN];

void SPFA(int st) {
    queue <int> q;
    d[st] = 0;
    vis[st] = true;
    q.push(st);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = false;
        for(int x = 0; x < g[u].size(); x++) {
            int v = g[u][x].v, dis = g[u][x].dis;
            if(d[v] > d[u] + dis) {
                d[v] = d[u] + dis;
                if(!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
}
```

#### Dijkstra

有向/无向图单源最短路，能求出st到任意一个点的最短路（无负环），加上小根堆优化后时间复杂度 $O(m \log n)$

这里还加了个输出最短路径

```cpp
struct node {
	int v, dis;
};

struct pri {
	int ans, id;
	bool operator < (const pri &x) const{return x.ans < ans;}
};

priority_queue <pri> q;
vector <node> g[MAXN];
int n, m, d[MAXN], pre[MAXN];
bool vis[MAXN];

void Dijkstra(int st) {
	for(int x = 1; x <= n; x++) {
        d[x] = INF;
        pre[x] = -1;
        vis[x] = false;
    }
	d[st] = 0;
	q.push((pri){0, st});
	while(!q.empty()) {
		pri tmp = q.top();
		q.pop();
		int u = tmp.id;
		if(!vis[u]) {
			vis[u] = true;
			for(int y = 0; y < g[u].size(); y++) {
				int v = g[u][y].v;
				if(!vis[v] && d[u] + g[u][y].dis < d[v]) {
					d[v] = d[u] + g[u][y].dis;
                    pre[v] = u;
                    q.push((pri){d[v], v});
				}
			}
		}
	}
}

// 从ed回溯
void printPath(int ed) {
    vector <int> ans;
    for(int u = ed; u != -1; u = pre[u]) ans.push_back(u);
    reverse(ans.begin(), ans.end());
    for(int u : ans) cout << u << " ";
    cout << endl;
}
```

#### Floyd

有向/无向图多源最短路，时间复杂度 $O(n^3)$ ，代码思路简单所以复杂度也比较高，可以判负环

```cpp
int n, m;
int d[MAXN][MAXN];
bool findN;

void Floyd() {
	findN = false;
	for(int z = 1; z <= n; z++)
		for(int x = 1; x <= n; x++)
			for(int y = 1; y <= n; y++)
				if(d[x][z] < INF && d[z][y] < INF)
					d[x][y] = min(d[x][y], d[x][z] + d[z][y]);
	for(int x = 1; x <= n; x++)
		if(d[x][x] < 0) findN = true; // 找到负环
}
```
然后 `main` 函数里要这样子初始化以及读边
```cpp
int main() {
    cin >> n >> m;
	for(int x = 1; x <= n; x++)
		for(int y = 1; y <= n; y++)
			d[x][y] = (x == y ? 0 : INF);
	
	for(int x = 1; x <= m; x++) {
		int u, v, w;
		cin >> u >> v >> w;
		d[u][v] = min(d[u][v], w);
	}
}
```

#### A*

启发式搜索算法，可以理解为 Dijkstra 的升级版。

```cpp
struct node {
    int x, y;
    double val;
    bool operator < (const node &a) const {
        return val > a.val;
    }
} pre[MAXN][MAXN];

int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1}, dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};
string s[MAXN];
int g[MAXN][MAXN];
double f[MAXN][MAXN];
bool vis[MAXN][MAXN];
int n, m, ex, ey;
vector <node> ansPath;

double hfun(int ux, int uy) {
    return sqrt((double)((ux-ex)*(ux-ex)+(uy-ey)*(uy-ey)));
}

void buildPath() {
    int ux = ex, uy = ey;
    while(!(ux == -1 && uy == -1)) {
        ansPath.push_back((node){ux, uy, 0});
        int vx = pre[ux][uy].x, vy = pre[ux][uy].y;
        ux = vx, uy = vy;
    }
}

void AStar(int sx, int sy) {
    cout << "A*: " << sx << " " << sy << "-> " << ex << " " << ey << endl;
    for(int x = 0; x < n; x++) {
        for(int y = 0; y < m; y++) g[x][y] = INF;
    }
    g[sx][sy] = 0;
    f[sx][sy] = hfun(sx, sy);
    pre[sx][sy] = (node){-1, -1};

    priority_queue <node> q;
    q.push((node){sx, sy, f[sx][sy]});
    while(!q.empty()) {
        node tmp = q.top(); q.pop();
        int ux = tmp.x, uy = tmp.y, val = tmp.val;
        if(vis[ux][uy]) continue;
        vis[ux][uy] = true;
        if(ux == ex && uy == ey) {
            buildPath();
            return;
        }
        for(int o = 0; o < 8; o++) {
            int vx = ux + dx[o], vy = uy + dy[o];
            if(vx < 0 || vx >= n || vy < 0 || vy >= m) continue;
            if(s[vx][vy] == '*') continue;
            int tmpg = g[ux][uy] + 1;
            if(tmpg < g[vx][vy]) {
                pre[vx][vy] = (node){ux, uy, 0};
                g[vx][vy] = tmpg;
                f[vx][vy] = g[vx][vy] + hfun(vx, vy);
                q.push((node){vx, vy, f[vx][vy]});
            }
        }
    }
}
```

这里给个输入样例：
```
5 5
s....
**..*
.....
..***
....t
```
输出的路径：
```
##...
**#.*
..#..
.#***
..###
```

### 最小生成树

#### Kruskal

给定一个无向图，求出最小生成树，模板这里是返回了最小生成树的边权之和，然后把相应的边存起来

时间复杂度 $O(m \log m)$

```cpp
struct edge {
	int u, v, w;
} e[MAXN];

int n, m;
int fa[MAXN];
vector <edge> MST;

bool cmp(edge x, edge y) {
	return x.w < y.w;
}

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int Kruskal() {
	for(int x = 1; x <= n; x++) fa[x] = x;
	int ans = 0;
	sort(e+1, e+m+1, cmp);
	for(int x = 1; x <= m; x++) {
		int u = find(e[x].u), v = find(e[x].v);
		if(u == v) continue;
		fa[v] = u;
		ans += e[x].w;
		MST.push_back(e[x]);
	}
	return ans;
}
```

### Tarjan

#### 割点

**无向图**中用Tarjan找割点

```cpp
int n, m, cnt;
vector <int> g[MAXN];
int dfn[MAXN], low[MAXN];
bool isCut[MAXN];

void Tarjan(int u, int parent) {
	low[u] = dfn[u] = ++cnt;
	int child = 0;
	for(int x = 0; x < g[u].size(); x++) {
		int v = g[u][x];
		if(!dfn[v]) {
			Tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if(parent != -1 && low[v] >= dfn[u]) isCut[u] = true;
			child++;
		}
		else if(v != parent) low[u] = min(low[u], dfn[v]);
	}
	if(parent == -1 && child >= 2) isCut[u] = true;
}

vector <int> getCutPoint() {
	for(int x = 1; x <= n; x++) // 注意下标
		if(!dfn[x]) Tarjan(x, -1);
	vector <int> ans;
	for(int x = 1; x <= n; x++)
		if(isCut[x]) ans.push_back(x);
	return ans;
}
```

#### 桥

**无向图**中用Tarjan找桥

```cpp
struct edge {
	int u, v;
};

int n, m, cnt;
vector <int> g[MAXN];
int dfn[MAXN], low[MAXN];
vector <edge> ans;

void Tarjan(int u, int parent) {
	low[u] = dfn[u] = ++cnt;
	for(int x = 0; x < g[u].size(); x++) {
		int v = g[u][x];
		if(v == parent) continue;
		if(!dfn[v]) {
			Tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] > dfn[u]) ans.push_back((edge){min(u,v), max(u,v)});
		}
		else low[u] = min(low[u], dfn[v]);
	}
}

bool cmp(edge x, edge y) {
	if(x.u == y.u) return x.v < y.v;
	return x.u < y.u;
}

vector <edge> getBridge() {
	for(int x = 1; x <= n; x++) // 注意下标
		if(!dfn[x]) Tarjan(x, -1);
	sort(ans.begin(), ans.end(), cmp);
	return ans;
}
```

#### 强连通分量

**有向图**中用Tarjan找强连通分量并染色

```cpp
int n, m, cnt, colcnt;
vector <int> g[MAXN];
int dfn[MAXN], low[MAXN], color[MAXN];
bool vis[MAXN];
stack <int> st;

void Tarjan(int u) {
	dfn[u] = low[u] = ++cnt;
	st.push(u);
	vis[u] = true;
	for(int x = 0; x < g[u].size(); x++) {
		int v = g[u][x];
		if(!dfn[v]) {
			Tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if(vis[v]) low[u] = min(low[u], dfn[v]); // 找到环了
	}
	if(dfn[u] == low[u]) {
		colcnt++;
		int v;
		do {
			v = st.top(); st.pop();
			vis[v] = false;
			color[v] = colcnt; // 染色
		} while(v != u);
	}
}

vector <int> ng[MAXN];

// 用颜色建新图
void newGraph() {
	for(int x = 0; x < n; x++) {
		for(int y = 0; y < g[x].size(); y++) {
			int v = g[x][y];
			if(color[x] != color[v]) ng[color[x]].push_back(color[v]);
		}
	}
}
```

边双连通分量，即无向图Tarjan缩点。记录一个 $last$ 即可

```cpp
struct edge {
	int v, id;
};

int dfn[MAXN], low[MAXN], cnt, coli;
bool vis[MAXN];
stack <int> st;
vector <edge> g[MAXN];
vector <int> col[MAXN];

void Tarjan(int u, int lst) {
	dfn[u] = low[u] = ++cnt;
	vis[u] = true;
	st.push(u);
	for(int x = 0; x < g[u].size(); x++) {
		int v = g[u][x].v, id = g[u][x].id;
		if(id == lst) continue;
		if(!dfn[v]) {
			Tarjan(v, id);
			low[u] = min(low[u], low[v]);
		}
		else if(vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if(dfn[u] == low[u]) {
		coli++;
		int v;
		do {
			v = st.top(); st.pop();
			vis[v] = false;
			col[coli].push_back(v);
		} while(v != u);
	}
}
```

### 拓扑排序

有向无环图中（DAG, Directed Acyclic Graph）的每一条有向边（ $u \rightarrow v$ ），在排序中顶点 $u$ 必须在顶点 $v$ 的前面

#### Kahn算法

基于入度的高效算法，还能检测不合法的环，时间复杂度 $O(n+m)$

```cpp
int n, m;
vector <int> g[MAXN];
int ind[MAXN];

vector <int> topoSort() {
	vector <int> ans;
	queue <int> q;
	for(int x = 1; x <= n; x++) // 注意下标
		for(int y = 0; y < g[x].size(); y++) ind[g[x][y]]++; // 计算入度
	for(int x = 1; x <= n; x++)
		if(ind[x] == 0) q.push(x); // 将入度为0的点丢进序列
	while(!q.empty()) {
		int u = q.front(); q.pop();
		ans.push_back(u);
		for(int x = 0; x < g[u].size(); x++) {
			int v = g[u][x];
			ind[v]--;
			if(ind[v] == 0) q.push(v);
		}
	}
	if(ans.size() != n) cout << "FIND CIRCLE!" << endl; // 找到环，不合法
	return ans;
}
```

### 树

#### 树的直径

跑两遍dfs找最远的两个点的距离，就是树的直径，时间复杂度 $O(n)$

```cpp
struct node {
	int v, w;	
};

int n, m;
vector <node> g[MAXN];
bool vis[MAXN];
int maxDist, farNode;

void findFar(int u, int dist) {
	vis[u] = true;
	if(dist > maxDist) {
		maxDist = dist;
		farNode = u;
	}
	for(int x = 0; x < g[u].size(); x++) {
		int v = g[u][x].v, w = g[u][x].w;
		if(!vis[v]) findFar(v, dist + w);
	}
}

int treeDiameter() {
	memset(vis, 0, sizeof(vis));
	maxDist = 0;
	findFar(1, 0);

	memset(vis, 0, sizeof(vis));
	maxDist = 0;
	findFar(farNode, 0);

	return maxDist;
}
```

#### 树的高度

换根DP，时间复杂度 $O(n)$ 能求分别以 $1-n$ 所有节点为根的树的高度

```cpp
struct node
struct node {
	int v, w;	
};

int n, m;
vector <node> g[MAXN];
int dp[MAXN], ht[MAXN];

void treeDepth(int u, int parent) {
	dp[u] = 0;
	for(int x = 0; x < g[u].size(); x++) {
		int v = g[u][x].v, w = g[u][x].w;
		if(v == parent) continue;
		treeDepth(v, u);
		dp[u] = max(dp[u], dp[v] + w);
	}
}

void changeRoot(int u, int parent, int up) {
	vector <int> pre, suf;
	for(int x = 0; x < g[u].size(); x++) {
		int v = g[u][x].v, w = g[u][x].w;
		if(v == parent) pre.push_back(up);
		else pre.push_back(dp[v] + w);
	}
	suf = pre;
	for(int x = 1; x < g[u].size(); x++) pre[x] = max(pre[x], pre[x-1]);
	for(int x = g[u].size() - 2; x >= 0; x--) suf[x] = max(suf[x], suf[x+1]);
	ht[u] = max(dp[u], up);
	for(int x = 0; x < g[u].size(); x++) {
		int v = g[u][x].v, w = g[u][x].w;
		if(v == parent) continue;
		int left = (x == 0 ? -INF : pre[x-1]);
		int right = (x == g[u].size()-1 ? -INF : suf[x+1]);
		int newUp = max(up, max(left, right)) + w;
		changeRoot(v, u, newUp);
	}
}

vector <int> treeHeight() {
	treeDepth(0, -1);
	changeRoot(0, -1, 0);
	vector <int> re;
	for(int x = 0; x < n; x++) re.push_back(ht[x]);
	return re;
}
```

#### LCA

倍增求LCA

```cpp
int n, m;
vector <int> g[MAXN];
int lg[MAXN], dep[MAXN], fa[MAXN][32];

void dfs(int u, int f) {
	fa[u][0] = f;
	dep[u] = dep[f] + 1;
	for(int x = 1; x < 20; x++) {
		if (fa[u][x - 1] == 0) break;
		fa[u][x] = fa[fa[u][x - 1]][x - 1];
	}
	for(int x = 0; x < g[u].size(); x++)
		if(g[u][x] != f) dfs(g[u][x], u);
}

void initLCA(int root) {
	lg[0] = -1;
	for(int x = 1; x <= n; x++) lg[x] = lg[x >> 1] + 1;
	dfs(root, 0);
}

int getLCA(int a, int b) {
	if(dep[a] < dep[b]) swap(a, b);
	for (int i = 19; i >= 0; i--)
		if (dep[a] - (1 << i) >= dep[b]) a = fa[a][i];
	if(a == b) return a;
	for(int x = lg[dep[a]]; x >= 0; x--)
		if(fa[a][x] != fa[b][x]) a = fa[a][x], b = fa[b][x];
	return fa[a][0];
}
```

### 网络流

邻接表享受者😎

#### Dinic

时间复杂度 $O(n^2m)$

唐逼 GPT 一开始给我生成的板子是错的，藏了半年没发现，被某次大数据卡了就老实了

```cpp
struct node {
	int v, rev, cap;
};

int n, m;
vector <node> g[MAXN];
int level[MAXN], iter[MAXN];

void addEdge(int u, int v, int cap) {
	g[u].push_back((node){v, (int)g[v].size(), cap});
	g[v].push_back((node){u, (int)g[u].size()-1, 0}); // 反向边
}

void buildLevel(int st) {
	for(int x = 0; x < n; x++) level[x] = -1;
	queue <int> q;
	level[st] = 0;
	q.push(st);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int x = 0; x < g[u].size(); x++) {
			int v = g[u][x].v, cap = g[u][x].cap;
			if(cap > 0 && level[v] < 0) {
				level[v] = level[u] + 1;
				q.push(v);
			}
		}
	}
}

int DinicDFS(int u, int ed, int upToFlow)
{
	if(u == ed) return upToFlow;
    int out = 0;
	for(int x = iter[u]; x < g[u].size(); x++) {
		int v = g[u][x].v, rev = g[u][x].rev, cap = g[u][x].cap;
		if(cap > 0 && level[u] < level[v]) {
			int d = DinicDFS(v, ed, min(upToFlow, cap));
			g[u][x].cap -= d;
			g[v][rev].cap += d;
			out += d;
			if(!(upToFlow-=d)) break;
		}
	}
	if(!out) level[u]=-1;
	return out;
}

int Dinic(int st, int ed) {
	int maxFlow = 0;
	while(1) {
		buildLevel(st);
		if(level[ed] < 0) break; // 到不了终点
		for(int x = 0; x < n; x++) iter[x] = 0; // 注意下标
		int f;
		while((f = DinicDFS(st, ed, INF)) > 0) maxFlow += f;
	}
	return maxFlow;
}
```

#### 费用流

最小费用 & 最小费用最大流

基于SPFA，时间复杂度 $O(F*(n+m))$ ， $F$ 是最大流总和

```cpp
struct node {
	int v, rev, cap, cost;
};

struct reNode {
	int flow, cost;
};

int n, m;
vector <node> g[MAXN];
int dist[MAXN], prevv[MAXN], preve[MAXN];
bool vis[MAXN];

void addEdge(int u, int v, int cap, int cost) {
	g[u].push_back((node){v, (int)g[v].size(), cap, cost});
	g[v].push_back((node){u, (int)g[u].size()-1, 0, -cost}); // 反向边
}

bool SPFA(int st, int ed) {
	for(int x = 0; x < n; x++) dist[x] = INF, vis[x] = false; // 注意下标
	dist[st] = 0;
	queue <int> q;
	q.push(st);
	vis[st] = true;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		vis[u] = false;
		for(int x = 0; x < g[u].size(); x++) {
			int v = g[u][x].v, cap = g[u][x].cap, cost = g[u][x].cost;
			if(cap > 0 && dist[v] > dist[u] + cost) {
				dist[v] = dist[u] + cost;
				prevv[v] = u;
				preve[v] = x;
				if(!vis[v]) {
					q.push(v);
					vis[v] = true;
				}
			}
		}
	}
	return dist[ed] < INF;
}

reNode minCostMaxFlow(int st, int ed) {
	int flow = 0, cost = 0;
	while(SPFA(st, ed)) {
		int f = INF;
		for(int u = ed; u != st; u = prevv[u]) f = min(f, g[prevv[u]][preve[u]].cap);
		flow += f;
		cost += f * dist[ed];
		for(int u = ed; u != st; u = prevv[u]) {
			g[prevv[u]][preve[u]].cap -= f;
			g[u][g[prevv[u]][preve[u]].rev].cap += f;
		}
	}
	return (reNode){flow, cost};
}

int minCost(int st, int ed, int F) {
	int flow = 0, cost = 0;
	while(F > 0 && SPFA(st, ed)) {
		int f = F;
		for(int u = ed; u != st; u = prevv[u]) f = min(f, g[prevv[u]][preve[u]].cap);
		F -= f;
		flow += f;
		cost += f * dist[ed];
		for(int u = ed; u != st; u = prevv[u]) {
			g[prevv[u]][preve[u]].cap -= f;
			g[u][g[prevv[u]][preve[u]].rev].cap += f;
		}
	}
	return F > 0 ? -1 : cost;
}
```

#### 二分图匹配

建图：超级原点 $S$ ->左边所有点->右边所有点->超级汇点 $T$ ，每条边流量为 $1$
时间复杂度 $O(\sqrt{n}m)$

```cpp
int n1, n2, S, T;

void buildBiGraph() {
	cin >> n1 >> n2 >> m;
	n = n1 + n2 + 2;
	S = n1 + n2;
	T = S + 1;
	for(int x = 1; x <= m; x++) {
		int u, v;
		cin >> u >> v;
		addEdge(u, v+n1, 1);
	}
	for(int x = 0; x < n1; x++) addEdge(S, x, 1);
	for(int x = 0; x < n2; x++) addEdge(x+n1, T, 1);
}

int biMatchNum() {
	return Dinic(S, T); // 最大匹配边数
}

struct edge {
	int u, v;
};

// 基于残量网络找匹配边
vector <edge> biMatchEdge() {
	vector <edge> re;
	for(int u = 0; u < n1; u++) {
		for(int x = 0; x < g[u].size(); x++) {
			int v = g[u][x].v, cap = g[u][x].cap;
			if(v >= n1 && v < n1 + n2 && cap == 0) re.push_back((edge){u, v-n1});
		}
	}
	return re;
}
```

## 数据结构

### 并查集

可以用于判断是否在一个连通块内，时间复杂度接近常数

```cpp
int n, m;
int fa[MAXN], sz[MAXN];

int getfa(int x) {
    return (x == fa[x]) ? x : fa[x] = getfa(fa[x]);
}

void merge(int x, int y) {
    x = getfa(x), y = getfa(y);
    if(x == y) return;
    if(sz[x] < sz[y]) swap(x, y);
    fa[y] = x;
    sz[x] += sz[y];
}

void initDSU() {
    for(int x = 1; x <= n; x++) fa[x] = x, sz[x] = 1;
}
```

### 树状数组

时间 $O(\log{n})$ 单点修改，区间求和，注意这里的 Tsum 查询之后是前缀和

```cpp
int n;
int tree[MAXN];

void Tadd(int i, int x) {
    for(; i <= n; i += i & -i) tree[i] += x;
}

int Tsum(int i) {
    int re = 0;
    for(; i; i -= i & -i) re += tree[i];
    return re;
}
```

### ST表
只能维护静态可重复贡献的数据的区间
可重复贡献指的是对于运算 $op$，满足 $x \ op \ x=x$，比如最大值、最小值、最大公因数、最小公倍数、按位与、按位或等等

```cpp
int n, m, f[MAXN][32], lg2[MAXN];

void Init() {
    for(int x = 2; x <= n; x++) lg2[x] = lg2[x>>1] + 1;
    for(int x = 1; x <= lg2[n]; x++)
        for(int y = 1; y + (1<<x) - 1 <= n; y++)
            f[y][x] = max(f[y][x-1], f[y+(1<<(x-1))][x-1]);
}

int Query(int l, int r) {
    int k = lg2[r - l + 1];
    return max(f[l][k], f[r-(1<<k)+1][k]);
}

int main() {
    n = read(); m = read();
    for(int x = 1; x <= n; x++) f[x][0] = read();
    Init();
    while(m--)
    {
        int l, r;
        l = read(); r = read();
        printf("%d\n", Query(l, r));
    }
    return 0;
}
```

### 线段树

```cpp
LL a[MAXN], tree[MAXN<<2], lazy[MAXN<<2];

void PushUp(LL k) {
    tree[k] = tree[k<<1] + tree[k<<1|1];
}

void PushDown(LL l, LL r, LL k) {
    if(lazy[k]) {
        lazy[k<<1] += lazy[k];
        lazy[k<<1|1] += lazy[k];
        LL mid = (l + r) >> 1;
        tree[k<<1] += lazy[k] * (mid - l + 1);
        tree[k<<1|1] += lazy[k] * (r - (mid+1) + 1);
        lazy[k] = 0;
    }
}

void BuildTree(LL l, LL r, LL k) {
    if(l == r) tree[k] = a[l];
    else {
        LL mid = (l + r) >> 1;
        BuildTree(l, mid , k<<1);
        BuildTree(mid + 1, r, k<<1|1);
        PushUp(k);
    }
}

void Update(LL L, LL R, LL l, LL r, LL k, LL p) {
    if(l >= L && r <= R) {
        lazy[k] += p;
        tree[k] += p * (r - l + 1);
    }
    else {
        PushDown(l, r, k);
        LL mid = (l + r) >> 1;
        if(L <= mid) Update(L, R, l, mid, k<<1, p);
        if(R > mid) Update(L, R, mid+1, r, k<<1|1, p);
        PushUp(k);
    }
}

LL Query(LL L, LL R, LL l, LL r, LL k) {
    if(l >= L && r <= R) return tree[k];
    else {
        PushDown(l, r, k);
        LL mid = (l + r) >> 1, re = 0;
        if(L <= mid) re += Query(L, R, l, mid, k<<1);
        if(R > mid) re += Query(L, R, mid+1, r, k<<1|1);
        return re;
    }
}

int main() {
    LL n, m;
    cin >> n >> m;
    for(LL x = 1; x <= n; x++) cin >> a[x];
    BuildTree(1, n, 1);
    //for(LL x = 1; x <= 4 * n; x++) cout << tree[x] << " ";
    //cout << endl;
    while(m--) {
        LL t, l, r, k;
        cin >> t;
        if(t == 1) {
            cin >> l >> r >> k;
            Update(l, r, 1, n, 1, k);
        }
        if(t == 2) {
            cin >> l >> r;
            cout << Query(l, r, 1, n, 1) << endl;
        }
    }
    return 0;
}
```

### 平衡树（AVL）

动态维护一个可重集合 $M$，有以下操作：
1. 向 $M$ 中插入一个数 $x$
2. 从 $M$ 中删除一个数 $x$（若有多个相同的数，应只删除一个）
3. 查询 $M$ 中有多少个数比 $x$ 小，并且将得到的答案加一
4. 查询如果将 $M$ 从小到大排列后，排名位于第 $x$ 位的数
5. 查询 $M$ 中 $x$ 的前驱（前驱定义为小于 $x$，且最大的数）
6. 查询 $M$ 中 $x$ 的后继（后继定义为大于 $x$，且最小的数）

所有操作复杂度均为 $O(\log n)$

```cpp
struct node {
    int key, height, size, cnt;
    node* left;
    node* right;
    node(int k): key(k), height(1), size(1), cnt(1), left(NULL), right(NULL) {}
};

int getSize(node* u) {
    return u ? u->size : 0;
}

int getHeight(node* u) {
    return u ? u->height : 0;
}

int getBalance(node* u) {
    return u ? getHeight(u->left) - getHeight(u->right) : 0;
}

void updateStats(node* u) {
    if(u) {
        u->height = max(getHeight(u->left), getHeight(u->right)) + 1;
        u->size = getSize(u->left) + getSize(u->right) + u->cnt;
    }
}

node* findNode(node* u, int key) {
    node* v = u;
    while(v) {
        if(key < v->key) v = v->left;
        else if(key > v->key) v = v->right;
        else return v;
    }
    return NULL;
}

node* rightRotate(node* u) {
    node* v = u->left;
    node* w = v->right;
    v->right = u;
    u->left = w;
    updateStats(u);
    updateStats(v);
    return v;
}

node* leftRotate(node* u) {
    node* v = u->right;
    node* w = v->left;
    v->left = u;
    u->right = w;
    updateStats(u);
    updateStats(v);
    return v;
}

node* reBalance(node* u) {
    int BL = getBalance(u);
    if(BL > 1 && getBalance(u->left) >= 0) return rightRotate(u); // LL
    if(BL < -1 && getBalance(u->right) <= 0) return leftRotate(u); // RR
    if(BL > 1 && getBalance(u->left) < 0) {
        u->left = leftRotate(u->left);
        return rightRotate(u); // LR
    }
    if(BL < -1 && getBalance(u->right) > 0) {
        u->right = rightRotate(u->right);
        return leftRotate(u); // RL
    }
    return u;
}

node *insert(node* u, int key) {
    if(!u) return new node(key);
    if(key < u->key) u->left = insert(u->left, key);
    else if(key > u->key) u->right = insert(u->right, key);
    else {
        u->cnt++;
        u->size++;
        return u;
    }
    updateStats(u);
    u = reBalance(u);
    return u;
}

node* deleteNode(node* u, int key) {
    if(!u) return NULL;
    if(key < u->key) u->left = deleteNode(u->left, key);
    else if(key > u->key) u->right = deleteNode(u->right, key);
    else {
        if(u->cnt > 1) {
            u->cnt--;
            u->size--;
        } else if(!u->left || !u->right) {
            node* tmp = u->left ? u->left : u->right;
            if(!tmp) {
                tmp = u;
                u = NULL;
            } else {
                *u = *tmp;
            }
            delete tmp;
        } else {
            node* tmp = u->right;
            while(tmp->left) tmp = tmp->left;
            u->key = tmp->key;
            u->cnt = tmp->cnt;
            tmp->cnt = 1;
            u->right = deleteNode(u->right, tmp->key);
        }
    }
    if(!u) return NULL;
    updateStats(u);
    u = reBalance(u);
    return u;
}

int findPre(node* u, int key) {
    int re = -INF;
    while(u) {
        if(key > u->key) {
            re = u->key;
            u = u->right;
        } else u = u->left;
    }
    return re;
}

int findSuc(node* u, int key) {
    int re = INF;
    while(u) {
        if(key < u->key) {
            re = u->key;
            u = u->left;
        } else u = u->right;
    }
    return re;
}

int rkof(node* u, int key) {
    if(!u) return 1;
    if(key < u->key) return rkof(u->left, key);
    if(key > u->key) return getSize(u->left) + u->cnt + rkof(u->right, key);
    return getSize(u->left) + 1;
}

int rk(node* u, int k) {
    if(!u) return 0;
    if(k <= getSize(u->left)) return rk(u->left, k);
    if(k <= getSize(u->left) + u->cnt) return u->key;
    return rk(u->right, k - getSize(u->left) - u->cnt);
}

void printTree(node* u) {
    if(u->left) {
        cout << u->key << " " << u->left->key << endl;
        printTree(u->left);
    }
    if(u->right) {
        cout << u->key << " " << u->right->key << endl;
        printTree(u->right);
    }
}

int main() {
    node* root = NULL;
    int T;
    cin >> T;
    while(T--) {
        int op, x;
        cin >> op >> x;
        if(op == 1) {
            root = insert(root, x);
        } else if(op == 2) {
            root = deleteNode(root, x);
        } else if(op == 3) {
            cout << rkof(root, x) << endl;
        } else if(op == 4) {
            cout << rk(root, x) << endl;
        } else if(op == 5) {
            cout << findPre(root, x) << endl;
        } else if(op == 6) {
            cout << findSuc(root, x) << endl;
        }
    }
    return 0;
}
```

## 字符串

### 哈希函数

多项式哈希，可以将字符串映射到一个数字上，但要**小心哈希冲突**
$$
f(s)=\sum_{i=1}^{l} {s[i] \times b^{l-i}} (\text{mod}\ M)
$$

```cpp
#define MOD 1000007 //可以根据数据范围调整
int getHash(string s, int BASE) {
	int l = s.size(), re = 0;
	for(int x = 0; x < l; x++) re = (re*BASE+int(s[x])) % MOD;
	return re;
}
```

### KMP

经典字符串查找算法，时间复杂度 $O(l_1 + l_2)$，即两字符串长度之和

```cpp
//前缀函数
vector <int> prefix(string s) {
    int n = s.length();
    vector <int> pi(n);
    for(int x = 1; x < n; x++) {
        int y = pi[x-1];
        while(y > 0 && s[x] != s[y]) y = pi[y-1];
        if(s[x] == s[y]) y++;
        pi[x] = y;
    }
    return pi;
}

// 返回存在 vector 里的下标
vector <int> KMP(string s1, string s2) {
    string cur = s2 + '#' + s1;
    int l1 = s1.size(), l2 = s2.size();
    vector <int> v;
    vector <int> lps = prefix(cur);
    for(int x = l2+1; x <= l1+l2; x++)
        if(lps[x] == l2) v.push_back(x - 2*l2);
    return v;
}
```

### Trie字典树

简单方便的字典树，插入和查询的复杂度都是 $O(L)$，其中 $L$ 表示单词的长度

```cpp
int son[MAXN][26], cnt[MAXN], idx;

void insert(string s) {
	int p = 0; //指向当前节点
	for(int x = 0; x < s.length(); x++) {
		int u = s[x] - 'a';
		if(!son[p][u]) son[p][u] = ++idx;
		p = son[p][u];
	}
	cnt[p]++;
}

// 返回查找到的数量
int query(string s) {
	int p = 0;
	for(int x = 0; x < s.length(); x++) {
		int u = s[x] - 'a';
		if(!son[p][u]) return 0;
		p = son[p][u];
	}
	return cnt[p];
}
```

## 其他

### 运行批处理

`run.bash`
```bash
#!/bin/bash
g++ -std=c++17 -O2 -Wall "$1" -o main
./main < in.txt > out.txt
```

### 对拍批处理

`cmp.bash`
```bash
#!/bin/bash
for ((i=1; ; i++)); do
    ./gen > input.txt           # generator
    ./code < input.txt > output1.txt  # your code
    ./std < input.txt > output2.txt   # std code
    if diff output1.txt output2.txt; then  # compare
        echo "Test $i: Accepted"
    else
        echo "Test $i: Wrong Answer"
        echo "Input:"
        cat input.txt
        echo "Your Output:"
        cat output1.txt
        echo "Standard Output:"
        cat output2.txt
        break
    fi
done
```
