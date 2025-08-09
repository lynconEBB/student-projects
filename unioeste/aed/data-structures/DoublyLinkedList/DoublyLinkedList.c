#include "DoublyLinkedList.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int isEmpty(List *l) {
    return (l == NULL);
}

List* insert(List* l, int data)
{
    List* aux = malloc(sizeof(List));
    aux->data = data;
    aux->prev = NULL;
    aux->next = l;

    if (!isEmpty(l)) {
        l->prev = aux;
    }

    return aux;
}

void printElements(List* l)
{
    printf("[ ");
    while (!isEmpty( l)) {
        printf("%d ", l->data);
        l = l->next;
    }
    printf("]\n");
}

List* removeElement(List* l, int data)
{
    List* head = l;
    while (!isEmpty(l) && l->data != data) {
        l = l->next;
    }
    if (l->next != NULL)
        l->next->prev = l->prev;
    if (l->prev != NULL)
        l->prev->next = l->next;
    else
        head = head->next;

    free(l);

    return head;
}

List* invert(List* l)
{
    List* prev = NULL;
    while (!isEmpty(l)) {
        List* curr = malloc(sizeof(List));
        curr->data = l->data;
        curr->next = prev;
        if (prev) {
            prev->prev = curr;
        }
        prev = curr;
        l = l->next;
    }
    prev->prev = NULL;
    return prev;
}

void aux_append(List** prev, List** source, List** head )
{
    List* curr = malloc(sizeof(List));
    curr->data = (*source)->data;
    curr->prev = (*prev);
    curr->next = NULL;

    if ((*prev) != NULL)
        (*prev)->next = curr;

    (*prev) = curr;
    (*source) = (*source)->next;

    if ((*head) == NULL)
        (*head) = curr;
}

List* concat(List* l1, List* l2)
{
    List* head = NULL;
    List* prev = NULL;

    while (!isEmpty(l1)) {
        aux_append(&prev, &l1, &head);
    }

    while (!isEmpty(l2)) {
        aux_append(&prev, &l2, &head);
    }

    return head;
}

List* mergeShuffle(List* l1, List* l2)
{
    List* head = NULL;
    List* prev = NULL;

    while (!isEmpty(l1) || !isEmpty(l2)) {
        if (!isEmpty(l1))
            aux_append(&prev, &l1, &head);
        if (!isEmpty(l2))
            aux_append(&prev, &l2, &head);
    }
    return head;
}

List *remover_anterior(List *l, int data_ref) {
    List* curr = l;
    while (!isEmpty(curr)) {
        if (curr->data == data_ref) {
            if (isEmpty(curr->prev))
                return l;

            List* rmv = curr->prev;
            if (isEmpty(rmv->prev))
                l = curr;
            else
                rmv->prev->next = curr;

            curr->prev = rmv->prev;
            free(rmv);
            return l;
        }
        curr = curr->next;
    }
    return l;
}



