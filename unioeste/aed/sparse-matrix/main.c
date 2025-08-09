#include <stdio.h>
#include "App.h"
#include "Matrix.h"

int main() {
    Matrix* mBuffer[MIN_M_BUFFER] = {NULL, NULL, NULL};
    FILE* fBuffer[MIN_F_BUFFER] = {NULL, NULL};

    startApp(mBuffer, fBuffer);
    return 0;
}

