#include "Queue.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Queue *newQueue()
{
    Queue* queue = malloc(sizeof(Queue));
    queue->n = 0;
    queue->last = NULL;
    queue->first = NULL;
    return queue;
}

int isEmpty(Queue *q)
{
    return (q->n <= 0);
}

void printElements(Queue *q)
{
    printf("[ ");
    Node* curr = q->first;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("]\n");
}

void enqueue(Queue *q, int data)
{
    Node* aux = malloc(sizeof(Node));
    aux->data = data;
    aux->next = NULL;

    if (isEmpty(q)) {
        q->first = aux;
    } else {
        q->last->next = aux;
    }
    q->n++;
    q->last = aux;
}

void dequeue(Queue *q)
{
    if (isEmpty(q)) {
        return;
    }
    Node* toBeDeleted = q->first;
    if (q->n == 1)
        q->last = NULL;

    q->first = q->first->next;
    q->n--;
    free(toBeDeleted);
}

void reverse(Queue *q)
{
    int data;
    if (isEmpty(q)) {
        return;
    } else {
        data = q->first->data;
        dequeue(q);
        reverse(q);
        enqueue(q, data);
    }
}
