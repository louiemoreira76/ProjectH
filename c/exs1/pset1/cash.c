#include <stdio.h>
#include <math.h>

int main() {
    printf("Quanto dinheiro estamos te devendo: ");
    float troco;
    int moedas = 0;

 
    while (1) {
        if (scanf("%f", &troco) == 1) {
            if (troco > 0.0) {
                break; 
            } else {
                printf("Valor deve ser positivo. Tente novamente: ");
            }
        } else {
            printf("Entrada inválida. Tente novamente: ");
            while (getchar() != '\n');  // Limpa o buffer de entrada
        }
    }
    
    int centavos = round(troco * 100);
    printf("%d\n",centavos);
    while(centavos >= 0.25){    
        if(centavos < 25){
            break;
        }
        centavos -= 25;
        moedas++;
            printf("%d\n",centavos);
    
    }
    while(centavos >= 0.10){
        if(centavos <10){
            break;
        }
        centavos -= 10;
        moedas++;
            printf("%d\n",centavos);
    }
    while(centavos >= 0.05){
        if(centavos < 5){
            break;
        }
        centavos -= 5;
        moedas++;
            printf("%d\n",centavos);
    }
       while (centavos >= 1) {
           if(centavos < 1){
            break;
        }
        centavos -= 1;
        moedas++;
            printf("%d\n",centavos);
    }

    printf("Número total de moedas: %d\n", moedas);

    return 0;
    
}