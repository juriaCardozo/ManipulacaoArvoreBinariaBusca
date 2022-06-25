#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
// ---------------------------------------
// ---------------------------------------

// PtrNoArvore = NoArvore* -> PtrNoArvore
typedef struct NoArvore *PtrNoArvore;

// Struct Nó de Árvore
typedef struct NoArvore{
    char palavra[40];
    int paginas[15];
    PtrNoArvore direita;
    PtrNoArvore esquerda;
} NoArvore;
// ---------------------------------------
// ---------------------------------------

// Função que inicia a árvore
void iniciaArvoreBinaria(PtrNoArvore *r){
    (*r) = NULL;
}
// ---------------------------------------
// ---------------------------------------

// Função que insere as palavras de busca do arquivo de entrada na árvore
bool inserirArvoreBinaria(PtrNoArvore *no, char *palavra){
    
    //Alocação dinâmica do nó de árvore e inserção da palavra no nó de árvore
    if ((*no) == NULL){
        (*no) = malloc(sizeof(NoArvore));
        strcpy((*no)->palavra, palavra);
        (*no)->direita = NULL;
        (*no)->esquerda = NULL;
        // Inserção de -1 no vetor do nó de árvore para controlar as posições para inserir o número da página em que a palavra for encontrada
        for (int k = 0; k < 15; k++){
            (*no)->paginas[k] = -1;
        }
        return (true);
    }

    // Caso o valor a ser inserido já esteja na árvore
    if (strcmp((*no)->palavra, palavra) == 0){
        return (false);
    }

    // Função recursiva para inserção na árvore que retorna enquanto os nós não forem nulos
    if (strcmp(palavra, (*no)->palavra) == 1){
        return (inserirArvoreBinaria(&(*no)->direita, palavra));
    } else{
        return (inserirArvoreBinaria(&(*no)->esquerda, palavra));
    }
}
// ---------------------------------------
// ---------------------------------------

// Função que imprime as palavras da árvore em ordem no arquivo de saída
void EmOrdemArvoreBinaria(PtrNoArvore* no, FILE* saida){
    
    // Caso o nó seja nulo, a função para
    if ((*no) == NULL){
        return;
    }
    
    // Imprime no arquivo de saída a palavra do nó mais a esquerda da árvore, pois é em ordem, ou seja, da esquerda para a direita
    EmOrdemArvoreBinaria(&(*no)->esquerda, saida);
    printf("%s", (*no)->palavra);
    fprintf(saida, "%s", (*no)->palavra);

    for (int k = 0; k < 15; k++){
        // Caso a posição do vetor seja diferente de -1, ou seja, tenha o número da página que a palavra do nó foi encontrada, ele imprime no arquivo de saída
        if ((*no)->paginas[k] != -1){
            printf(",%d", (*no)->paginas[k]);
            fprintf(saida, ",%d", (*no)->paginas[k]);
        }
    }
    printf("\n");
    fprintf(saida, "\n");

    // Manda de volta para a função o nó à direita do que foi impresso acima
    EmOrdemArvoreBinaria(&(*no)->direita, saida);
}
// ---------------------------------------
// ---------------------------------------

// Função de pesquisa das palavras na árvore
bool pesquisaArvoreBinaria(PtrNoArvore *no, char buscar[40], int pag){
    
    // Caso o nó da árvore seja nulo, a função para
    if ((*no) == NULL){
        return false;
    }
    
    // Caso a palavra do nó da árvore seja igual a palavra que está sendo enviada para ser buscada, 
    // é inserido no vetor do nó da árvore o número da página que a palavra foi encontrada
    if (strcmp((*no)->palavra, buscar) == 0){

        // Contador para controlar se a palavra foi encontrada na mesma página 
        int inseriu = 0;
        //
        for (int k = 0; k < 15; k++){
            if ((*no)->paginas[k] == -1){
                for (int l = 0; l < k; l++){
                    // Se a palavra já foi inserida, o contador é incrementado
                    if ((*no)->paginas[l] == pag){
                        inseriu++;
                    }
                }
                // Se a palavra não foi inserida, ela é inserida no vetor
                if (inseriu == 0 && k != 0){
                    (*no)->paginas[k] = pag;
                }
            }
        }
        return (true);
    }

    // Se não for igual, ele retorna os outros nós para a função
    if (strcmp(buscar, (*no)->palavra) == 1){
        return (pesquisaArvoreBinaria(&(*no)->direita, buscar, pag));
    } else{
        return (pesquisaArvoreBinaria(&(*no)->esquerda, buscar, pag));
    }
}
// ---------------------------------------
// ---------------------------------------
int main(int argc, const char *argv[]){
    
    // Verificando a quantidade de parâmetros
    if (argc != 3){
        printf("Quantidade de parametros invalida\n");
        return 0;
    }

    // Abertura dos arquivos
    FILE *entrada = fopen(argv[1], "r");
    FILE *saida = fopen(argv[2], "w");

    // Verificando a abertura dos arquivos
    if (entrada == NULL || saida == NULL){
        printf("Erro: algum dos arquivos não pode ser criado corretamente\n");
        return 0;
    }

    // Verificando se o arquivo está vazio
    char teste;
    if ((teste = fgetc(entrada)) == EOF){
        printf("Erro: Arquivo inválido\n");
        fprintf(saida, "Erro: Arquivo inválido");
        return 0;
    }

    // Retornando para o começo do arquivo
    rewind(entrada);

    // Declarando e iniciando a árvore
    PtrNoArvore raiz;
    iniciaArvoreBinaria(&raiz);

    // Declaração de variáveis
    char linha[200];
    int virgulas = 0, i = 0;
    int linhaAtual = 0;

    // Pegando os termos a serem buscados do arquivo de entrada
    fgets(linha, 200, entrada);
    linhaAtual++;

    // Contando a quantidade de vírgulas da primeira linha para saber a quantidade de termos a serem inseridos na árvore
    for (i = 0; i != strlen(linha); i++){
        if (linha[i] == ','){
            virgulas++;
        }
    }

    // Separando os termos da primeira linha a serem buscados com strtok e inserindo as palavras de busca na árvore
    char *pch;
    int atual = 0;
    int qntDados = virgulas + 1;
    pch = strtok(linha, ":,>");
    while (pch != NULL){
        pch = strtok(NULL, ":,>");
        if (atual < qntDados){
            atual++;
            *pch = tolower((char)*pch);
            inserirArvoreBinaria(&raiz, pch);
        }
    }

    // Contando quantas páginas tem o arquivo de entrada e se tem páginas sem conteúdo
    int j = 0;
    int qtdePgs = 0;
    while (fgets(linha, 200, entrada) != !EOF){
        linhaAtual++;
        for (j = 0; j < strlen(linha); j++){
            if (linha[j] == 60){
                qtdePgs++;
                fgets(linha, 200, entrada);
                if (linha[0] == 60){
                    rewind(entrada);
                    int k;
                    for (k = 0; k < linhaAtual; k++){
                        fgets(linha, 200, entrada);
                    }
                } else{
                    linhaAtual++;
                }
            }
        }

        // Mandando as palavras da árvore para serem pesquisadas nas páginas
        char *wordTxt;
        wordTxt = strtok(linha, " ,.:()\n");
        while (wordTxt != NULL){
            *wordTxt = tolower((char)*wordTxt);
            pesquisaArvoreBinaria(&raiz, wordTxt, qtdePgs);
            wordTxt = strtok(NULL, " ,.:()\n");
        }
    }

    // Imprimindo a as palavras dos nós das árvores e as páginas que foram econtradas em ordem no arquivo de saída
    EmOrdemArvoreBinaria(&raiz, saida);
    
    // Fechando os arquivos que foram abertos
    fclose(entrada);
    fclose(saida);

    return 0;
}