#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define MAX_WORDS 1000  // Adjust if needed
#define MAX_WORD_LENGTH 100 
#define ANSI_COLOR_GREEN    "\e[0;32m"
#define ANSI_COLOR_RESET    "\x1b[0m"
#define ANSI_COLOR_RED     	"\x1b[31m"



int main(void) {
    setlocale(LC_ALL, "");

    FILE *arq;
    char words[MAX_WORDS][MAX_WORD_LENGTH]; 
    char frases[1000], *linha;
    int numWords = 0;

    srand(time(NULL));

    arq = fopen("../palavras.nao.bastam.txt", "r");

    if (arq == NULL) {
        printf("Nao foi possivel ler o arquivo!\n");
        return 1;
    }

    // Read all words into the 'words' array
    while (fgets(frases, sizeof(frases), arq) != NULL) {
        linha = strdup(frases);
        linha[strcspn(linha, "\n")] = '\0';
        strcpy(words[numWords], linha);
        numWords++;
        free(linha); 
    }

    fclose(arq); // Close the file

    int nivel = 0;

    printf("Escolha o nivel de dificuldade:\n");
    printf("1. Facil (ate 5 letras)\n");
    printf("2. Medio (6 a 7 letras)\n");
    printf("3. Dificil (8 ou mais letras)\n");
    printf("Digite o numero correspondente ao nivel: ");
    scanf("%d", &nivel);
    getchar();

    if (nivel < 1 || nivel > 3) {
        printf("Nivel de dificuldade invalido!\n");
        return 1;
    }

    int qntdLetra1, qntdLetra2;

    if (nivel == 1) {
        qntdLetra1 = 1;
        qntdLetra2 = 5;
    }
    if (nivel == 2) {
        qntdLetra1 = 6;
        qntdLetra2 = 7;
    }
    if (nivel == 3) {
        qntdLetra1 = 8;
        qntdLetra2 = 20;
    }
    
    char resposta[1000];
    int d = 0;
    int count = 0;
    while (d == 0) {
        // Find a word that meets the difficulty criteria
        int randomIndex;
        do {
            randomIndex = rand() % numWords;
            count = strlen(words[randomIndex]);
        } while (count < qntdLetra1 || count > qntdLetra2);

        // Copy the selected word into 'linha'
        strcpy(linha, words[randomIndex]);

        strcpy(resposta, linha);

        // Shuffle the letters in 'linha'
        for (int i = 0; i < 200; i++) {
            char cache;
            int y = rand() % count;
            int z = rand() % count;
            cache = linha[y];
            linha[y] = linha[z];
            linha[z] = cache;
        }
        d = 1;
    }
    d = 0;

    int points = 100, lose;


    printf("vc tem 100 de vida\n");
    printf("quantos pontos de vida vc quer perder a cada erro?");
    scanf("%d", &lose);
    getchar();


    while (d == 0){

        if (points > 1){

            printf("\nAnagrama = %s\n", linha);
            char chute[1000];
            printf("R: ");

            fgets(chute, sizeof(chute), stdin);
            chute[strcspn(chute, "\n")] = '\0';

            if (strcmp(chute, resposta) == 0) {
                d = 1;
                printf("\nParabens, voce ganhou!\n\n");
                printf("       ___________      \n");
                printf("      '._==_==_=_.'     \n");
                printf("      .-\\:      /-.    \n");
                printf("     | (|:.     |) |    \n");
                printf("      '-|:.     |-'     \n");
                printf("        \\::.    /      \n");
                printf("         '::. .'        \n");
                printf("           ) (          \n");
                printf("         _.' '._        \n");
                printf("        '-------'       \n\n");
            } else {
                points -= lose;
                if ((points < 1)){
                }
                else{
                    printf("\n");
                    for (int i = 0; i<count;i++){
                        if (chute[i] == resposta[i]){
                            printf(ANSI_COLOR_GREEN "%c " ANSI_COLOR_RESET, chute[i]);
                        }
                        else{
                            printf(ANSI_COLOR_RED "%c " ANSI_COLOR_RESET, chute[i]);
                        }
                    }
                    printf("\n");

                    printf("\nChute errado, tente novamente.\n");
                    printf("vc esta com %i pontos de vida\n", points);
                }
            }
        }
        else{
            printf("\nessa eh a resposta: %s\n", resposta);
            printf("\n\t\tvc perdeu :(");
            d = 1;
        }
    }

    return 0;
}