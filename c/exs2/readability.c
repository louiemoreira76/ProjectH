    #include <stdio.h>
    #include <string.h>
    #include <ctype.h>
    #include <math.h>

    char text[1000];
    const char punctuation[] = {'.', '?', '!'};

    float mediaLetras();
    float sentences();
    int contPalavras();

    int main (void){
        printf("Escreva o texto a seguir para descobir seu nível:");
        fgets(text, sizeof(text), stdin);  // fgets le o texto com espaços scanf n

        float L = (float) mediaLetras();
        float S = (float) sentences();

        double cal = 0.0588 * L - 0.296 * S - 15.8;
        int indice = (int)round(cal);

        if (indice <= 5)
        {
            indice++;
        }
        

        printf("Índice de legibilidade: %i\n", indice);
        return 0;
    }

    float mediaLetras(){
        int letras = 0;
        int totalC = contPalavras();

        for(int i = 0; text[i] != '\0'; i++){
            if (isalpha(text[i]))
            {
                letras++;
            }
        }

        float L = ((float)letras / totalC)*100;
        return L;
    }

    float sentences(){
        int sen = 0;
        int totalC = contPalavras();

        for (int i = 0; text[i] != '\0'; i++)
        {
            for(int j =0; j < 3; j++)
            {
                if (text[i] == punctuation[j])
                {
                    sen++;
                }
                
            }   
        }
        float S = ((float)sen/totalC)*100;
        return S;   
    }

    int contPalavras(){
    int palavras = 0;

    for (int i = 0; text[i] != '\0'; i++) {

        if (isspace(text[i]) && (i > 0 && !isspace(text[i - 1]))) { //qtd spaces
            palavras++;
        }
    }
    //primeiro caratere
    if (text[0] != '\0' && !isspace(text[0])) {
        palavras++;
    }

    return palavras;
    }

    //L = (NmLetras / NmCarater) * 100
    // palavras e frases mais longas provavelmente se correlacionam com níveis de leitura mais altos
    //indice = 0.0588 * L - 0.296 * S - 15.8
    //Aqui, L é o número médio de letras por 100 palavras no texto e S é o número médio de sentenças por 100 palavras no texto.
