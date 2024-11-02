int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) { return (a * b) / gcd(a, b);}

int factorial(int n) 
{
    if (n < 0) return -1;
    if (n == 1 || n == 0) return 1;
    return n * factorial(n - 1);
}

int main() {
    int n1 = 10, n2 = 20, n3, n4;
    float f1 = 2.5, f2, f3 = 5.0;
    
    n1 = gcd(36, 60);
    n2 = lcm(36, lcm(60, 72));
    n3 = factorial(gcd(n1, n2));
    n4 = factorial(gcd(lcm(5, 10), gcd(10, 15)));

    n1 = ((n2 << 2) + n3) >> n1;
    n2 = n1 >> 2;
    n3 = n1 * n2 / (int)f3;
    n1 = n2 ^ n3;
    n2 = (n1 & n2) | n3;
    n3 = n1 & (n2 | n3);
    return 0;
}
