#include <stdio.h>
#include "simple.h"


int hash(int k){
    return k % TAM;
}

void initHashTable(HashTable t) {
    for (int i = 0; i < TAM;i++) {
        t[i].ocupado = 0;
    }
}

void insert(HashTable t, key_t k, registry_t r) {
    int index = hash(k);
    if (t[index].ocupado)
        return;

    t[index].k = k;
    t[index].r = r;
    t[index].ocupado = 1;
}

int search(HashTable t,key_t k) {
    int i = hash(k);
    if (!t[i].ocupado)
        return -1;
    else
        return i;
}

void removeOne(HashTable t, key_t k) {
    int i = hash(k);
    if (!t[i].ocupado)
        return;

    t[i].ocupado = 0;
    t[i].k = 0;
}

void printAll(HashTable t) {
    for (int i = 0; i < TAM; i++ ) {
        if (t[i].ocupado) {
            printf("[%d] %d => {%d, %s}\n",i, t[i].k, t[i].r.matricula, t[i].r.nome);
        }
    }
}