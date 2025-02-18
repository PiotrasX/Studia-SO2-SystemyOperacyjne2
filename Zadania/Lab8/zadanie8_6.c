#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void perrorExample() {
    FILE *file = fopen("test.txt", "r");
    if (file == NULL) {
        perror("\nError opening file");
        printf("\n");
    } else {
        fclose(file);
    }
}

int main() {
    perrorExample();

    return 0;
}
