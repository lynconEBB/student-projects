#include <stdio.h>
#include "TrieTree.h"
#include <stdlib.h>

int main (void)
{
    TstNode* t = insert_tst(NULL, "cara", 10);
    t = insert_tst(t, "caramba", 30);
    t = insert_tst(t, "zumba", 40);
    t = insert_tst(t, "zoom", 20);
    t = insert_tst(t, "zon", 100);
    printDictionary_tst(t);
    t = removeOne_tst(t,"caramba");
    t = removeOne_tst(t,"ar");
    printf("=============\n");
    printDictionary_tst(t);
    return 0;
}