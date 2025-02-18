#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAX 512

int main(int argc, char *argv[]) {
    char buffer[MAX];
    int desc_zrod, desc_cel;
    int lbajt;

    if (argc < 3) {
        fprintf(stderr, "\nZa malo argumentow, uzyj: ");
        fprintf(stderr, "%s <plik1> <plik2> ... <plik_wynikowy>\n\n", argv[0]);
        exit(1);
    }

    desc_cel = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (desc_cel == -1) {
        perror("\nBlad otwarcia pliku wynikowego");
        printf("\n");
        exit(1);
    }

    for (int i = 1; i < argc - 1; i++) {
        desc_zrod = open(argv[i], O_RDONLY);

        if (desc_zrod == -1) {
            perror("\nBlad otwarcia pliku zrodlowego");
            printf("\n");
            exit(1);
        }

        while ((lbajt = read(desc_zrod, buffer, MAX)) > 0) {
            if (write(desc_cel, buffer, lbajt) != lbajt) {
                perror("\nBlad zapisu do pliku wynikowego");
                printf("\n");
                exit(1);
            }
        }

        if (lbajt == -1) {
            perror("\nBlad odczytu pliku zrodlowego");
            printf("\n");
            exit(1);
        }

        if (close(desc_zrod) == -1) {
            perror("\nBlad zamkniecia pliku zrodlowego");
            printf("\n");
            exit(1);
        }
    }

    if (close(desc_cel) == -1) {
        perror("\nBlad zamkniecia pliku wynikowego");
        printf("\n");
        exit(1);
    }
    
    return 0;
}
