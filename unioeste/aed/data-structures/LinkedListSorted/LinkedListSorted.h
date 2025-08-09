#ifndef LISTA1_LINKEDLISTSORTED_H
#define LISTA1_LINKEDLISTSORTED_H

/**
 * Estrutura de nó para lista encadeada
 */
typedef struct node {
    int data;
    struct node* next;
} List;

int isEmpty(List* l);

List* insert(List* l, int data);

List* removeElement(List* l, int data);

void printElements(List* s);

List* merge(List* l1, List* l2);


#endif