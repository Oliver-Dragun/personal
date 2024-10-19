#include <stdio.h>

double calculate(char equation[], int current_index) {
    int i = current_index, multiplier = 1;
    double num1 = 0, temp = 0, divider = 10;

    while (equation[i] >= '0' && equation[i] <= '9') {
        num1 = num1 * multiplier + (equation[i] - '0');
        multiplier *= 10;
        i++;
    }

    if (equation[i] == '.' || equation[i] == ',') {
        i++;
        while (equation[i] >= '0' && equation[i] <= '9') {
            temp = (equation[i] - '0');
            num1 = num1 + temp / divider;
            divider *= 10;
            i++;
        }
    }

    if (equation[i] == '\0') {
        return num1;
    }

    switch (equation[i]) {
    case '+':
        return num1 + calculate(equation, i + 1);
        break;
    case '-':
        return num1 - calculate(equation, i + 1);
        break;
    case '*':
        return num1 * calculate(equation, i + 1);
        break;
    case '/':
        return num1 / calculate(equation, i + 1);
        break;
    default:
        return 0;
        break;
    }
}

int main() {
    char equation[256];

    scanf("%s", &equation);

    printf("%g", calculate(equation, 0));

    return 0;
}