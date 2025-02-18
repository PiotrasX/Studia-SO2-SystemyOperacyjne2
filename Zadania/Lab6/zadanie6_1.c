#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* xor_encrypt(const char* key, const char* salt, char* output) {
    int key_len = strlen(key);
    int salt_len = strlen(salt);

    for (int i = 0; i < key_len; i++) {
        output[i] = (key[i] ^ salt[i % salt_len]) % 94 + 32;
    }
    output[key_len] = '\0';

    return output;
}

int main() {
    char password[] = "password";
    char salt[] = "key";
    char encrypted[50];
    char decrypted[50];

    xor_encrypt(password, salt, encrypted);
    xor_encrypt(encrypted, salt, decrypted);

    printf("\n Password: %s\n", password);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n\n", decrypted);

    return 0;
}
