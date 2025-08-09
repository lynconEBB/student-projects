#ifndef ADS_CLASSES_LINEARPROBE_H
#define ADS_CLASSES_LINEARPROBE_H

#include "Hashtable.h"

void lp_initHashTable(HashTable T);

void lp_insert(HashTable T, key_t k, registry_t r);

int lp_search(HashTable T, key_t k);

void lp_removeOne(HashTable T, key_t k);

int lp_hash(int k);

#endif