#include "../Stack/Stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

int isOperator(char str[]) {
    if (strlen(str) != 1)
        return 0;
    if (str[0] == '+' || str[0] == '-' || str[0] == '*' || str[0] == '/') {
        return 1;
    }
    return 0;
}

int executeOperation(char operation, int n1, int n2)
{
    switch (operation) {
        case '+':
            return n1 + n2;
        case '-':
            return n1 - n2;
        case '*':
            return n1 * n2;
        case '/':
            return n1 / n2;
    }
    return 0;
}

int main (void) {

    char buf[MAX], lastChar;
    Stack* s = NULL;
    while (1) {
        scanf("%s%c", buf ,&lastChar);

        if (!isOperator(buf)) {
            s = push(s, atoi(buf));
        } else {
            if (!isEmpty(s) && !isEmpty(s->next)) {
                int ans = executeOperation(buf[0], s->next->data,s->data);
                s = pop(s);
                s = pop(s);
                s = push(s,ans);
            }
        }

        if (lastChar == '\n')
            break;
    }

    printf("Total = %d\n", s->data);
    return 0;
}
