#include "linearProbe.h"

void lp_initHashTable(HashTable t) {
    for (int i = 0;i < TAM; i++) {
        t[i].ocupado = 0;
    }
}

void lp_insert(HashTable t, key_t k, registry_t r) {
    for (int i = 0; i < TAM;i++) {
        int index = (lp_hash(k) + i) % TAM;
        if (!t[index].ocupado) {
            t[index].ocupado = 1;
            t[index].k = k;
            t[index].r = r;
            break;
        }
    }
}

int lp_search(HashTable t, key_t k) {
    for(int i = 0; i < TAM; i++) {
        int index = (lp_hash(k) + i) % TAM;
        if (!t[index].ocupado)
            return -1;
        if (t[index].k == k)
            return index;
    }
    return -1;
}

void lp_removeOne(HashTable t, key_t k) {
    int index = lp_search(t,k);
    if (index != -1) {
        t[index].ocupado = 0;
        t[index].k = k;
    }
}

int lp_hash(int k) {
    return k % TAM;
}