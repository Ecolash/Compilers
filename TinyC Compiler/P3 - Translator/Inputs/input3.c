float pi = 3.14159265;
char grade;	
int number1, number2, result1, result2, quotient, remainder;
int myArray[5];                   // 1D array declaration
float matrix[3][3];               // 2D array declaration
int age = 30, *ptr, temperature;   // pointer declaration

void printMessage (int num, float val) {
    val = (float)(num + 42);
    return;
}

int main () {
    // Variable Declaration
    int apples = 10;
    int bananas = 3;
    char initial = 'M', grade = 'A';  // character definitions

    // Arithmetic Operations
    number1 = apples + bananas;
    number2 = apples - bananas;
    result1 = apples * bananas;
    result2 = apples / bananas;
    quotient = apples % bananas;
    remainder = apples & bananas;
    grade = grade | 'B';

    bananas = number1 << 2;
    apples = number2 >> 1;

    // Call a function
    printMessage(apples, pi);

    return 0;
}