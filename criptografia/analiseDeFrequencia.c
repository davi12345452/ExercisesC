// Aluno: Davi Janisch Maia

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

// Definindo a estrutura, para análise de 1 letra
typedef struct Letra {
    int freq;
    char letra;
} letra;

/*
    Nessa função, há a cifra de argumento, armazenando a letra e sua frequência
    dentro de um vetor da estrutura letra. No final, o programa ainda ajusta e
    ordena de forma decrescente de acordo com a frequencia.
*/

letra *calcularFrequencia(char *cifra) {
    letra *freq_tabela = (letra *) malloc(ALPHABET_SIZE * sizeof(letra));
    int i, j;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        freq_tabela[i].freq = 0;
        freq_tabela[i].letra = i + 'a';
    }

    for (i = 0; cifra[i] != '\0'; i++) {
        if (isalpha(cifra[i])) {
            freq_tabela[tolower(cifra[i]) - 'a'].freq++;
        }
    }

    for (i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (j = 0; j < ALPHABET_SIZE - i - 1; j++) {
            if (freq_tabela[j].freq < freq_tabela[j + 1].freq) {
                letra temp = freq_tabela[j];
                freq_tabela[j] = freq_tabela[j + 1];
                freq_tabela[j + 1] = temp;
            }
        }
    }

    return freq_tabela;
}


/*
    Nessa função, há o armazenamento da letras e suas frequencias 
    dentro de um arquivo, como solicitado, ignorando letras com 0
    frequencia. 
*/
int imprimeValores (letra *freq_tabela, char *nomeArquivo){

    //Abre o arquivo
    FILE *file = fopen(nomeArquivo, "w");

    if (file == NULL) {
        printf("Erro ao criar o arquivo.");
        return 1;
    }

    // Escreve a tabela de frequência no arquivo
    int i;
    fprintf(file, "Tabela de frequencia para cada caracteres:\n");
    fprintf(file, "-------------------\n");
    for (i = 0; i < ALPHABET_SIZE; i++) {
        if(freq_tabela[i].freq != 0){
            fprintf(file, "| %c ----> %d Vezes |\n", freq_tabela[i].letra, freq_tabela[i].freq);
        }
    }
    fprintf(file, "-------------------\n");
    // Fecha o arquivo
    fclose(file);
}

int main() {
    char cifra[] = "HQKQWTFLCGETRTEGROYOEGXQDTFLQUTDLTEKTZQ";

    letra *freq_tabela = calcularFrequencia(cifra);

    imprimeValores(freq_tabela, "tabela.txt");

    // Libera a memória alocada para a tabela de frequência
    free(freq_tabela);

    return 0;
}
