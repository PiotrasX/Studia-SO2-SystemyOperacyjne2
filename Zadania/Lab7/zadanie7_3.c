#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("\nNie podano zadnych argumentow!\n\n");
        return 1;
    }
 
    char command[1024] = "";
    #if defined(_WIN32) || defined(_WIN64)
        strcpy(command, "dir ");
    #else
        strcpy(command, "ls ");
    #endif
 
    for (int i = 1; i < argc; i++) {
        strcat(command, argv[i]);
        strcat(command, " ");
    }
 
    int result = system(command);
    if (result == -1) {
        printf("\nBlad przy wywolywaniu komendy!\n\n");
        return 1;
    } else if (result == 0) {
        printf("\nKomenda zakonczona sukcesem!\n\n");
    } else {
        printf("\nKomenda zakonczona z bledem. Kod bledu: %d\n\n", result);
    }
 
    return 0;
}
