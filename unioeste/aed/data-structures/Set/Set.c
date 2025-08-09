#include "Set.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int contains(Set *s, int data) {
    while (s != NULL) {
        if (s->data == data) {
            return true;
        }
        s = s->next;
    }
    return false;
}

Set* newNode(int data) {
    Set* aux = malloc(sizeof(Set));
    aux->data = data;
    aux->next = NULL;
    return aux;
}

Set* insert(Set *s, int data) {

    if (s == NULL ) {
        return newNode(data);
    }

    Set* head = s;
    Set* prev = s;
    while(s != NULL) {
        if (s->data == data) {
            return head;
        }
        prev = s;
        s = s->next;
    }

    prev->next = newNode(data);
    return head;
}

void printElements(Set *s) {
    printf("[ ");
    while (s != NULL) {
        printf("%d ", s->data);
        s= s->next;
    }
    printf("]\n");
}

Set* unionOf(Set *s1, Set *s2) {
    Set* head = NULL;

    while (s1 != NULL) {
        Set* aux = newNode(s1->data);
        aux->next = head;
        head = aux;
        s1 = s1->next;
    }

    Set* head1 = head;
    while (s2 != NULL) {
        if (!contains(head1, s2->data)) {
            Set* aux = newNode(s2->data);
            aux->next = head;
            head = aux;
        }
        s2 = s2->next;
    }

    return head;
}

Set *intersection(Set *s1, Set *s2) {
    Set* head = NULL;
    while (s1 != NULL) {
        if (contains(s2, s1->data)) {
            Set* aux = newNode(s1->data);
            aux->next = head;
            head = aux;
        }
        s1 = s1->next;
    }
    return head;
}

Set *difference(Set *s1, Set *s2) {
    Set* head = NULL;
    while (s1 != NULL) {
        if (!contains(s2, s1->data)) {
            Set* aux = newNode(s1->data);
            aux->next = head;
            head = aux;
        }
        s1 = s1->next;
    }
    return head;
}

int itsContained(Set *s1, Set *s2) {
    while (s2 != NULL) {
        if (!contains(s1, s2->data)) {
            return false;
        }
        s2 = s2->next;
    }
    return true;
}

