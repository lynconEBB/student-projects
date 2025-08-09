#include "TrieTree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

TrieNode *createNode() {
    TrieNode *node = malloc(sizeof(TrieNode));
    for (int i = 0; i < ALPHA_SIZE; i++) {
        node->children[i] = NULL;
    }
    node->data = -1;
    return node;
}

void insert_aux(TrieNode *node, char *str, int data) {
    if (*str == '\0') {
        node->data = data;
        return;
    }
    int index = *str - ASCII_BASE;
    if (node->children[index] == NULL) {
        node->children[index] = createNode();
    }
    str++;
    insert_aux(node->children[index], str, data);
}

void insert(TrieTree *tree, char *str, int data) {
    if (tree->root == NULL) {
        tree->root = createNode();
    }
    insert_aux(tree->root, str, data);
}

TrieNode *remove_aux(TrieNode *node, char *str) {
    int index = *str - ASCII_BASE;
    if (node == NULL)
        return node;

    if (*str == '\0' && node->data != -1) {
        node->data = -1;
    } else {
        str++;
        node->children[index] = remove_aux(node->children[index], str);
    }

    int hasChildren = 0;
    for (int i = 0; i < ALPHA_SIZE; i++) {
        if (node->children[i] != NULL) {
            hasChildren = 1;
            break;
        }
    }

    if (hasChildren || node->data != -1)
        return node;

    free(node);
    return NULL;
}

void removeOne(TrieTree *tree, char *str) {
    if (tree->root == NULL)
        return;
    tree->root = remove_aux(tree->root, str);
}

void print_aux(TrieNode *node, char *prefix, int length) {
    char newPrefix[length + 2];
    memcpy(newPrefix, prefix, length);
    newPrefix[length + 1] = '\0';

    if (node->data != -1) {
        printf("%s => %d\n", prefix, node->data);
    }
    for (int i = 0; i < ALPHA_SIZE; i++) {
        if (node->children[i] != NULL) {
            newPrefix[length] = (char) (i + ASCII_BASE);
            print_aux(node->children[i], newPrefix, length + 1);
        }
    }
}

void printDictionary(TrieTree *tree) {
    print_aux(tree->root, NULL, 0);
}

int search(TrieTree *tree, const char *str) {
    TrieNode *node = tree->root;
    for (int i = 0; str[i] != '\0'; i++) {
        int index = str[i] - ASCII_BASE;
        if (node->children[index] == NULL) {
            return -1;
        }
        node = node->children[index];
    }
    return node->data;
}

TstNode *createTst() {
    TstNode *node = malloc(sizeof(TstNode));
    node->minor = NULL;
    node->equal = NULL;
    node->greater = NULL;
    node->chr = '\0';
    node->data = -1;
    return node;
}

TstNode *insert_tst(TstNode *node, char *str, int data) {
    if (node == NULL) {
        node = createTst();
        node->chr = *str;
    }

    if (*str == node->chr) {
        if (*(str + 1) != '\0')
            node->equal = insert_tst(node->equal, str + 1, data);
        else
            node->data = data;
    } else {
        if (*str < node->chr)
            node->minor = insert_tst(node->minor, str, data);
        else
            node->greater = insert_tst(node->greater, str, data);
    }

    return node;
}

void printDict_tst_aux(TstNode *node, char *prefix, int length) {
    if (node == NULL)
        return;
    printDict_tst_aux(node->minor, prefix, length);

    char newPrefix[length + 2];
    memcpy(newPrefix, prefix, length);
    newPrefix[length + 1] = '\0';
    newPrefix[length] = node->chr;

    if (node->data != -1) {
        printf("%s => %d\n", newPrefix, node->data);
    }
    printDict_tst_aux(node->equal, newPrefix, length + 1);

    printDict_tst_aux(node->greater, prefix, length);
}

void printDictionary_tst(TstNode *tree) {
    if (tree != NULL)
        printDict_tst_aux(tree, NULL, 0);
}

int search_tst(TstNode *node, const char *str) {
    TstNode* prev;
    while (*str != '\0') {
        if (node == NULL)
            return -1;

        prev = node;
        if(node->chr == *str) {
            node = node->equal;
            str++;
        } else if (*str > node->chr) {
            node = node->greater;
        } else {
            node = node->minor;
        }

    }

    return prev->data;
}

TstNode* removeOne_tst(TstNode* node, char *str) {
    if (node == NULL || *str == '\0')
        return node;

    if (*str == node->chr) {
        if (*(str+1) != '\0') {
            node->equal = removeOne_tst(node->equal, str+1);
        } else {
            node->data = -1;
        }
    } else if (*str > node->chr) {
        node->greater = removeOne_tst(node->greater, str);
    } else {
        node->minor = removeOne_tst(node->minor, str);
    }

    if (node->minor == NULL && node->greater == NULL && node->equal == NULL && node->data == -1) {
        free(node);
        node = NULL;
    }

    return node;
}
