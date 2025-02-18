#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    #if defined(_WIN32) || defined(_WIN64)
    printf("\nProgram compiled on: Windows\n\n");
    #elif defined(__unix__) || defined(__unix)
    printf("\nProgram compiled on: UNIX\n\n");
    #elif defined(__APPLE__) || defined(__MACH__)
    printf("\nProgram compiled on: MacOS\n\n");
    #elif defined(__linux__)
    printf("\nProgram compiled on: Linux\n\n");
    #else
    printf("\nUnknown system\n\n");
    #endif

    return 0;
}
