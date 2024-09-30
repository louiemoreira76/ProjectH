#include <ctype.h>
#include <stdio.h>
#include <string.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(char l[]);

int main(void) {

    char word1[100];
    char word2[100];

    printf("Player 1: ");
    scanf("%99s", word1);  // Limitar a entrada para evitar estouro de buffer

    printf("Player 2: ");
    scanf("%99s", word2);

    int pontos1 = compute_score(word1);
    int pontos2 = compute_score(word2);

    if (pontos1 > pontos2) {
        printf("Player 1 Ganhou!\n");
    } else if (pontos1 < pontos2) {
        printf("Player 2 Ganhou!\n");
    } else {
        printf("Os Dois Players Empataram!\n");
    }

    return 0;
}

int compute_score(char l[]) {
    int pontos = 0;

    for (int i = 0; l[i] != '\0'; i++) {
        // Converte para minúsculo
        l[i] = tolower(l[i]);

        // Verifica se o caractere é uma letra atraves do ASCII
        if (l[i] >= 'a' && l[i] <= 'z') {
            int index = l[i] - 'a';  // Encontra o índice no alfabeto (0 para 'a', 25 para 'z')
            pontos += POINTS[index]; 
        }
    }

    return pontos;
}
