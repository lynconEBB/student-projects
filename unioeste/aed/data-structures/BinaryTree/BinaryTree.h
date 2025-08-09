#ifndef ADS_CLASSES_BINARYTREE_H
#define ADS_CLASSES_BINARYTREE_H

#include <stddef.h>

struct node {
    int info;
    struct node* left;
    struct node* right;
};

typedef struct node* Tree;

typedef struct nodeStack{
    Tree treeNode;
    struct nodeStack* next;
} Stack;

int isEmpty(Stack* s);

Stack* push(Stack* s, int data);

Stack* pop(Stack* s);

int empty(Tree t);

Tree insert(Tree t, int info);
Tree rec_insert(Tree t, int info);

Tree removeNode(Tree t, int info);
Tree rec_removeNode(Tree t, int info);

void inFixPrint(Tree t);
void rec_inFixPrint(Tree t);

void preFixPrint(Tree t);
void rec_preFixPrint(Tree t);

void posFixPrint(Tree t);
void rec_posFixPrint(Tree t);

Tree min(Tree t);
Tree rec_min(Tree t);

Tree max(Tree t);
Tree rec_max(Tree t);

int height(Tree t);

int sum(Tree t);

int isFull(Tree t,int* level, int currentLevel);

int next(Tree t, int info);

void interval(Tree t, int a, int b);

int countLeafs(Tree t);
#endif