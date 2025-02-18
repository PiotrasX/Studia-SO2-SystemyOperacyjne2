#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 1

void compare_files(int desc1, int desc2, const char *file1, const char *file2) {
    char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
    int lbajt1, lbajt2;
    int pozycja = 1;
    int linia = 1;

    while (1) {
        lbajt1 = read(desc1, buf1, BUFFER_SIZE);
        lbajt2 = read(desc2, buf2, BUFFER_SIZE);
        if (lbajt1 > 0 && lbajt2 > 0) {
            if (buf1[0] != buf2[0]) {
                printf("\nPliki roznia sie od znaku nr %d w linii %d\n\n", pozycja, linia);

                if (close(desc1) == -1 || close(desc2) == -1) {
                    perror("\nBlad zamkniecia plikow");
                    printf("\n");
                    exit(1);
                }

                exit(0);
            }
            if (buf1[0] == '\n') {
                linia++;
                pozycja = 0;
            }
            pozycja++;
        } else {
            break;
        }
    }

    if (lbajt1 == 0 && lbajt2 == 0) {
        printf("\nPliki sa identyczne\n\n");
    } else if (lbajt1 > 0) {
        int extra_chars = 1;

        while ((lbajt1 = read(desc1, buf1, BUFFER_SIZE)) > 0) {
            extra_chars++;
        }

        printf("\nPlik %s zawiera %d znakow wiecej niz zawartosc pliku %s\n\n", file1, extra_chars, file2);
    } else if (lbajt2 > 0) {
        int extra_chars = 1;

        while ((lbajt2 = read(desc2, buf2, BUFFER_SIZE)) > 0) {
            extra_chars++;
        }

        printf("\nPlik %s zawiera %d znakow wiecej niz zawartosc pliku %s\n\n", file2, extra_chars, file1);
    }

    if (close(desc1) == -1 || close(desc2) == -1) {
        perror("\nBlad zamkniecia plikow");
        printf("\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    int desc1, desc2;

    if (argc < 3) {
        fprintf(stderr, "\nZa malo argumentow, uzyj: ");
        fprintf(stderr, "%s <plik1> <plik2>\n\n", argv[0]);
        exit(1);
    }

    desc1 = open(argv[1], O_RDONLY);

    if (desc1 == -1) {
        perror("\nBlad otwarcia pliku 1");
        printf("\n");
        exit(1);
    }

    desc2 = open(argv[2], O_RDONLY);

    if (desc2 == -1) {
        perror("\nBlad otwarcia pliku 2");
        printf("\n");
        exit(1);
    }

    compare_files(desc1, desc2, argv[1], argv[2]);

    return 0;
}
