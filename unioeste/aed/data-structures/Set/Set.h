#ifndef LISTA1_SET_H
#define LISTA1_SET_H

typedef struct set {
    int data;
    struct set* next;
} Set;

Set* insert(Set* s, int data);

int contains(Set* s, int data);

Set* unionOf(Set* s1, Set* s2);

Set* intersection(Set* s1, Set* s2);

Set* difference(Set* s1, Set* s2);

int itsContained(Set* s1, Set* s2);

void printElements(Set* s);

#endif
