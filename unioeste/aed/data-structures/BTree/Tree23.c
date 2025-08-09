#include "Tree23.h"
#include <stdlib.h>

Node23* createNode() {
    Node23* node = malloc(sizeof(Node23));
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->middleChild = NULL;
    node->keyCount = 0;
    return node;
}
int isEmpty(Node23* node) {
    return  node == NULL;
}
int isLeaf(Node23* node) {
    return node->leftChild == NULL;
}

Node23* split(Node23* node, int key, Node23* child, int* promotedKey ) {
    if (key > node->rightKey) {
        *promotedKey = node->rightKey;

        Node23* aux = createNode();
        aux->leftKey = key;
        aux->middleChild = child;
        aux->leftChild = node->rightChild;
        aux->keyCount++;

        node->rightChild = NULL;
        node->keyCount--;
        return aux;
    }
    if (key >= node->leftKey) {
        *promotedKey = key;

        Node23* aux = createNode();
        aux->leftKey = node->rightKey;
        aux->leftChild = child;
        aux->middleChild = node->rightChild;
        aux->keyCount++;

        node->rightChild = NULL;
        node->keyCount--;

        return aux;
    }

    *promotedKey = node->leftKey;

    Node23* aux = createNode();
    aux->leftKey = node->rightKey;
    aux->leftChild = node->middleChild;
    aux->middleChild = node->rightChild;
    aux->keyCount++;

    node->leftKey = key;
    node->rightKey = 0;
    node->rightChild = NULL;
    node->middleChild = child;
    node->keyCount--;

    return aux;
}

void addKeyToNode(Node23* node, int key, Node23* child) {
    if (node->leftKey > key) {
        node->rightKey = node->leftKey;
        node->leftKey = key;
        node->rightChild = node->middleChild;
        node->middleChild = child;
    } else {
        node->rightKey = key;
        node->rightChild = child;
    }
    node->keyCount++;
}

Node23* insert_aux(Node23* node, int key, int* keyPromoted) {
    if (isLeaf(node)) {
        if (node->keyCount == 1) {
            addKeyToNode(node, key,NULL);
            return NULL;
        } else {
            return split(node,key,NULL,keyPromoted);
        }
    }

    Node23* aux;
    int promoted;
    if (key < node->leftKey) {
        aux = insert_aux(node->leftChild, key, &promoted);
    }
    else if (node->keyCount == 1 || key < node->rightKey) {
        aux = insert_aux(node->middleChild, key,&promoted);
    } else {
        aux = insert_aux(node->rightChild, key, &promoted);
    }
    if (aux == NULL)
        return NULL;
    if (node->keyCount == 1) {
        addKeyToNode(node, promoted, aux);
        return NULL;
    }

    return split(node, promoted, aux, keyPromoted);

}

Node23* insert(Node23* root, int key) {
    if (isEmpty(root)) {
        Node23* aux = createNode();
        aux->leftKey = key;
        aux->keyCount++;
        return aux;
    } else {
        int medianKey;
        Node23* aux = insert_aux(root, key,&medianKey);
        if (!isEmpty(aux)) {
            Node23* newRoot = createNode();
            newRoot->keyCount++;
            newRoot->leftKey = medianKey;
            newRoot->leftChild = root;
            newRoot->middleChild = aux;
            return  newRoot;
        } else {
            return root;
        }
    }

}
