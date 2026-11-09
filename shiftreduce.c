#include <stdio.h>

#define MAX 100

char input[MAX], stack[MAX];
int top = -1, ip = 0, len = 0;

int prec(char c)
{
    if (c == '*') return 2;
    if (c == '+') return 1;
    return 0;
}

void show(char *action)
{
    int i;

    printf("%-15s %-15s %s\n", "", "", "");

    for (i = 0; i <= top; i++)
        printf("%c", stack[i]);

    printf("\t\t");

    for (i = ip; i < len; i++)
        printf("%c", input[i]);

    printf("$\t\t%s\n", action);
}

int reduce()
{
    char look = (ip < len) ? input[ip] : '$';

    if (top >= 0 && stack[top] == 'i') {
        stack[top] = 'E';
        show("REDUCE E->i");
        return 1;
    }

    if (top >= 2 && stack[top-2] == '(' &&
        stack[top-1] == 'E' && stack[top] == ')') {
        top -= 2;
        stack[top] = 'E';
        show("REDUCE E->(E)");
        return 1;
    }

    if (top >= 2 && stack[top-2] == 'E' &&
        (stack[top-1] == '+' || stack[top-1] == '*') &&
        stack[top] == 'E') {

        char op = stack[top-1];

        if (look == '$' || look == ')' ||
            (look != '(' && prec(op) >= prec(look))) {

            top -= 2;
            stack[top] = 'E';

            printf("");
            show(op == '+' ? "REDUCE E->E+E" : "REDUCE E->E*E");
            return 1;
        }
    }

    return 0;
}

int main()
{
    char str[MAX];

    printf("Grammar: E -> E+E | E*E | (E) | i\n");
    printf("Enter input string: ");
    scanf("%99s", str);

    for (int i = 0; str[i]; i++) {
        if (str[i] == 'i') {
            input[len++] = 'i';
        }
        else if (str[i] == '+' || str[i] == '*' ||
                 str[i] == '(' || str[i] == ')') {
            input[len++] = str[i];
        }
        else {
            printf("Invalid symbol: %c\n", str[i]);
            return 1;
        }
    }

    printf("\nSTACK\t\tINPUT\t\tACTION\n");
    printf("------------------------------------------\n");

    show("Initial");

    while (ip < len) {
        while (reduce());

        stack[++top] = input[ip++];
        show("SHIFT");
    }

    while (reduce());

    printf("------------------------------------------\n");

    if (top == 0 && stack[0] == 'E')
        printf("String ACCEPTED\n");
    else
        printf("String REJECTED\n");

    return 0;
}

