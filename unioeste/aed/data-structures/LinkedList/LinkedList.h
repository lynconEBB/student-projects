#ifndef LISTA1_LINKEDLIST_H
#define LISTA1_LINKEDLIST_H

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

List* invert(List* l);

List* concat(List* l1, List* l2);

List* mergeShuffle(List* l1, List* l2);

int somar_intervalo(List* l, int a, int b);

List* filtrar(List* l, int n);

void merge_sort(List** l);
#endif