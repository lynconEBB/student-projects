#ifndef LISTA1_LINKEDLISTTAILHEAD_H
#define LISTA1_LINKEDLISTTAILHEAD_H

typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} List;

List* newList();

int isEmpty(List* l);

void insertHead(List* l, int data);

void insertTail(List* l, int data);

void printElements(List* l);

void removeElement(List* l, int data);

#endif
