#ifndef ADS_CLASSES_TREE23_H
#define ADS_CLASSES_TREE23_H

typedef struct node23 {
    int leftKey;
    int rightKey;
    struct node23* leftChild;
    struct node23* middleChild;
    struct node23* rightChild;
    int keyCount;
} Node23;

Node23* insert(Node23* root, int key);
#endif