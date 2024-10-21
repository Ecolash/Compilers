void customSwap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void customSort(int *data, int length)
{
    int i, j, minIndex;
    i = 0;
    j = 0;
    for (i = 0; i < length - 1; i++)
    {
        minIndex = i;
        for (j = i + 1; j < length; j++)
        {
            if (data[j] < data[minIndex])
            {
                minIndex = j;
            }
        }
        customSwap(&data[minIndex], &data[i]);
    }
    return;
}

int main()
{
    int numbers[7];
    numbers[0] = (int)1.6; // Type casting float to int
    numbers[1] = -4;
    numbers[2] = 7;
    numbers[3] = (int)8.9;
    numbers[4] = -342;
    numbers[5] = (int)0.6;
    numbers[6] = 100;
    int length = 7;
    customSort(numbers, length);

    return 0;
}