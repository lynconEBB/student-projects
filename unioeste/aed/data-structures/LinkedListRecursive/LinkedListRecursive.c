#include "LinkedListRecursive.h"
#include "../Stack/Stack.h"

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
    if (isEmpty(l)) {
        List* head = malloc(sizeof(List));
        head->data = data;
        head->next = NULL;
        return head;
    }

    l->next = insert(l->next,data);
    return l;
}

List* removeElement(List* l, int data)
{
    if(isEmpty(l)) {
        return l;
    }
    if (l->data == data) {
        List* head = l->next;
        free(l);
        return head;
    }
    if (!isEmpty(l->next) && l->next->data == data) {
        List* toBeDeleted = l->next;
        l->next = toBeDeleted->next;
        free(toBeDeleted);
        return l;
    }

    removeElement(l->next, data);
    return l;
}

List* aux_invert(List* curr, List* prev)
{
    if (!isEmpty(curr)) {
        List* newNode = malloc(sizeof(List));
        newNode->data = curr->data;
        newNode->next = prev;
        return aux_invert(curr->next, newNode);
    }
    return prev;
}

List* invert(List* l)
{
    return aux_invert(l,NULL);
}

List* concat(List* l1, List* l2)
{
    if (isEmpty(l1) && isEmpty(l2)) {
        return NULL;
    }
    List* curr = malloc(sizeof(List));

    if (!isEmpty(l1)) {
        curr->data = l1->data;
        curr->next = concat(l1->next, l2);
        return curr;
    }
    if (!isEmpty(l2)) {
        curr->data = l2->data;
        curr->next = concat(l1, l2->next);
        return curr;
    }

    return NULL;
}

List* mergeShuffle(List* l1, List* l2)
{
    if (isEmpty(l1) && isEmpty(l2)) {
        return NULL;
    }
    List* curr = malloc(sizeof(List));

    if (!isEmpty(l1)) {
        curr->data = l1->data;
        if (!isEmpty(l2)) {
            List* curr2 = malloc(sizeof(List));
            curr->next = curr2;
            curr2->data = l2->data;
            curr2->next = mergeShuffle(l1->next, l2->next);
        } else {
            curr->next = mergeShuffle(l1->next, l2);
        }
    } else if(!isEmpty(l2)) {
        curr->data = l2->data;
        curr->next = mergeShuffle(l1,l2->next);
    }
    return curr;
}

List* append(List *l1, List *l2)
{
    if (isEmpty(l1)) {
        return l2;
    }
    List* curr = l1;
    while (!isEmpty(curr->next)) {
        curr = curr->next;
    }
    curr->next = l2;
    return l1;
}

List* recursive_append(List* l1, List* l2)
{
    if (isEmpty(l1)) {
        return l2;
    }
    l1->next = recursive_append(l1->next,l2);
    return l1;
}

int count_occurrences(List *l, int data) {
    int count;
    for (count = 0; !isEmpty(l); l = l->next) {
        if (l->data == data) {
            count++;
        }
    }
    return count;
}

int recursive_count_occurrences(List *l, int data)
{
    if (isEmpty(l)) {
        return 0;
    }
    if (l->data == data) {
        return 1 + recursive_count_occurrences(l->next, data);
    }
    return recursive_count_occurrences(l->next,data);
}

int aux_contains(List*l , int data)
{
    while (!isEmpty(l)) {
        if (data == l->data)
            return 1;
    }
    return 0;
}

List* remove_duplicates(List *l) {
    List* curr = NULL;
    List* head = l;

    while(!isEmpty(l) && !isEmpty(l->next)) {
        curr = l;
        while(!isEmpty(curr->next)) {
            if(curr->next->data == l->data) {
                List* duplicate = curr->next;
                curr->next = duplicate->next;
                free(duplicate);
            } else {
                curr = curr->next;
            }
        }
        l = l->next;
    }

    return head;
}

int recursive_count_even(List *l)
{
    if (isEmpty(l)) {
        return 0;
    }
    if (l->data % 2 == 0) {
        return 1 + recursive_count_even(l->next);
    }
    return recursive_count_occurrences(l->next);
}

