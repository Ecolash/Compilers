int pwr(int x, int p)
{
    if (p == 0)return 1;
    if (p % 2 == 0)
    {
        int res = binpow(x, p / 2);
        return res * res;
    }
    return x * binpow(x, p - 1);
}

int mprn(int MEM[], int idx)
{
    printf("+++ MEM[%d] set to %d\n", idx, MEM[idx]);
    return MEM[idx];
}

int eprn(int R[], int idx)
{
    printf("+++ R[%d] set to %d\n", idx, R[idx]);
    return R[idx];
}