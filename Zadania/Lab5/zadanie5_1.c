#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Zadanie 5.1.1

void printChars(FILE *fp) {
    int c;
    while ((c = fgetc(fp)) != EOF) {
        putchar(c);
    }
}

// Koniec zadania 5.1.1



// Zadanie 5.1.2

void printLines(FILE *fp) {
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
}

// Koniec zadania 5.1.2



// Zadanie 5.1.3

void copy(const char *addr1, const char *addr2) {
    FILE *src = fopen(addr1, "rb");
    if (src == NULL) {
        perror("Blad przy otwieraniu pliku zrodlowego");
        printf("\n");
        return;
    }

    FILE *dest = fopen(addr2, "wb");
    if (dest == NULL) {
        perror("Blad przy otwieraniu pliku docelowego");
        printf("\n");
        fclose(src);
        return;
    }

    char buffer[1024];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    printf("Kopiowanie plikow zakonczono pomyslnie!\n\n");
    fclose(src);
    fclose(dest);
}

// Koniec zadania 5.1.3



int main() {
    FILE *file = fopen("test.txt", "r");
    if (file == NULL) {
        perror("\nBlad przy otwieraniu pliku");
        printf("\n");
        return 1;
    }

    printf("\nZawartosc pliku bajt po bajcie:\n");
    printChars(file);
    rewind(file);

    printf("\nZawartosc pliku linia po linii:\n");
    printLines(file);
    fclose(file);

    printf("\nDzialanie funkcji 'copy':\n");
    copy("test.txt", "kopia.txt");

    return 0;
}
