#ifndef LISTAS_DOUBLYLINKEDLIST_H
#define LISTAS_DOUBLYLINKEDLIST_H

/**
 * Estrutura de nó para lista encadeada
 */
typedef struct node {
    int data;
    struct node* next;
    struct node* prev;
} List;

int isEmpty(List* l);

List* insert(List* l, int data);

List* removeElement(List* l, int data);

void printElements(List* s);

List* invert(List* l);

List* concat(List* l1, List* l2);

List* mergeShuffle(List* l1, List* l2);

List* remover_anterior(List* l, int data_ref);
#endif
