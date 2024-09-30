#include <stdio.h>

#include <stdbool.h>
#include <math.h>
//get int depois
int main(void){
    bool end = false;
    int anos = 0;


    printf("Qual o número incial que a polulação começa:");
    int inicial;
    scanf("%i", &inicial);
    printf("Qual o número final que a população firaca:");
    int final;
    scanf("%i", &final);
    while (end == false)
    {
        anos++;
        
        float cal1 = (float)inicial/3; //evitar truncamento
        float cal2 = (float)inicial/4; //evitar truncamento

        int value1 = round(cal1);
        int value2 = round(cal2);

        int estimate = (inicial + value1) - value2;
        printf("%d", estimate);
        inicial = estimate;

        if ( estimate >= final)
        {
            end = true;
            break;
        }
    }
    printf("Years: %d", anos);
}
// Start size: 100
// End size: 200
// Years: 9