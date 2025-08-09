#ifndef LISTAS_STACK_H
#define LISTAS_STACK_H

typedef struct node{
    int data;
    struct node* next;
} Stack;

int isEmpty(Stack* s);

Stack* push(Stack* s, int data);

Stack* pop(Stack* s);

int top(Stack* s);

void printElements(Stack* s);

#endif
