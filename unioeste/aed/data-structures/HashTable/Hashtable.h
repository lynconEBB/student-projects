#ifndef ADS_CLASSES_HASHTABLE_H
#define ADS_CLASSES_HASHTABLE_H

#define TAM 100

typedef int key_t;

typedef struct {
    int matricula;
    char nome[50];
} registry_t;

typedef struct {
    key_t k;
    registry_t r;
    int ocupado;
} slot_t;

typedef slot_t HashTable[TAM];


#endif