#include "LinkedList.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int isEmpty(List *l) {
    return (l == NULL);
}

List* insert(List *l, int data) {
    List* aux = (List*) malloc(sizeof(List));
    aux->next = l;
    aux->data = data;
    return aux;
}

List* removeElement(List *l, int data) {
    List* prev = l;
    List* curr = l;

    while (!isEmpty(curr) && curr->data != data) {
        prev = curr;
        curr = curr->next;
    }

    if (!isEmpty(curr)) {
        if(curr == prev) {
            l = l->next;
        } else {
            prev->next = curr->next;
        }
        free(curr);
    }
    return l;
}

void printElements(List *l) {
    printf("[ ");
    while (!isEmpty( l)) {
        printf("%d ", l->data);
        l = l->next;
    }
    printf("]\n");
}

List* aux_newFrom(List* l) {
    List* curr = NULL;
    List* prev = NULL;
    List* head = NULL;

    for (;!isEmpty(l); l = l->next, prev = curr) {
        curr = malloc(sizeof(List));
        curr->data = l->data;
        curr->next = NULL;

        if (!isEmpty(prev)) {
            prev->next = curr;
        }
        if (isEmpty(head)) {
            head = curr;
        }
    }

    return head;
}

List *concat(List *l1, List *l2)
{
    if (isEmpty(l1)) {
        return aux_newFrom(l2);
    } else if (isEmpty(l2)) {
        return aux_newFrom(l1);
    }

    List* head = aux_newFrom(l1);
    List* curr = head;

    while (!isEmpty(curr->next)) {
        curr = curr->next;
    }
    curr->next = aux_newFrom(l2);

    return head;
}

void aux_appendToTail(List** source, List** curr, List** prev)
{
    *curr = malloc(sizeof(List));
    (*curr)->data = (*source)->data;
    (*prev)->next = *curr;
    *prev = *curr;
    *source = (*source)->next;
}

List* mergeShuffle(List *l1, List *l2)
{
    if (isEmpty(l1)) {
        return aux_newFrom(l2);
    } else if (isEmpty(l2)) {
        return aux_newFrom(l1);
    }

    List* head = malloc(sizeof(List));
    head->data = l1->data;
    l1 = l1->next;

    List* curr = NULL;
    List* prev = head;

    while(!isEmpty(l1) || !isEmpty(l2)) {
        if (!isEmpty(l2))
            aux_appendToTail(&l2, &curr, &prev);
        if (!isEmpty(l1))
            aux_appendToTail(&l1, &curr, &prev);
    }

    return head;
}

List *invert(List *l)
{
    List* prev = NULL;
    List* curr = NULL;

    while(!isEmpty(l)) {
        curr = malloc(sizeof(List));
        curr->data = l->data;
        curr->next = prev;
        prev = curr;
        l = l->next;
    }

    return prev;
}

int somar_intervalo(List *l, int a, int b) {
    if (isEmpty(l))
        return 0;

    if (l->data >= a && l->data <= b)
        return l->data + somar_intervalo(l->next,a,b);
    else
        return somar_intervalo(l->next,a,b);
}

List *filtrar(List *l, int n) {
    if (n <= 0 || isEmpty(l))
        return NULL;

    List* newList = malloc(sizeof(List));
    newList->data = l->data;
    newList->next = NULL;
    List* head = newList;
    l = l->next;

    int cont = 1;
    int jump = 0;
    while (!isEmpty(l)) {
        if (cont >= n) {
            jump = !jump;
            cont = 0;
        }
        if (!jump) {
            newList->next = malloc(sizeof(List));
            newList->next->data = l->data;
            newList = newList->next;
            newList->next = NULL;
        }
        cont++;
        l = l->next;
    }
    return head;
}
void dividirLista(List* src, List** metadeDir, List** metadEsq) {
    List *rapido, *lento;
    rapido = src->next;
    lento = src;

    while (!isEmpty(rapido)) {
        rapido = rapido->next;
        if (!isEmpty(rapido)) {
            rapido = rapido->next;
            lento = lento->next;
        }
    }

    *metadeDir = src;
    *metadEsq = lento->next;
    lento->next = NULL;
}
List* intercalar(List* d, List* e) {
    List* ant = NULL;
    List* head = NULL;
    List* proximo = NULL;
    while (!isEmpty(d) && !isEmpty(e)) {
        if (d->data <= e->data) {
            proximo = d->next;
            d->next = e;
            if (!isEmpty(ant))
                ant->next = d;
            ant = d;
            d = proximo;
        } else {
            proximo = e->next;
            e->next = d;
            if (!isEmpty(ant))
                ant->next = e;
            ant = e;
            e = proximo;
        }
        if (isEmpty(head))
            head = ant;
    }
    return head;
}
void merge_sort(List **l) {
    if (isEmpty(*l) || isEmpty((*l)->next))
        return;

    List *dir, *esq;

    dividirLista(*l,&dir,&esq);
    merge_sort(&dir);
    merge_sort(&esq);
    *l = intercalar(dir, esq);
    return;
}

