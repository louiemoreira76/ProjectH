#include <stdio.h>
#include <stdlib.h> 
#include "getInputs/String.h" // Incluímos o cabeçalho para usar a função
#include "getInputs/Int.h"

int main() {
    printf("Digite uma string: ");
    char* userInput = get_string();
    printf("Voce digitou: %s\n", userInput);
    
    // Libera a memória alocada
    free(userInput);

    int n = get_int();
    printf("%d", n);

    return 0;
}