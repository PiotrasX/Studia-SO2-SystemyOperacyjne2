#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_PATH_LENGTH 32767

// Funkcja dodająca katalog do zmiennej systemowej PATH
void add_to_path(const char* dir) {
    char path[MAX_PATH_LENGTH]; // Tablica znaków do przechowywania ścieżki zmiennej systemowej PATH
    HKEY hKey; // Zmienna do przechowywania uchwytu do klucza rejestru Windows

    // Otwarcie klucza rejestru Windows dla zmiennych środowiskowych użytkownika
    if (RegOpenKeyEx(HKEY_CURRENT_USER, "Environment", 0, KEY_READ | KEY_WRITE, &hKey) != ERROR_SUCCESS) { // Otwieranie klucza rejestru 'HKEY_CURRENT_USER\Environment' z uprawnieniami do odczytu i zapisu oraz zapisanie ich w zmiennej 'hKey' 
        fprintf(stderr, "\nBlad podczas otwierania klucza rejestru Windows!\n\n");
        return; // Błąd otwierania klucza rejestru Windows, koniec działania funkcji
    }

    DWORD pathSize = MAX_PATH_LENGTH; // Zmienna do przechowywania rozmiaru danych w zmiennej systemowej PATH
    if (RegQueryValueEx(hKey, "Path", NULL, NULL, (LPBYTE)path, &pathSize) != ERROR_SUCCESS) { // Pobranie wartości zmiennej 'Path' z klucza rejestru 'hKey' i zapisanie tych danych w tablicy 'path', a rozmiar danych w 'pathSize'
        strcpy(path, ""); // Jeśli zmienna systemowa nie istnieje, to zmienna 'path' zostaje ustawiona na pustą wartość
    }

    // Sprawdzenie, czy katalog już istnieje w zmiennej systemowej PATH
    if (strstr(path, dir) == NULL) { // Katalog nie istnieje w zmiennej systemowej PATH
        if (strlen(path) > 0 && path[strlen(path) - 1] != ';') { // Sprawdzenie czy zmienna 'path' nie jest pusta oraz czy ostatni znak zmiennej 'path' to nie średnik
            strcat(path, ";"); // Dodanie średnika na końcu, jeśli powyższe obra warunki są spełnione
        }
        strcat(path, dir); // Dodanie katalogu 'dir' to zmiennej 'path'

        // Aktualizacja zmiennej systemowej PATH w rejestrze
        if (RegSetValueEx(hKey, "Path", 0, REG_EXPAND_SZ, (const BYTE*)path, strlen(path) + 1) != ERROR_SUCCESS) { // Zapisanie zmodyfikowanej wartości zmiennej 'Path' w kluczu rejestru 'HKEY_CURRENT_USER\Environment'
            fprintf(stderr, "\nBlad podczas aktualizacji PATH w rejestrze!\n\n"); // Niepowodzenie operacji
        } else {
            printf("\nDodano katalog do zmiennej systemowej PATH: %s\n\n", dir); // Powodzenie operacji
        }
    } else { // Katalog istnieje w zmiennej systemowej PATH
        printf("\nPodany katalog juz istnieje w zmiennej systemowej PATH: %s\n\n", dir);
    }

    RegCloseKey(hKey); // Zamknięcie klucza rejestru
}

// Funkcja usuwająca katalog z zmiennej systemowej PATH
void remove_from_path(const char* dir) {
    char path[MAX_PATH_LENGTH]; // Tablica znaków do przechowywania ścieżki zmiennej systemowej PATH
    HKEY hKey; // Zmienna do przechowywania uchwytu do klucza rejestru Windows

    // Otwarcie klucza rejestru Windows dla zmiennych środowiskowych użytkownika
    if (RegOpenKeyEx(HKEY_CURRENT_USER, "Environment", 0, KEY_READ | KEY_WRITE, &hKey) != ERROR_SUCCESS) {  // Otwieranie klucza rejestru 'HKEY_CURRENT_USER\Environment' z uprawnieniami do odczytu i zapisu oraz zapisanie ich w zmiennej 'hKey'
        fprintf(stderr, "\nBlad podczas otwierania klucza rejestru Windows!\n\n");
        return; // Błąd otwierania klucza rejestru Windows, koniec działania funkcji
    }

    DWORD pathSize = MAX_PATH_LENGTH; // Zmienna do przechowywania rozmiaru danych w zmiennej systemowej PATH
    if (RegQueryValueEx(hKey, "Path", NULL, NULL, (LPBYTE)path, &pathSize) != ERROR_SUCCESS) { // Pobranie wartości zmiennej 'Path' z klucza rejestru 'hKey' i zapisanie tych danych w tablicy 'path', a rozmiar danych w 'pathSize'
        fprintf(stderr, "\nBlad podczas odczytu zmiennej systemowej PATH z rejestru!\n\n");
        RegCloseKey(hKey); // Jeśli zmienna systemowa nie istnieje, to klucz rejestru zostaje zamknięty
        return; // Klucz rejestru zamknięty, koniec działania funkcji
    }

    // Szukanie pozycji katalogu w zmiennej systemowej PATH
    char* position = strstr(path, dir); // Szukanie pierwszego wystąpienia katalogu 'dir' w zmiennej 'path'
    if (position != NULL) { // Katalog istnieje w zmiennej systemowej PATH
        size_t dir_length = strlen(dir); // Obliczenie długości katalogu
        memmove(position, position + dir_length, strlen(position + dir_length) + 1); // Przesunięcie zawartości zmiennej 'path' występującej po katalogu do usunięcia, w miejsce gdzie ten katalog się znajdował
        if (*(position - 1) == ';') { // Sprawdzenie, czy przed usuniętym katalogiem znajdował się średnik
            memmove(position - 1, position, strlen(position) + 1); // Jeśli średnik się znajdował, to ten średnik zostaje usunięty
        }

        // Aktualizacja zmiennej systemowej PATH w rejestrze
        if (RegSetValueEx(hKey, "Path", 0, REG_EXPAND_SZ, (const BYTE*)path, strlen(path) + 1) != ERROR_SUCCESS) { // Zapisanie zmodyfikowanej wartości zmiennej 'Path' w kluczu rejestru 'HKEY_CURRENT_USER\Environment'
            fprintf(stderr, "\nBlad podczas aktualizacji PATH w rejestrze!\n\n"); // Niepowodzenie operacji
        } else {
            printf("\nUsunieto katalog z zmiennej systemowej PATH: %s\n\n", dir); // Powodzenie operacji
        }
    } else { // Katalog nie istnieje w zmiennej systemowej PATH
        printf("\nPodany katalog nie istnieje w zmiennej systemowej w PATH: %s\n\n", dir);
    }

    RegCloseKey(hKey); // Zamknięcie klucza rejestru
}

// Głowna funkcja programu
int main(int argc, char* argv[]) {
    // Sprawdzenie, czy jest odpowiednia ilość argumentów
    if (argc < 2 || argc > 3) {
        printf("\nNiepoprawna skladnia polecenia, uzyj: %s <add|remove> [katalog]\n\n", argv[0]);
        return 1; // Brak odpowiedniej ilości argumentów, koniec programu
    }

    char operation[10]; // Tablica znaków, przechowująca nazwę operacji
    char directory[MAX_PATH]; // Tablica znaków, przechowująca ścieżkę katalogu

    strncpy(operation, argv[1], sizeof(operation) - 1); // Kopiowanie pierwszego argumentu przekazanego do programu do tablicy znaków 'operation'
    operation[sizeof(operation) - 1] = '\0'; // Zakończenie tablicy znaków null-terminatorem

    // Sprawdzenie, ile wynosi liczba argumentów przekazanych do programu
    if (argc == 2) { // Przekazano 2 argumenty
        if (GetCurrentDirectory(MAX_PATH, directory) == 0) { // Pobranie bieżącego katalogu, i zapisanie go do tablicy znaków 'directory'
            fprintf(stderr, "\nBlad podczas uzyskiwania biezacego katalogu!\n\n");
            return 1; // Błąd uzyskiwania biezacego katalogu, koniec programu
        }
    } else { // Przekazano 3 argumenty
        if (GetFullPathName(argv[2], MAX_PATH, directory, NULL) == 0) { // Pobranie przekazanego katalogu, zamienienie jego ścieżki względnej na bezwzględną, i zapisanie go do tablicy znaków 'directory'
            fprintf(stderr, "\nBlad podczas rozpoznawania przekazanego katalogu!\n\n");
            return 1; // Błąd rozpoznawania przekazanego katalogu, koniec programu
        }
    }

    // Sprawdzenie, jaka operacja została wywołana
    if (strcmp(operation, "add") == 0) { // Operacja dodawania 'add'
        add_to_path(directory); // Wywołanie funkcji dodającej katalog do zmiennej systemowej PATH
    } else if (strcmp(operation, "remove") == 0) { // Operacja usuwania 'remove'
        remove_from_path(directory); // Wywołanie funkcji usuwającej katalog z zmiennej systemowej PATH
    } else { // Nieprawidłowa operacja
        fprintf(stderr, "\nNieprawidlowa operacja: %s\n\n", operation);
        return 1; // Użycie nieprawidłowej operacji, koniec programu
    }

    return 0; // Program pomyślnie zakończył swoje działanie
}
