cmake_minimum_required(VERSION 3.16)

project(
        ads-classes
        LANGUAGES C
        )

# Libs
add_library(LinkedList STATIC LinkedList/LinkedList.c)
target_include_directories(LinkedList PUBLIC LinkedList/)

add_library(LinkedListRecursive STATIC LinkedListRecursive/LinkedListRecursive.c)
target_include_directories(LinkedListRecursive PUBLIC LinkedListRecursive/)

add_library(LinkedListSorted STATIC LinkedListSorted/LinkedListSorted.c)
target_include_directories(LinkedListSorted PUBLIC LinkedListSorted/)

add_library(LinkedListTailHead STATIC LinkedListTailHead/LinkedListTailHead.c)
target_include_directories(LinkedListTailHead PUBLIC LinkedListTailHead/)

add_library(DoublyLinkedList STATIC DoublyLinkedList/DoublyLinkedList.c)
target_include_directories(DoublyLinkedList PUBLIC DoublyLinkedList/)

add_library(DoublyCircularLinkedList STATIC DoublyCircularLinkedList/DoublyCircularLinkedList.c)
target_include_directories(DoublyCircularLinkedList PUBLIC DoublyCircularLinkedList/)

add_library(Set STATIC Set/Set.c)
target_include_directories(Set PUBLIC Set/)

add_library(Queue STATIC Queue/Queue.c)
target_include_directories(Queue PUBLIC Queue/)

add_library(Stack STATIC Stack/Stack.c)
target_include_directories(Stack PUBLIC Stack/)

add_library(HashTable STATIC HashTable/simple/simple.c HashTable/linearProbe/linearProbe.c)
target_include_directories(HashTable PUBLIC HashTable/)

add_library(BinaryTree STATIC BinaryTree/BinaryTree.c TrieTree/TrieTree.c TrieTree/TrieTree.h)
target_include_directories(BinaryTree PUBLIC BinaryTree/)

add_library(BTree STATIC BTree/Tree23.c BTree/Tree23.h BTree/BTree.c BTree/BTree.h)
target_include_directories(BTree PUBLIC BTree/)

add_library(TrieTree STATIC TrieTree/TrieTree.c)
target_include_directories(TrieTree PUBLIC TrieTree/)

#StandAlone
add_executable(Expressions Standalone/arithmeticExpression.c)
add_executable(Recursion Standalone/recursion.c)

#Main
add_executable(Main main.c)
target_link_libraries(Main PUBLIC TrieTree)