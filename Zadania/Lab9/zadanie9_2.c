#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    int desc;
    long rozm;

    if (argc < 2) {
        fprintf(stderr, "\nZa malo argumentow, uzyj: ");
        fprintf(stderr, "%s <nazwa pliku>\n\n", argv[0]);
        exit(1);
    }

    desc = open(argv[1], O_RDONLY);

    if (desc == -1) {
        perror("\nBlad otwarcia pliku");
        printf("\n");
        exit(1);
    }

    rozm = lseek(desc, 0, SEEK_END);

    if (rozm == -1) {
        perror("\nBlad w pozycjonowaniu");
        printf("\n");
        exit(1);
    }

    printf("\nRozmiar pliku %s: %ld\n\n", argv[1], rozm);

    if (close(desc) == -1) {
        perror("\nBlad zamkniecia pliku");
        printf("\n");
        exit(1);
    }

    exit(0);
}
