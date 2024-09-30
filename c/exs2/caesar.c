#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char* cryptography(char m[], short key); 
int cesar(int decimal, short key); 
short get_key(void); 

int main(void) {
    printf("Forneça a chave de criptografia: ");
    short chave = get_key();  

    char msg[100];
    printf("Digite a palavra que deseja criptografar: ");
    
    fgets(msg, sizeof(msg), stdin);
    
    // Remove o '\n' do final da string lida por fgets
    msg[strcspn(msg, "\n")] = '\0';

    char* crypto = cryptography(msg, chave);    

    printf("Original: %s\n", msg);
    printf("Criptografado: %s\n", crypto);
    
    return 0;
}   

char* cryptography(char m[], short key) { 
    for (int i = 0; m[i] != '\0'; i++) {
        if (isupper(m[i])) {
            int letra = m[i] - 'A';
            int crito = cesar(letra, key);
            m[i] = 'A' + crito;  
        }
        else if (islower(m[i])) {
            int letra = m[i] - 'a';
            int crito = cesar(letra, key); 
            m[i] = 'a' + crito;  
        }
    }
    return m;  
}

int cesar(int decimal, short key) { 
    return (decimal + key) % 26; 
}

short get_key(void) {
    short k;
   while (1)
   {
     if (scanf("%hd", &k) != 1)
    {
        printf("Entrada invalida tente novamente!");
        while (getchar() != '\n'); //limpa buffer
    }
    else if (k < 0 || k > 26)
    {
        printf("Chave de criptogracao invalida");
    }
    else{
        break;
    }
   }
    getchar(); // Limpa o buffer após a leitura da chave
    return k;
}
