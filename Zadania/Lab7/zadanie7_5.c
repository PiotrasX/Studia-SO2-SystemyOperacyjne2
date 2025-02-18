#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Windows
int main() {
    #ifdef _MSC_VER
    printf("\nSposob 1: MSC Version -> %d", _MSC_VER);
    #else
    printf("\nSposob 1: MSC Version -> Not defined");
    #endif

    #ifdef _MSC_FULL_VER
    printf("\nSposob 2: MSC Full Version -> %d", _MSC_FULL_VER);
    #else
    printf("\nSposob 2: MSC Full Version -> Not defined");
    #endif

    #ifdef __cplusplus
    printf("\nSposob 3: C++ Standard Version -> %ld\n\n", __cplusplus);
    #else
    printf("\nSposob 3: C++ Standard Version -> Not defined\n\n");
    #endif
    
    return 0;
}

// // Linux
// int main() {
//     printf("\nSposob 1: glibc version -> %s", gnu_get_libc_version());
//
//     FILE *fp = fopen("/proc/version", "r");
//     if (fp != NULL) {
//         char buffer[1024];
//         if (fgets(buffer, sizeof(buffer), fp) != NULL) {
//             printf("\nSposob 2: Kernel version -> %s", buffer);
//         }
//         fclose(fp);
//     } else {
//         printf("\nSposob 2: Kernel version -> Cannot open file /proc/version");
//     }
//
//     // Metoda 3: Użycie system i ldd do uzyskania wersji ldd
//     printf("\nSposób 3: ldd version -> ");
//     system("ldd --version | grep ldd");
//     printf("\n\n");
//
//     return 0;
// }
