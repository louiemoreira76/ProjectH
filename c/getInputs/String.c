#include <stdio.h> //bibliresponsável pelas operações de entrada e saída, como usar printf e fgets
#include <stdlib.h>//alocação dinâmica de memória (usamos malloc e free) e para a função exit (caso ocorra erro de alocação de memória).
#include <string.h>//Fornece funções para manipulação de strings, como strlen (para obter o comprimento da string) e strcpy (para copiar strings).

#include "String.h"

#define BUFFER_SIZE 100//Define valor constante, é temporário e serve para capturar a string do usuário antes de alocarmos memória dinamicamente.

// Função para capturar uma string do usuário
char* get_string() {
    char buffer[BUFFER_SIZE];  // Buffer temporário para armazenar a string
    fgets(buffer, BUFFER_SIZE, stdin);  //b = local onde a string capturada será armazenada B = O número máximo de caracteres a serem lidos s = Indica que a entrada está vindo do teclado
    
    
    size_t length = strlen(buffer);//Essa função retorna o comprimento da string, ou seja, quantos caracteres estão na string
    if (buffer[length - 1] == '\n') { //usuário pressiona "Enter"
        buffer[length - 1] = '\0'; //nulo (\0)
    }

    //malloc: Esta função aloca memória dinamicamente. Ela recebe como argumento o número de bytes a serem alocados
    char* result = (char*)malloc((length + 1) * sizeof(char)); //+1 = \0 sizeof =O tamanho de um caractere em bytes(1 byte)
    
    if (result == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    
    // Copia o conteúdo do buffer para a nova string
    strcpy(result, buffer);

    return result;
}