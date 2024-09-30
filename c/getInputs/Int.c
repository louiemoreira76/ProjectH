#include <stdio.h>
#include <limits.h>  // Para INT_MAX e INT_MIN

int get_int() {
    int number_input;

    while (1) {
        printf("Digite um número inteiro: ");
        if (scanf("%d", &number_input) == 1 && scanf("%d", &number_input) < 0) {
            // Verificação se o número está dentro dos limites típicos de um int
            if (number_input >= INT_MIN && number_input <= INT_MAX) {
                break;  // Sai do loop se a leitura e a verificação forem bem-sucedidas
            } else {
                printf("Número fora dos limites de 32 bits. Tente novamente.\n");
            }
        } else {
            printf("Entrada inválida. Tente novamente.\n");
            while (getchar() != '\n');  // Limpa o buffer de entrada
        }
    }

    return number_input;
}
