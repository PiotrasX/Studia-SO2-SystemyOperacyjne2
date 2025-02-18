#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    const char *childMessage = "Proces potomny\n";       // Wiadomość dla procesu potomnego
    size_t childMsgLen = strlen(childMessage);           // Długość wiadomości procesu potomnego
    const char *parentMessage = "Proces macierzysty\n";  // Wiadomość dla procesu macierzystego
    size_t parentMsgLen = strlen(parentMessage);         // Długość wiadomości procesu macierzystym

    // Wrapper syscall vfork
    pid_t pid = vfork();

    // Sprawdzenie, czy proces jest rodzicem czy dzieckiem (ewentualnie błąd przy wywołaniu vfork)
    if (pid < 0) {
        // Błąd przy wywołaniu vfork
        
        perror("Blad przy wywolaniu vfork");  // Obsługa błędu, jeśli wywołanie vfork się nie powiodło
        return 1;                             // Zwrot kodu błędu
    } else if (pid == 0) {
        // Wyświetlenie komunikatu dla procesu potomnego

		// Zapis wiadomości na standardowe wyjście (wypisanie w terminalu)
        ssize_t bytes_written = write(STDOUT_FILENO, childMessage, childMsgLen);

        if (bytes_written == -1) {                   
            perror("write");  // Obsługa błędu, jeśli zapis się nie powiódł
            _exit(1);         // Zakończenie procesu potomnego z błędem
        }

        _exit(0);  // Zakończenie procesu potomnego z sukcesem
    } else {
        // Wyświetlenie komunikatu dla procesu macierzystego
		
		// Zapis wiadomości na standardowe wyjście (wypisanie w terminalu)
        ssize_t bytes_written = write(STDOUT_FILENO, parentMessage, parentMsgLen);

        if (bytes_written == -1) {
            perror("write");  // Obsługa błędu, jeśli zapis się nie powiódł
            return 1;         // Zwrot kodu błędu
        }

        return 0;   // Sukces w procesie macierzystym
    }
}
