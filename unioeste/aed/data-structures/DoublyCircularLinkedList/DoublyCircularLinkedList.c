#include "DoublyCircularLinkedList.h"
#include "../Stack/Stack.h"

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

    if (!isEmpty(l)) {
        aux->prev = l->prev;
        aux->next = l;
        l->prev->next = aux;
        l->prev = aux;
    } else {
        aux->prev = aux->next = aux;
    }

    return aux;
}

void printElements(List* l)
{
    List* head = l;
    printf("[ ");
    if (!isEmpty(l)) {
        do {
            printf("%d ", l->data);
            l = l->next;
        } while (head != l);
    }
    printf("]\n");
}

Stack *push(Stack *s, int data) {
    return NULL;
}

List* removeElement(List* l, int data)
{
    if (isEmpty(l))
        return l;
    if (l == l->next && l->data == data) {
        free(l);
        return NULL;
    }

    List* head = l;

    while (l->next != head) {
        if (l->data == data) {
            if (l == head)
                head = head->next;
            l->next->prev = l->prev;
            l->prev->next = l->next;
            free(l);
            return head;
        }
        l = l->next;
    }

    return head;
}

List* invert(List* l)
{
    if (isEmpty(l))
        return NULL;

    List* head = l;
    List* prev = NULL;
    List* tail = NULL;

    do {
        List* curr = malloc(sizeof(List));
        curr->data = l->data;
        curr->next = prev;
        if (prev != NULL)
            prev->prev = curr;

        if (tail == NULL)
            tail = curr;

        prev = curr;
        l = l->next;
    } while (l != head);

    prev->prev = tail;
    tail->next = prev;

    return prev;
}

List* reverse(List* l)
{
    if (isEmpty(l)) {
        return NULL;
    }

    List* tail = l->prev;
    List* newHead = NULL;
    l = tail;

    do {
        List* curr = malloc(sizeof(List));
        curr->data = l->data;
        l = l->prev;

        if (newHead == NULL) {
            newHead = curr;
            curr->next = curr->prev = curr;
            continue;
        }

        curr->prev = newHead->prev;
        curr->next = newHead;
        newHead->prev->next = curr;
        newHead->prev = curr;

    } while (l != tail);

    return newHead;
}

void aux_append(List** head, int data)
{
    List* curr = malloc(sizeof(List));
    curr->data = data;

    if (isEmpty(*head)) {
        *head = curr;
        curr->next = curr->prev = curr;
        return;
    }

    curr->next = *head;
    curr->prev = (*head)->prev;
    (*head)->prev->next = curr;
    (*head)->prev = curr;
}

List* concat(List* l1, List* l2)
{
    List *head1 = l1, *head2 = l2;
    List* head = NULL;

    if (!isEmpty(l1)) {
        do {
            aux_append(&head, l1->data);
            l1 = l1->next;
        } while (l1 != head1);
    }

    if (!isEmpty(l2)) {
        do {
            aux_append(&head, l2->data);
            l2 = l2->next;
        } while (l2 != head2);
    }

    return head;
}

List* mergeShuffle(List* l1, List* l2)
{
    List *head1 = l1, *head2 = l2;
    List* head = NULL;

    if(!isEmpty(l1)) {
        aux_append(&head, l1->data);
        l1 = l1->next;
    }
    if(!isEmpty(l2)) {
        aux_append(&head, l2->data);
        l2 = l2->next;
    }

    do {
        if (l1 != head1 ) {
            aux_append(&head, l1->data);
            l1 = l1->next;
        }
        if (l2 != head2 ) {
            aux_append(&head, l2->data);
            l2 = l2->next;
        }
    } while (l1 != head1 || l2 != head2);

    return head;
}
