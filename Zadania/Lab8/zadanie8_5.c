#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void errnoExample() {
    FILE *file = fopen("test.txt", "r");
    if (file == NULL) {
        printf("\nError opening file: %s\n\n", strerror(errno));
    } else {
        fclose(file);
    }
}

int main() {
    errnoExample();

    return 0;
}
