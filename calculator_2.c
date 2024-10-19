#include <stdio.h>

struct token {
    char type;
    union {
        double num;
        char opr;
    };
};

int tokenize(char equation[], struct token tokens[]) {
    int i = 0, token_count = 0, multiplier = 10;
    double number = 0, divider = 10, temp;

    while (i < 256 && equation[i] != '\0') {
        if (equation[i] == ' ') {
            i++;
            continue;
        }

        if (equation[i] >= '0' && equation[i] <= '9') {
            while (equation[i] >= '0' && equation[i] <= '9') {
                number = number * multiplier + equation[i] - '0';
                i++;
            }
            if (i < 256 && (equation[i] == '.' || equation[i] == ',')) {
                i++;
                while (equation[i] >= '0' && equation[i] <= '9') {
                    temp = equation[i] - '0';
                    number += temp / divider;
                    divider *= 10;
                    i++;
                }
                divider = 10;
            }
            tokens[token_count].type = 'd';
            tokens[token_count].num = number;

            number = 0;
        } else {
            tokens[token_count].type = 'c';
            tokens[token_count].opr = equation[i];
            i++;
        }
        token_count++;
    }
    return token_count;
}

int get_precedence(char token) {
    switch (token) {
    case '+':
        return 1;
        break;
    case '-':
        return 1;
        break;
    case '*':
        return 2;
        break;
    case '/':
        return 2;
        break;
    default:
        return 0;
        break;
    }
}

int infix_to_postfix(struct token tokens[], int token_count, struct token postfix[256]) {
    struct token output[256];
    char operators[256];
    int count_1 = 0, count_2 = 0, i = 0;

    for (i = 0; i < token_count; i++) {
        switch (tokens[i].type) {
        case 'd':
            output[count_1].type = 'd';
            output[count_1].num = tokens[i].num;
            count_1++;
            break;

        case 'c':
            switch (tokens[i].opr) {
            case '(':
                operators[count_2] = '(';
                count_2++;
                break;
            case ')':
                count_2--;
                while (operators[count_2] != '(' && count_2 >= 0) {
                    output[count_1].type = 'c';
                    output[count_1].opr = operators[count_2];
                    count_1++;
                    count_2--;
                }
                break;
            default:
                while (count_2 > 0 && get_precedence(operators[count_2 - 1]) >= get_precedence(tokens[i].opr)) {
                    output[count_1].type = 'c';
                    output[count_1].opr = operators[count_2 - 1];
                    count_1++;
                    count_2--;
                }
                operators[count_2] = tokens[i].opr;
                count_2++;
                break;
            }
            break;

        default:
            break;
        }
    }
    while (count_2 > 0) {
        count_2--;
        output[count_1].type = 'c';
        output[count_1].opr = operators[count_2];
        count_1++;
    }
    for (i = 0; i < count_1; i++) {
        postfix[i] = output[i];
    }
    return count_1;
}

double evaluate_postfix(struct token postfix[256], int postfix_size) {
    double result = 0, stack[postfix_size];
    int i = 0, count = 0;

    while (i < postfix_size) {
        switch (postfix[i].type) {
        case 'd':
            stack[count] = postfix[i].num;
            count++;
            break;
        case 'c':
            switch (postfix[i].opr) {
            case '+':
                result = stack[count - 2] + stack[count - 1];
                stack[count - 2] = result;
                count -= 1;
                break;
            case '-':
                result = stack[count - 2] - stack[count - 1];
                stack[count - 2] = result;
                count -= 1;
                break;
            case '*':
                result = stack[count - 2] * stack[count - 1];
                stack[count - 2] = result;
                count -= 1;
                break;
            case '/':
                result = stack[count - 2] / stack[count - 1];
                stack[count - 2] = result;
                count -= 1;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        i++;
    }
    return stack[0];
}

double evaluate_expression(char expression[256]) {
    struct token tokens[256], postfix[256];
    int token_count, postfix_size;

    token_count = tokenize(expression, tokens);
    postfix_size = infix_to_postfix(tokens, token_count, postfix);

    return evaluate_postfix(postfix, postfix_size);
}

int main() {
    char expression[256];

    fgets(expression, 256, stdin);
    printf("%g", evaluate_expression(expression));

    return 0;
}