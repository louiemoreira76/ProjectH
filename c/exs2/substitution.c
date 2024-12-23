#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int is_valid_key(char *key) {
    if (strlen(key) != 26) {
        return 0; // Chave deve ter exatamente 26 caracteres
    }

    int seen[26] = {0}; // Array para rastrear letras já vistas

    for (int i = 0; i < 26; i++) {
        if (!isalpha(key[i])) {
            return 0; // Apenas caracteres alfabéticos são permitidos
        }
        int index = toupper(key[i]) - 'A';
        if (seen[index] > 0) {
            return 0; // Cada letra deve aparecer exatamente uma vez
        }
        seen[index]++;
    }
    return 1; // Chave é válida
}

void encrypt(char *plaintext, char *key) {
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++) {
        if (isalpha(plaintext[i])) {
            int is_upper = isupper(plaintext[i]);
            int index = (is_upper ? plaintext[i] - 'A' : plaintext[i] - 'a');
            char cipher_char = is_upper ? toupper(key[index]) : tolower(key[index]);
            printf("%c", cipher_char);
        } else {
            printf("%c", plaintext[i]); // Mantém caracteres não alfabéticos
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    // há exatamente um argumento
    if (argc != 2) {
        printf("Uso: ./substitution chave de substituição\n");
        return 1;
    }

    char *key = argv[1];

    // Valida a chave
    if (!is_valid_key(key)) {
        printf("A chave deve conter 26 caracteres únicos e alfabéticos.\n");
        return 1;
    }

    // simples ao usuário
    printf("plaintext: ");
    char plaintext[256];
    if (fgets(plaintext, sizeof(plaintext), stdin) == NULL) {
        printf("Erro ao ler o texto.\n");
        return 1;
    }

    // Remove o caractere de nova linha do input, se presente
    plaintext[strcspn(plaintext, "\n")] = '\0';

    encrypt(plaintext, key);

    return 0;
}
