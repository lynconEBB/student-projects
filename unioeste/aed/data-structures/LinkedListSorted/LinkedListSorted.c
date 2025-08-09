#include "LinkedListSorted.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int isEmpty(List *l) {
    return (l == NULL);
}

void aux_printElements(List* l)
{
    if (!isEmpty(l)) {
        printf("%d ", l->data);
        aux_printElements(l->next);
    }
}

void printElements(List* l)
{
    printf("[ ");
    aux_printElements(l);
    printf("]\n");
}

List* insert(List* l, int data)
{
    if (isEmpty(l) || l->data > data) {
        List* aux = malloc(sizeof(List));
        aux->data = data;
        aux->next = NULL;
        if (!isEmpty(l))
            aux->next = l;
        return aux;
    }

    l->next = insert(l->next,data);
    return l;
}

List* removeElement(List* l, int data)
{
    if (isEmpty(l)) {
        return l;
    }
    if (l->data == data) {
        List* next = l->next;
        free(l);
        if (!isEmpty(next))
            next = removeElement(next, data);
        return next;
    } else {
        l->next = removeElement(l->next, data);
        return l;
    }
}

List* merge(List* l1, List* l2)
{
    if (isEmpty(l1) && isEmpty(l2)) {
        return NULL;
    }
    List *aux = malloc(sizeof(List));

    if (isEmpty(l1)) {
        aux->data = l2->data;
        aux->next = merge(l1,l2->next);
        return aux;
    }
    if (isEmpty(l2)) {
        aux->data = l1->data;
        aux->next = merge(l1->next,l2);
        return aux;
    }

    if (l1->data <= l2->data) {
        aux->data = l1->data;
        aux->next = merge(l1->next, l2);
    } else {
        aux->data = l2->data;
        aux->next = merge(l1, l2->next);
    }
    return aux;
}


