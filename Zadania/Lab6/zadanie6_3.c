#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

void delete_user(const char *username) {
    char command[MAX_LINE_LENGTH];
    snprintf(command, sizeof(command), "net user %s /delete", username);
    printf("Usuwanie uzytkownika: %s\n", username);
}

int main() {
    FILE *file = fopen("baza.txt", "r");

    if (file == NULL) {
        perror("\nBlad przy ladowaniu pliku");
        printf("\n");
        return 1;
    }

    printf("\n");
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\r\n")] = 0;

        char *username = strtok(line, ";");

        if (username != NULL) {
            delete_user(username);
        } else {
            printf("Nieprawidlowy format linii: %s\n", line);
        }
    }

    printf("\n");
    fclose(file);

    return 0;
}
