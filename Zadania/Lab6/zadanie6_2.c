#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

void create_user(const char *username, const char *lastname, const char *password) {
    char command[MAX_LINE_LENGTH];
    snprintf(command, sizeof(command), "net user %s %s /add", username, password);
    printf("Tworzenie uzytkownika: %s %s; haslo: %s\n", username, lastname, password);
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
        char *lastname = strtok(NULL, ";");
        char *password = strtok(NULL, ";");

        if (username != NULL && lastname != NULL && password != NULL) {
            create_user(username, lastname, password);
        } else {
            printf("Nieprawidlowy format linii: %s\n", line);
        }
    }

    printf("\n");
    fclose(file);

    return 0;
}
