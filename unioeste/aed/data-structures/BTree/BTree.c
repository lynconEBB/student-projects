#include "BTree.h"
#include <stddef.h>

int isLeaf(BNode* node) {
    return node->children[0] == NULL;
}

int search_aux(BNode* node, int* k) {
    if (!isLeaf(node)) {
        int data = search_aux(node->children[0], k);
        if (data != -1) {
            return data;
        }
    }
    if (node->keyCount < *k) {
        *k = *k - node->keyCount;
        return -1;
    }
    return node->keys[(*k) - 1];
}

int search_k(BNode *node, int k) {
    if (node != NULL) {
        return search_aux(node, &k);
    }
    return -1;
}

int countLeafs(NodeBPlus* node) {
    if (node == NULL)
        return 0;

    int leafCount = 0;
    while (!node->isLeaf) {
        node = node->children[0];
    }

    leafCount++;
    while (node->children[DEGREE-1] != NULL) {
        node = node->children[DEGREE-1];
        leafCount++;
    }
    return leafCount;
}