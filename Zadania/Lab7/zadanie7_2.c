#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Wartość zmiennej argc
    printf("\nargc = %d\n\n", argc);
 
    // Adres programu
    printf("addr: %s\n\n", argv[0]);
 
    // Nazwa programu
    char *program_name = argv[0];
    char *last_slash = strrchr(program_name, '\\');
    if (last_slash) {
        program_name = last_slash + 1;
    }
    printf("name: %s\n\n", program_name);
 
    // Przekazane parametry
    printf("params:");
    for (int i = 1; i < argc; i++) {
        printf(" %s", argv[i]);
    }
    printf("\n\n");
 
    return 0;
}
