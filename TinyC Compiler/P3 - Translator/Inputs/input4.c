float power(float base, int exponent) {
    if (exponent == 0) {
        return 1.0;
    } else if (exponent > 0) {
        return base * power(base, exponent - 1);
    } else {
        // Negative exponent
        return 1.0 / (base * power(base, -exponent - 1));
    }
}

int main() {
    int num;
    float base;
    int exponent;
    float result;

    num = 5;
    base = 2.0;
    exponent = 3;
    result = 0.0;

    if (exponent < 0) {
        exponent = -exponent;
    } else {
        result = power(base, exponent);
    }

    if (num % 2 == 0) {
        if (num > 0) {
            num += 1;
        } else if (num < 0) {
            num -= 1;
        } else {
            num = 0;
        }
    } else {
        if (num > 0) {
            num += 2;
        } else if (num < 0) {
            num -= 2;
        } else {
            num = 0;
        }
    }

    return 0;
}