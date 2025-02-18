#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int cyfry1(int liczba) {
    if (liczba == 0) return 1;
    return (int)log10(abs(liczba)) + 1;
}

int cyfry2(int liczba) {
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "%d", abs(liczba));
    return strlen(buffer);
}

int cyfry3(int liczba) {
    if (liczba == 0) return 1;
    int licznik = 0;
    while (liczba != 0) {
        liczba /= 10;
        licznik++;
    }
    return licznik;
}

int main() {
    int liczba = -1337;

    printf("\ncyfry1(%d) = %d", liczba, cyfry1(liczba));
    printf("\ncyfry2(%d) = %d", liczba, cyfry2(liczba));
    printf("\ncyfry3(%d) = %d\n\n", liczba, cyfry3(liczba));

    return 0;
}
