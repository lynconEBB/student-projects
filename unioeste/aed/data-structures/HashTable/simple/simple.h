#ifndef ADS_CLASSES_SIMPLE_H
#define ADS_CLASSES_SIMPLE_H

#include "Hashtable.h"

void initHashTable(HashTable T);

void insert(HashTable T, key_t k, registry_t r);

int search(HashTable T, key_t k);

void removeOne(HashTable T, key_t k);

void printAll(HashTable T);

int hash(int k);

#endif //ADS_CLASSES_SIMPLE_H
