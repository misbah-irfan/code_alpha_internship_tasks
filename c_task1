#include <stdio.h>

int main(void) {
    char op;
    double a, b;

    printf("=== Simple Calculator ===\n");
    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &op);

    printf("Enter two numbers: ");
    if (scanf("%lf %lf", &a, &b) != 2) {
        printf("Invalid input.\n");
        return 1;
    }

    switch (op) {
        case '+':
            printf("%.2f + %.2f = %.2f\n", a, b, a + b);
            break;
        case '-':
            printf("%.2f - %.2f = %.2f\n", a, b, a - b);
            break;
        case '*':
            printf("%.2f * %.2f = %.2f\n", a, b, a * b);
            break;
        case '/':
            if (b == 0)
                printf("Error: Division by zero is not allowed.\n");
            else
                printf("%.2f / %.2f = %.2f\n", a, b, a / b);
            break;
        default:
            printf("Error: Invalid operator '%c'.\n", op);
    }
    return 0;
}
