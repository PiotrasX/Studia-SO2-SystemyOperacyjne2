#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Zadanie 5.4.1

void printHex(FILE *fp) {
    int c;
    while ((c = fgetc(fp)) != EOF) {
        printf("%02X ", c);
    }
    printf("\n");
}

// Koniec zadania 5.4.1



// Zadanie 5.4.2

void printChar(FILE *fp) {
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            printf("'\\n' ");
        } else if (c == '\r') {
            printf("'\\r' ");
        } else {
            printf("'%c' ", c);
        }
    }
    printf("\n");
}

// Koniec zadania 5.4.2



// Zadanie 5.4.3

void printLinesHex(FILE *fp) {
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        for (int i = 0; line[i] != '\0'; i++) {
            printf("%02X ", line[i]);
        }
        printf("\n");
    }
}

// Koniec zadania 5.4.3



// Zadanie 5.4.4

void printLinesChar(FILE *fp) {
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == '\n') {
                printf("'\\n' ");
            } else if (line[i] == '\r') {
                printf("'\\r' ");
            } else {
                printf("'%c' ", line[i]);
            }
        }
        printf("\n");
    }
}

// Koniec zadania 5.4.4



int main() {
    int choice;
    char filename[256];

    printf("\n");
    printf("1 linux.txt\n");
    printf("2 windows.txt\n");
    printf("\nChoose file: ");
    scanf("%d", &choice);

    if (choice == 1) {
        sprintf(filename, "linux.txt");
    } else if (choice == 2) {
        sprintf(filename, "windows.txt");
    } else {
        printf("\nInvalid choice!\n\n");
        return 1;
    }

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("\nError opening file");
        printf("\n");
        return 1;
    }

    printf("\n%s\n", filename);

    printf("\n");
    printHex(file);
    rewind(file);

    printf("\n");
    printChar(file);
    rewind(file);

    printf("\n");
    printLinesHex(file);
    rewind(file);

    printf("\n");
    printLinesChar(file);

    printf("\n");
    fclose(file);

    return 0;
}
