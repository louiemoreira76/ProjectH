#include <stdio.h>

int main() {
    int tam;

    // Solicita ao usuário o tamanho da pirâmide
    printf("Qual o tamanho da pirâmide? ");
    while (scanf("%d", &tam) != 1 || tam < 1 || tam > 8) {
        // Limpa o buffer de entrada se a entrada for inválida
        while (getchar() != '\n');
        printf("Entrada inválida. Insira um número entre 1 e 8: ");
    }

    // Cria a pirâmide
    for (int i = 0; i < tam; i++) {
        // Imprime espaços à esquerda
        for (int j = 0; j < tam - i - 1; j++) {
            printf(" ");
        }
        // Imprime os caracteres #
        for (int k = 0; k <= i; k++) {
            printf("#");
        }
        // Nova linha após cada linha da pirâmide
        printf("\n");
    }

    return 0;
}
