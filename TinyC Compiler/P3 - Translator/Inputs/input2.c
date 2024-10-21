
int arraySize = 3;

void generateSubmatrix(int matrix[arraySize][arraySize], int submatrix[arraySize][arraySize], int row, int col, int size) {
    int i = 0, j = 0, subRow = 0, subCol = 0;

    for (subRow = 0; subRow < size; subRow++) { // Nested for loop
        for (subCol = 0; subCol < size; subCol++) {
            if (subRow != row && subCol != col) {
                submatrix[i][j++] = matrix[subRow][subCol];
            }
            if (j == size - 1) {
                j = 0;
                i++;
            }
        }
    }
    return;
}

int main() {
    int numbers[4]; // 1D integer array
    int index = 0;

    while (index < 4) { // while loop
        numbers[index++] = index;
    }

    int total = 0;
    int arraySize = 4;
    index = 0;
    do { // do-while loop
        total = total + numbers[index++];
    } while (index < arraySize);

    int matrix[arraySize][arraySize];

    int row = 0, col = 0, value = 10;

    for (row = 0; row < arraySize; row++) {
        for (col = 0; col < arraySize; col++) {
            matrix[row][col] = value++;
        }
    }

    int submatrix[arraySize][arraySize];
    generateSubmatrix(matrix, submatrix, 0, 0, arraySize);

    return 0;
}