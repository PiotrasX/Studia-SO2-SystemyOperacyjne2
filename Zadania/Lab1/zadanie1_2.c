#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("\nWprowadz dane lub nacisnij Ctrl+Z: ");

    int c;
    c = getchar();

    if (c == EOF) {
        printf("Strumien wejsciowy jest pusty.\n\n");
    } else {
        printf("Strumien wejsciowy nie jest pusty.\n\n");
    }

    return 0;
}
