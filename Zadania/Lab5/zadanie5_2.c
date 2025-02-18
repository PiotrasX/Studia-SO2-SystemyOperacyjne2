#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



// Zadanie 5.2.1

int countWords1(FILE *fp) {
    int c;
    int inside = 0;
    int wordCount = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (isspace(c)) {
            inside = 0;
        } else {
            if (inside == 0) {
                wordCount++;
                inside = 1;
            }
        }
    }

    return wordCount;
}

// Koniec zadania 5.2.1



// Zadanie 5.2.2

int countWords2(FILE *fp) {
    int c;
    int wordCount = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (!isspace(c)) {
            wordCount++;
            while ((c = fgetc(fp)) != EOF && !isspace(c)) { }
        }
    }

    return wordCount;
}

// Koniec zadania 5.2.2



int main() {
    FILE *file = fopen("test.txt", "r");
    if (file == NULL) {
        perror("\nBlad przy otwieraniu pliku");
        printf("\n");
        return 1;
    }

    rewind(file);
    int words1 = countWords1(file);
    printf("\nLiczba slow z funkcji 'countWords1': %d\n", words1);

    rewind(file);
    int words2 = countWords2(file);
    printf("\nLiczba slow z funkcji 'countWords2': %d\n\n", words2);

    fclose(file);

    return 0;
}
