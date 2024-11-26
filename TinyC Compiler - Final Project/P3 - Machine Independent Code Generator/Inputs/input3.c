
const int X = 3;
const int Y = 4;
const int Z = 5;

void solve(int dp[X][Y][Z])
{
    for (int i = 0; i < X; ++i)
    for (int j = 0; j < Y; ++j)
    {
        for (int k = 0; k < Z; ++k)
        {
            if (i == 0 || j == 0 || k == 0) dp[i][j][k] = 1;
            else
            {
                int a, b, c;
                a = dp[i - 1][j][k];
                b = dp[i][j - 1][k];
                c = dp[i][j][k - 1];
                dp[i][j][k] = a + b + c;
            }
        }
    }
}


int main()
{
    int dp[X][Y][Z] = {0};
    solve(dp);
    return 0;
}
