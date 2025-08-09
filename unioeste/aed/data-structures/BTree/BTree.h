#ifndef ADS_CLASSES_BTREE_H
#define ADS_CLASSES_BTREE_H
#define DEGREE 5
typedef struct node {
    int keyCount;
    int keys[DEGREE - 1];
    struct node *children[DEGREE];
} BNode;

typedef struct NodeBPlus {
    void** children;
    int* keys;
    int isLeaf;
    int keyCount;
} NodeBPlus;

int search_k(BNode *node, int k);

int countLeafs(NodeBPlus* node);

#endif