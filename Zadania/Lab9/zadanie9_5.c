#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAX 4096

// Kopiowanie ostatnich 10 znaków
void copy_last_10_chars(int zrod, int cel, int file_size) {
    char buf[10];

    if (lseek(zrod, -1, SEEK_END) == -1) {
        perror("Blad ustawiania pozycji w pliku");
        printf("\n");
        exit(1);
    }

    char last_char;

    if (read(zrod, &last_char, 1) != 1) {
        perror("\nBlad czytania ostatniego znaku");
        printf("\n");
        exit(1);
    }

    int offset = (last_char == '\n') ? file_size - 12 : file_size - 10;
    offset = offset >= 0 ? offset : 0;

    if (lseek(zrod, offset, SEEK_SET) == -1) {
        perror("Blad ustawiania pozycji w pliku");
        printf("\n");
        exit(1);
    }

    int lbajt = read(zrod, buf, 10);

    if (lbajt > 0) {
        if (write(cel, buf, lbajt) != lbajt) {
            perror("\nBlad zapisu danych do pliku docelowego");
            printf("\n");
            exit(1);
        }
        write(cel, "\n", 1);
    }
}

// Kopiowanie ostatnich 10 słów
void copy_last_10_words(int zrod, int cel, int file_size) {
    char buf[MAX];

    if (lseek(zrod, 0, SEEK_SET) == -1) {
        perror("Blad ustawiania pozycji w pliku");
        printf("\n");
        exit(1);
    }

    int lbajt = read(zrod, buf, file_size > MAX ? MAX : file_size);
    
    if (lbajt > 0) {
        buf[lbajt] = '\0';
        char *words[1000];
        int count = 0;

        char *word = strtok(buf, " \n\t");
        
        while (word != NULL) {
            words[count++] = word;
            word = strtok(NULL, " \n\t");
        }

        int start = count > 10 ? count - 10 : 0;
        
        for (int i = start; i < count; i++) {
            if (write(cel, words[i], strlen(words[i])) != strlen(words[i]) || write(cel, " ", 1) != 1) {
                perror("\nBlad zapisu danych do pliku docelowego");
                printf("\n");
                exit(1);
            }
        }
        write(cel, "\n", 1);
    }
}

// Kopiowanie ostatnich 10 linii
void copy_last_10_lines(int zrod, int cel, int file_size) {
    char buf[MAX];

    if (lseek(zrod, 0, SEEK_SET) == -1) {
        perror("Blad ustawiania pozycji w pliku");
        printf("\n");
        exit(1);
    }

    int lbajt = read(zrod, buf, file_size > MAX ? MAX : file_size);
    
    if (lbajt > 0) {
        buf[lbajt] = '\0';
        char *lines[1000];
        int count = 0;

        char *line = strtok(buf, "\n");
        
        while (line != NULL) {
            lines[count++] = line;
            line = strtok(NULL, "\n");
        }

        int start = count > 10 ? count - 10 : 0;
        
        for (int i = start; i < count; i++) {
            if (write(cel, lines[i], strlen(lines[i])) != strlen(lines[i]) || write(cel, "\n", 1) != 1) {
                perror("\nBlad zapisu danych do pliku docelowego");
                printf("\n");
                exit(1);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int desc_zrod, desc_cel;
    int file_size;

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

    file_size = lseek(desc_zrod, 0, SEEK_END);

    if (file_size == -1) {
        perror("\nBlad uzyskania rozmiaru pliku");
        printf("\n");
        exit(1);
    }

    copy_last_10_chars(desc_zrod, desc_cel, file_size);
    copy_last_10_words(desc_zrod, desc_cel, file_size);
    copy_last_10_lines(desc_zrod, desc_cel, file_size);

    if (close(desc_zrod) == -1 || close(desc_cel) == -1) {
        perror("\nBlad zamkniecia pliku");
        printf("\n");
        exit(1);
    }

    return 0;
}
