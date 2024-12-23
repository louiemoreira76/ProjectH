#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    char name[50];
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(char *name);
void print_winner(void);

int main(int argc, char *argv[]) // argc representa o num de argumentos passados na linha de comando.argv É um array de strings onde cada elemento é um argumento.
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1; //excluindo o nome do programa ./plurality
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i].name, argv[i + 1]);
        candidates[i].votes = 0;
    }

    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);
    getchar(); // Consome o '\n' residual

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        char name[50];
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(char *name)
{
    for (short i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        } 
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Variáveis auxiliares
    int maxVotes = 0;
    int empateCount = 0;

    // Encontra o número máximo de votos
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > maxVotes)
        {
            maxVotes = candidates[i].votes;
        }
    }

    // Verifica quantos candidatos têm o número máximo de votos
    char empate[50][50]; // Array para armazenar os nomes dos candidatos empatados
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == maxVotes)
        {
            strcpy(empate[empateCount], candidates[i].name); // Copia o nome para o array de empate
            empateCount++;
        }
    }

    // Exibe o resultado com base no número de candidatos empatados
    if (empateCount > 1)
    {
        printf("EMPATE entre os seguintes candidatos:\n");
        for (int i = 0; i < empateCount; i++)
        {
            printf("%s\n", empate[i]);
        }
    }
    else
    {
        printf("O vencedor é:\n");
        printf("%s\n", empate[0]);
    }
}
//./plurality Alice Bob Charlie