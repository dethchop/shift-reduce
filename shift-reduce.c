#include <stdio.h>
#include <string.h>

char stack[50], input[50];
int top = -1, i = 0;

void reduce()
{
    if(top >= 0 && stack[top] == 'i')
    {
        stack[top] = 'E';
        printf("Reduce i to E\n");
    }
    else if(top >= 2 &&
            stack[top - 2] == 'E' &&
            stack[top - 1] == '+' &&
            stack[top] == 'E')
    {
        top = top - 2;
        stack[top] = 'E';
        printf("Reduce E+E to E\n");
    }
    else if(top >= 2 &&
            stack[top - 2] == 'E' &&
            stack[top - 1] == '*' &&
            stack[top] == 'E')
    {
        top = top - 2;
        stack[top] = 'E';
        printf("Reduce E*E to E\n");
    }
}

int main()
{
    printf("Enter expression using i: ");
    scanf("%s", input);

    while(input[i] != '\0')
    {
        stack[++top] = input[i++];
        printf("Shift %c\n", stack[top]);
        reduce();
    }

    while(top > 0)
    {
        int oldtop = top;
        reduce();
        if(oldtop == top)
            break;
    }

    if(top == 0 && stack[0] == 'E')
        printf("Accepted\n");
    else
        printf("Rejected\n");

    return 0;
}
