// TEST FILE FOR TESTING TINY-C YACC PARSER

/* ============================================================
    TEST FILE 3.0 
    This is a test file for testing the tiny-c yacc parser.
   ============================================================
*/

int x, *y, z = 10, w = 0;
char x1, *y1, z1, w1 = 'c';
float a = 10.5, b = 3.4, *c;
void *c;

void fnc0(int arr[][6][7], int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 6; j++)
        for (int k = 0; k < 7; ++k)
        {
            arr[i][j][k] = i + j + k;
            printf("%d ", arr[i][j][k]);
        }
    }
}

inline int fnc1(char *p1, const int p2, volatile int p3, int *restrict p4,...)
{
    auto int a;
    register int b;
    extern int exvar;
    static int d = 4;
    return d;
}

const char *fnc2(int b[const static 8], int c[static 9], int d[], int e[const * ]);

char* reverse(char *str, int n);

int fib(int n)
{
    int x = (n <= 1) ? n : fib(n - 1) + fib(n - 2);
    printf("Fib(%d) = %d", n, x);
    return x;
}

int fnc4(float a, int b, char c)
{
    int d = a + b - b / 2;
    printf("c = %c, d = %d\n", c, d);
    return d;
}

void sort(float arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - i - 1; j++)
    if (arr[j] > arr[j + 1])
    {
        float temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
    }
}

int main()
{
    int a = 10, b = 20, c = 30, n;
    int d = fnc4(a, b, 'a');
    int e = fib(10);
    foo1(a, b, c, d, e, 1, 5.0, 'a', "Happy");
    ptr1.a = 6, ptr1->b = 'd';
    node->left->left->right->val = 0;

    printf("%d = %d + %d\n", fib(9), fib(8), fib(7));
    printf("a = %d, b = %d, d = %d\n", a, b, d);
    for (;;)
        for (int i;;)
            for (int i = 0, j = 1; i != j; i++)
            {
                if (j == 1) continue;
                else if (j == 2) j = 6;

                if (j == 6) printf("Hi!");
                if (j == 7) break;
                else goto end;
            }

    int arr[4][6][7];
    fnc0(arr, 4);

    float arr2[] = {0.5, 0.8, 7.2, 5.1, 3.3};
    sort(arr2, 5);


    char *x = "Hello World!", temp;
    temp = reverse(x, 11);
    
    a = (a * c / b) + (b % 3) + 2;
    c = ((c * d / 5) % 1) << 2 >> z;
    c &= 2, c |= 1, c ^= 0;

    b = ++a, b = a++; 
    a = b--, a = --b;
    a = (b & 1) | 1; 
    b = a && c, c = b || (c == 5) && !a;

    if (a > 5) if (b > 10)
        if (c < 3) x = 1;
        else y = 2;
    else if (d == 7) z = 3;
    else w = 4;

    if (a != 0) c = 5;
    else if (b == 0) c = 6;
    else if (c == 0) c = 7;
    else c = 8;

    int grade = 10;
    switch(grade) 
    {
        case 10: printf("EX"); break;
        case 9: printf("A"); break;
        case 8: printf("B"); break;
        default: printf("P");
    }

    RND_LOC:
        if (x < y) n = (z == 0) ? 1 : z - 1;
        else if (x > y) 
        {
            if (z >= w) w++;
            else if (z <= w) z++;
        }

    while (z--) goto RND_LOC;

    char str1[100] = "Hello, ", str2[] = "World!";
    int i = 0, j = 0;
    while (str1[i]) i++;
    while (str2[j]) str1[i++] = str2[j++];
    str1[i] = '\0';
    printf("%s\n", str1);

    end:
    return 0;
}

char* reverse(char *x, int len)
{
    int l = 0, r = -1;
    char *temp;
    while (x[r + 1] != '\0') r++;
    while (l < r)
    {
        temp = x[l];
        x[l++] = x[r];
        x[r--] = temp;
    }
    return temp;
}