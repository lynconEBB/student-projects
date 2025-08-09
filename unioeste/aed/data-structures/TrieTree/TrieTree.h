#ifndef ADS_CLASSES_TRIETREE_H
#define ADS_CLASSES_TRIETREE_H
#define ALPHA_SIZE 26
#define ASCII_BASE 97

typedef struct TstNode {
    char chr;
    int data;
    struct TstNode *minor;
    struct TstNode *equal;
    struct TstNode *greater;
} TstNode;

typedef struct TrieNode {
    struct TrieNode *children[ASCII_BASE];
    int data;
} TrieNode;

typedef struct {
    TrieNode *root;
} TrieTree;

TstNode* insert_tst(TstNode* node, char* str, int data);

TstNode* removeOne_tst(TstNode* tree, char *str);

void printDictionary_tst(TstNode* tree);

int search_tst(TstNode* tree, const char *str);

void insert(TrieTree *tree, char *str, int data);

void removeOne(TrieTree *tree, char *str);

void printDictionary(TrieTree *tree);

int search(TrieTree *tree, const char *str);

#endif