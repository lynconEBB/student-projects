#ifndef LISTAS_QUEUE_H
#define LISTAS_QUEUE_H

typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct {
    int n;
    Node* first;
    Node* last;
} Queue;

Queue* newQueue();

int isEmpty(Queue* q);

void enqueue(Queue* q, int data);

void dequeue(Queue* q);

void printElements(Queue* q);

void reverse(Queue* q);

#endif