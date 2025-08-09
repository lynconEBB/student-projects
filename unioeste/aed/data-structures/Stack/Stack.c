#include "Stack.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int isEmpty(Stack* s)
{
    return (s == NULL);
}

void printElements(Stack *s)
{
    printf("[ ");
    while (s != NULL) {
        printf("%d ", s->data);
        s = s->next;
    }
    printf("]\n");
}

Stack* push(Stack* s, int data)
{
    Stack* head = malloc(sizeof(Stack));
    head->data = data;
    head->next = s;
    return head;
}

Stack *pop(Stack *s)
{
    if (!isEmpty(s)) {
        Stack* toBeDeleted = s;
        s = s->next;
        free(toBeDeleted);
    }
    return s;
}


int top(Stack *s) {
    if (!isEmpty(s))
        return s->data;

    printf("Lista vazia!\n");
    return 0;
}