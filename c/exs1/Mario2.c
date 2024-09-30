#include <stdio.h>

int main() {
   int tam;

    // Solicita o tamanho da pirâmide
    printf("Qual o tamanho da pirâmide? ");
    while (scanf("%d", &tam) != 1 || tam < 1 || tam > 8) {
        // Limpa o buffer de entrada e solicita a entrada novamente
        while (getchar() != '\n');
        printf("Entrada inválida. Insira um número entre 1 e 8: ");
    }
    
    for(int i = 0; i < tam; i++){
        
       for (int j = 0; j < tam - i - 1; j++) {
            printf(" ");
        }
        
        for (int k = 0; k <= i; k++) {
            printf("#");
        }
        
        printf(" ");
        
        for (int k = 0; k <= i; k++) {
            printf("#");
        }
        
        printf("\n");
    }
}