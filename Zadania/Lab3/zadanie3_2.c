#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Zadanie 3.2.1

    /*
                       index
                       |
             0    1    2    3    4       indexes
    str -> ['9']['9']['$'][' ']['\0']
           |         |
           str       ptr                 pointers
    */

int indexOf(const char *str, int c) {
    const char *ptr = str;
    while (*ptr != '\0') {
        if (*ptr == (char)c) {
            return ptr - str;
        }
        ptr++;
    }
    return -1;
}

// Koniec zadania 3.2.1



// Zadanie 3.2.2

char *identity(const char *name, const char *surname){
    char *result = malloc(strlen(name) + strlen(surname) + 2);
    if (result == NULL) return NULL;

    strcpy(result, name);
    strcat(result, " ");
    strcat(result, surname);
    return result;
}

// Koniec zadania 3.2.2



// Zadanie 3.2.3

char *login(const char *name, const char *surname) {
    char *login = (char *)malloc(33 * sizeof(char));
    if (login == NULL) return NULL;

    snprintf(login, 33, "%c%s", name[0], surname);
    login[32] = '\0';
    return login;
}

// Koniec zadania 3.2.3



int main() {
    const char str[] = "Ala ma kota";
    int index = indexOf(str, 't');
    printf("\nIndeks znaku 't': %d\n", index);

    char *name = "Jan";
    char *surname = "Kowalski";
    char *id = identity(name, surname);
    printf("Imie i nazwisko: %s\n", id);
    free(id);

    char *userLogin = login(name, surname);
    printf("Login uzytkownika: %s\n\n", userLogin);

    return 0;
}
