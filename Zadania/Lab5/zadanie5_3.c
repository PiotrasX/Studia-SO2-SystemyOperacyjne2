#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printWords(FILE *fp) {
    char line[1024];

    while (fgets(line, sizeof(line), fp) != NULL) {
        char *word = strtok(line, " \t\n");

        while (word != NULL) {
            printf("%s\n", word);
            word = strtok(NULL, " \t\n");
        }
    }
}

int main() {
    FILE *file = fopen("test.txt", "r");
    if (file == NULL) {
        perror("\nBlad przy otwieraniu pliku");
        printf("\n");
        return 1;
    }

    printf("\n");
    printWords(file);
    fclose(file);
    printf("\n");

    return 0;
}
