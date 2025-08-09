#include "LinkedListTailHead.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

List *newList()
{
    List* aux = malloc(sizeof(List));
    aux->head = NULL;
    aux->tail = NULL;
    return aux;
}

int isEmpty(List *l)
{
    return (l->tail == NULL);
}

void insertHead(List *l, int data)
{
    Node* aux = malloc(sizeof(Node));
    aux->data = data;

    if (isEmpty(l)) {
        l->tail = aux;
    }

    aux->next = l->head;
    l->head = aux;
}

void insertTail(List *l, int data)
{
    Node* aux = malloc(sizeof(Node));
    aux->data = data;
    aux->next = NULL;

    if (isEmpty(l)) {
        l->head = aux;
        l->tail = aux;
        return;
    }

    l->tail->next = aux;
    l->tail = aux;
}

void printElements(List *l)
{
    printf("[ ");
    Node* aux = l->head;
    while (aux != NULL) {
        printf("%d ", aux->data);
        aux = aux->next;
    }
    printf("]\n");
}

void removeElement(List *l, int data)
{
    if (isEmpty(l)) {
        return;
    }
    Node* aux = l->head;

    if (l->head->data == data) {
        if (l->head == l->tail) {
            l->tail = NULL;
        }
        l->head = l->head->next;
        free(aux);
        return;
    }

    while (aux->next != NULL) {
        if (aux->next->data == data) {
            Node* toBeDeleted = aux->next;
            aux->next = aux->next->next;
            if (toBeDeleted == l->tail) {
                l->tail = aux->next;
            }
            free(toBeDeleted);
            return;
        }
        aux = aux->next;
    }
}



