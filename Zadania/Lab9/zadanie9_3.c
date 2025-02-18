#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAX 512

int main(int argc, char* argv[]) {
    char buf[MAX];
    int desc_zrod, desc_cel;
    int lbajt;

    if (argc < 3) {
        fprintf(stderr, "\nZa malo argumentow, uzyj: ");
        fprintf(stderr, "%s <plik zrodlowy> <plik docelowy>\n\n", argv[0]);
        exit(1);
    }

    desc_zrod = open(argv[1], O_RDONLY);

    if (desc_zrod == -1) {
        perror("\nBlad otwarcia pliku zrodlowego");
        printf("\n");
        exit(1);
    }

    desc_cel = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (desc_cel == -1) {
        perror("\nBlad otwarcia pliku docelowego");
        printf("\n");
        exit(1);
    }

    while ((lbajt = read(desc_zrod, buf, MAX)) > 0) {
        if (write(desc_cel, buf, lbajt) != lbajt) {
            perror("\nBlad zapisu pliku docelowego");
            printf("\n");
            exit(1);
        }
    }

    if (lbajt == -1) {
        perror("\nBlad odczytu pliku zrodlowego");
        printf("\n");
        exit(1);
    }

    if (close(desc_zrod) == -1 || close(desc_cel) == -1) {
        perror("\nBlad zamkniecia pliku");
        printf("\n");
        exit(1);
    }

    exit(0);
}
