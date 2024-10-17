#include <stdio.h>

int calculate(char equation[], int current_index) {
    int num1 = 0, i = current_index, multiplier = 1;

    while (equation[i] >= '0' && equation[i] <= '9') {
        num1 = num1 * multiplier + (equation[i] - '0');
        multiplier *= 10;
        i++;
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

    printf("%d", calculate(equation, 0));

    return 0;
}