#include <stdio.h>
#include <string.h>

void conversion(char c[], int n[]);
int checking(int n[], int tam);  // Modifiquei a assinatura para incluir o tamanho

int main(void)
{
    printf("Digite seu numero de cartao de credito: ");
    char numeros[17]; // +1 nulo
    int creditCard[16];

    fgets(numeros, sizeof(numeros), stdin);
    numeros[strcspn(numeros, "\n")] = '\0';

    conversion(numeros, creditCard);
    int tam = sizeof(creditCard) / sizeof(creditCard[0]);
    // Passando o tamanho do array creditCard
    int calculo = checking(creditCard, tam);

    printf("Calculo: %d\n", calculo); // Exibe o resultado do cálculo

    return 0;
}

int checking(int n[], int tam) {  // Recebe o tamanho do array
    int cal = 0;

    for (int i = 0; i < tam; i++) {
        if (n[i] > 9)
        {
            break;
        }
        
        int digit = n[i] * 2;  // Multiplica pelo valor já convertido
        cal += digit;

        printf("Posicao: %d\n", i);
        printf("Numero: %d\n", n[i]);
    }
    return cal;
}

void conversion(char c[], int n[]) {
    int tam = strlen(c); // Usa strlen para obter o tamanho da string

    for (int i = 0; i < tam; i++) {
        n[i] = c[i] - '0'; // Converte caractere para inteiro
    }
}
