#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAX 512

void reverse_line(char *line, int len) {
    int start = 0;
    int end = len - 1;
    while (start < end) {
        char temp = line[start];
        line[start] = line[end];
        line[end] = temp;
        start++;
        end--;
    }
}

int main(int argc, char* argv[]) {
    char buf[MAX];
    char line[MAX];
    int desc_zrod, desc_temp;
    int lbajt;
    char desc_temp_name[] = "zadanie9_4_temp.txt";

    if (argc < 2) {
        fprintf(stderr, "\nZa malo argumentow, uzyj: ");
        fprintf(stderr, "%s <plik zrodlowy>\n\n", argv[0]);
        exit(1);
    }

    desc_zrod = open(argv[1], O_RDWR);

    if (desc_zrod == -1) {
        perror("\nBlad otwarcia pliku zrodlowego");
        printf("\n");
        exit(1);
    }

    desc_temp = open(desc_temp_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
    
    if (desc_temp == -1) {
        perror("\nBlad otwarcia pliku tymczasowego");
        printf("\n");
        exit(1);
    }

    while ((lbajt = read(desc_zrod, buf, MAX)) > 0) {
        int line_len = 0;

        for (int i = 0; i < lbajt; i++) {
            if (buf[i] == '\n') {
                line[line_len] = '\0';
                reverse_line(line, line_len);
                line_len = 0;

                if (write(desc_temp, line, strlen(line)) != strlen(line) || write(desc_temp, "\n", 1) != 1) {
                    perror("\nBlad zapisu pliku tymczasowego");
                    printf("\n");
                    exit(1);
                }
            } else {
                line[line_len++] = buf[i];
            }
        }
    }

    if (lseek(desc_zrod, 0, SEEK_SET) == -1 || lseek(desc_temp, 0, SEEK_SET) == -1) {
        perror("\nBlad ustawienia wskaznika w plikach");
        printf("\n");
        exit(1);
    }

    while ((lbajt = read(desc_temp, buf, MAX)) > 0) {
        if (write(desc_zrod, buf, lbajt) != lbajt) {
            perror("\nBlad zamiany pliku zrodlowego");
            printf("\n");
            exit(1);
        }
    }

    if (close(desc_zrod) == -1 || close(desc_temp) == -1) {
        perror("\nBlad zamkniecia pliku");
        printf("\n");
        exit(1);
    }

    if (remove(desc_temp_name) == -1) {
        perror("\nBlad usuwania pliku tymczasowego");
        printf("\n");
        exit(1);
    }

    exit(0);
}
