int add(int x, int y) { return x + y; }
int mul(int x, int y, int z) { return x * y * z;}
int sub(int x, int y, int z, int w) { return x - y - z - w; }
int divmod(int x, int y, int z) { return (x / y) % z; }


int powr(int base, int exp, int mult)
{
    if (exp == 0) return mult;
    int ans = exp % 2 == 0 ? mult : mult * base;
    return powr(base, exp / 2, ans);
}

int fact(int n, int d)
{
    if (n == 0) return d;
    return fact(n - 1, d * n);
}

int fib(int n, int a, int b)
{
    if (n == 0) return a;
    if (n == 1) return b;
    return fib(n - 1, a, b) + fib(n - 2, a, b);
}

int comp(int a, int b, int c)
{
    int r = add(a, b) * mul(b, c, add(a, c));
    r -= sub(r, a, b, c);
    r += divmod(a, b, c);
    return r;
}

int rec(int x, int y, int z, int d)
{
    if (d == 0) return x + y + z;
    int t1 = add(x, rec(y, z, x + y, d - 1));
    int t2 = mul(y, x, comp(z, x, y));
    return sub(t1, t2, rec(x, y, z, d - 1), d);
}

int nested(int a, int b, int c) {return powr(a, 3, 1) + fact(b, 1) + sum_sq(a, b, c) - fib(5, a, b);}
int sum_sq(int x, int y, int z) {return add(x * x, y * y) + z * z; }

int max4(int a, int b, int c, int d)
{
    int max_ab = a > b ? a : b;
    int max_cd = c > d ? c : d;
    return max_ab > max_cd ? max_ab : max_cd;
}

int min4(int a, int b, int c, int d)
{
    int min_ab = a < b ? a : b;
    int min_cd = c < d ? c : d;
    return min_ab < min_cd ? min_ab : min_cd;
}

int deep_op(int a, int b, int c, int d)
{
    int res = max4(comp(a, b, c), nested(b, c, a), sum_sq(a, d, b), fib(d, a, c));
    res += min4(powr(b, 2, 1), fact(a, 1), divmod(d, b, c), rec(c, a, b, 2));
    return res;
}

int ultimate(int a, int b, int c, int d, int depth)
{
    if (depth == 0) return a + b + c + d;
    int part1 = deep_op(a, b, c, d);
    int part2 = ultimate(b, c, d, a, depth - 1);
    int part3 = add(part1, comp(c, part2, b));
    int part4 = mul(ultimate(a, b, c, d, depth - 1), deep_op(c, d, a, b), fact(depth, 1));
    return sub(part3, part4, deep_op(a, b, c, d), depth);
}

int main()
{
    int a = 3, b = 5, c = 7, d = 2;
    int res1 = ultimate(a, b, c, d, 3);
    int res2 = deep_op(a, b, c, d);
    int res3 = nested(a, b, c);
    int res4 = max4(res1, res2, res3, sub(res1, res2, res3, d));
    int res5 = min4(res1, res2, res3, powr(res4, 2, 1));
    int ans = add(res1, mul(res2, res3, res4)) - sub(res5, res1, res2, res3);
    return ans;
}
