#include <stdio.h>
#include <string.h>

void conversion(char c[], int n[]);
int checking(int n[]);

int main(void)
{
    printf("Digite seu numero de cartao de credito: ");
    char numeros[17]; //+1 nulo
     int creditCard[16];

    fgets(numeros, sizeof(numeros), stdin);
    numeros[strcspn(numeros, "\n")] = '\0';

    conversion(numeros, creditCard);

    int calculo = checking(numeros);

    return 0;
}

int checking(int n[]){
    int cal = 0;
    int tam = sizeof(n) / sizeof(n[0]);

    for(int i = 0; i < 16; i++){
        int digit = n[i] * 2;
        cal+=digit;
        
        printf("Posicao: %d\n", i);
        printf("Numero: %d\n", n[i]); // Corrige a falta de ponto e vírgula
    } 
    return cal;
}

void conversion(char c[], int n[])
{
    int tam = sizeof(c) / sizeof(c[0]);

    for(int i = 0; i < tam; i++){
        n[i] = c[i] - '0';
    }

}