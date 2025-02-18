#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>

#define MAX 512

int is_text_file(const char *zrod) {
    char buffer[MAX];
    int lbajt;
    int wynik = 1;

    int desc_zrod = open(zrod, O_RDONLY);

    if (desc_zrod == -1) {
        perror("\nBlad otwarcia pliku zrodlowego");
        printf("\n");
        exit(1);
    }

    while ((lbajt = read(desc_zrod, buffer, MAX)) > 0) {
        for (int i = 0; i < lbajt; i++) {
            if (!isascii(buffer[i])) {
                wynik = 0;
            }
        }
    }

    if (close(desc_zrod) == -1) {
        perror("\nBlad zamkniecia pliku");
        printf("\n");
        exit(1);
    }

    if (lbajt == -1) {
        perror("\nBlad odczytu pliku");
        printf("\n");
        return -1;
    }

    return wynik;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "\nZa malo argumentow, uzyj: ");
        fprintf(stderr, "%s <plik zrodlowy>\n\n", argv[0]);
        exit(1);
    }

    int result = is_text_file(argv[1]);

    if (result == 1) {
        printf("\nPlik %s jest plikiem tekstowym\n\n", argv[1]);
    } else if (result == 0) {
        printf("\nPlik %s nie jest plikiem tekstowym\n\n", argv[1]);
    } else {
        printf("\nBlad podczas sprawdzania pliku %s\n\n", argv[1]);
    }

    return 0;
}
