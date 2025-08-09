#ifndef LISTA1_LINKEDLISTRECURSIVE_H
#define LISTA1_LINKEDLISTRECURSIVE_H

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

List* append(List* l1, List* l2);

List* recursive_append(List* l1, List* l2);

int count_occurrences(List* l, int data);

int recursive_count_occurrences(List *l, int data);

List* remove_duplicates(List* l);

int recursive_count_even(List* l);

#endif