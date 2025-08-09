#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void printAscending(int n) {
    if (n) {
        printAscending(n-1);
    } else {
        return;
    }
    printf("%d\n", n);
}

void printDescending(int n) {
    if (n) {
        printf("%d\n", n);
        printDescending(n-1);
    }
}

int factorial(int n)
{
    if (n > 1) {
        return n * factorial(n-1);
    }
    return 1;
}

int superFactorial(int n)
{
    if (n > 1) {
        return factorial(n) * superFactorial(n-1);
    }
    return 1;
}

long exponentialFactorial(long n)
{
   if (n > 1) {
       return (long)pow(n, exponentialFactorial(n-1));
   }
   return 1;
}

int sum(int n)
{
   if (n) {
       return n + sum(n - 1);
   }
   return 0;
}

double catalanNumber(int n)
{
    if (n > 0) {
        return  ((double)(2*(2*n-1))/(n+1)) * catalanNumber(n-1);
    }
    return 1;
}

int recursivePalindrome(const char str[], int start, int end)
{
    if (start == end) {
        return 1;
    }
    if (str[start] == str[end]) {
        return recursivePalindrome(str,start+1,end-1);
    }
    return 0;
}

int isPalindrome(const char str[])
{
    int i;
    for (i = 0; str[i] != '\0'; i++) {}
    if (i == 0) return 1;
    return recursivePalindrome(str,0, i-1);
}

typedef struct {
    int size;
    char* value;
} Set;

void appendSet(Set* set, char c) {
    set->size += 1;
    realloc(set->value,sizeof(char) * set->size);
    set->value[set->size - 1] = c;
}

void popSet(Set* set) {
    set->size -= 1;
    realloc(set->value,sizeof(char) * set->size);
}

void printSet(Set* set)
{
    printf("{ ");
    for (int i = 0; i < set->size; i++) {
        printf("%c ", set->value[i]);
    }
    printf("}\n");
}

void printSubset(Set* set, int i, Set* currSet)
{
    if (i == set->size) {
        printSet(currSet);
        return;
    }

    printSubset(set, i + 1, currSet);

    appendSet(currSet, set->value[i]);
    printSubset(set, i + 1, currSet);
    popSet(currSet);
}


void recursiveInvert(int arr[], int start, int end)
{
    if (start < end) {
        int aux = arr[end];
        arr[end] = arr[start];
        arr[start] = aux;
        recursiveInvert(arr, start+1, end-1);
    }
}

void invertArray(int arr[], int size)
{
    if (size > 1) {
        recursiveInvert(arr, 0, size-1);
    }
}

int ackermanFunction(int m, int n) {
    if (m == 0) {
        return n + 1;
    }
    else if (m > 0 && n == 0) {
        return ackermanFunction(m-1,1);
    }
    else if (m > 0 && n > 0) {
        return ackermanFunction(m-1, ackermanFunction(m, n-1));
    }
}

int sumDigits(int n) {
    if (n != 0) {
        return n % 10 + sumDigits(n / 10);
    }
    return 0;
}