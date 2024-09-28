// TEST FILE FOR TESTING TINY-C YACC PARSER

/* ======================================================
    TEST FILE : GROUP - 54
    -------------------------
    TUHIN MONDAL (22CS10087)
    DIGANTA MANDAL (22CS30062)
    ----------------------------
*/

int x, *y, z = 10, w = 0;
char x1, *y1, z1, w1 = 'c';
float a = 10.5, b = 3.4, *c;
void *c;

int fnc1(float a, int b, char c)
{
    int d = a + b - b / 2;
    printf("c = %c, d = %d\n", c, d);
    return d;
}

int main()
{
    int a = 10, b = 20, c = 30;
    int d = fnc1(a, b, 'a');
    printf("a = %d, b = %d, d = %d\n", a, b, d);

    int arr[5][6][7];
    for (int i = 0; i < 5; i++)
    for (int j = 0; j < 6; j++)
    {
        for (int k = 0; k < 7; k++)
        {
            arr[i][j][k] = i + j + k;
            printf("%d ", arr[i][j][k]);
        }
    }

    float arr2[] = {0.5, 0.8, 7.2, 5.1, 3.3};
    for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4 - i; j++)
    if (arr2[j] > arr2[j + 1])
    {
        float temp = arr2[j];
        arr2[j] = arr2[j + 1];
        arr2[j + 1] = temp;
    }

    char *x = "Hello World!", temp;
    int l = 0, r = -1;
    while (x[r + 1] != '\0') r++;
    while (l < r)
    {
        temp = x[l];
        x[l++] = x[r];
        x[r--] = temp;
    }

    a++, b--; 
    b = ++a, b = a++; 
    a = b--, a = --b;
    a = (b & 1) | 1; 
    a = a * c / b + b % 3 + 2; 
    c = (c * d / 5 % 1) << 2 >> z; 
    c &= 2, c |= 1, c ^= 0;
    b = a && c, c = b || (c == r) && !a;

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

    char str1[100] = "Hello, ", str2[] = "World!";
    int i = 0, j = 0;
    while (str1[i]) i++;
    while (str2[j]) str1[i++] = str2[j++];
    str1[i] = '\0';
    printf("%s\n", str1);
    return 0;
}

