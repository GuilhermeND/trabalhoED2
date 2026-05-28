#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "arvore.h"
#include "pilha.h"
#include "matematica.h"

int main() {

    int continuar = 1;
    int quantidade = 0;
    int tamanho = 10;

    char **expressoes = NULL;
    char **expressoesOriginais = NULL;
    TreeNode **arvores = NULL;
    float *resultados = NULL;
    int *validos = NULL;

    while (continuar) {

        Pilha pilhaOperadores;
        initPilha(&pilhaOperadores);

        printf("\nDigite sua expressao: ");

        char *str = userInput(tamanho);

        char *original = strdup(str);

        str = ordenadora(str, &pilhaOperadores);

        TreeNode *arvore = inserirExpressao(str);

        float resultado = 0;

        int valido = calcularExpressao(arvore, &resultado);

        quantidade++;

        expressoes = realloc(expressoes, quantidade * sizeof(char *));
        expressoesOriginais = realloc(expressoesOriginais, quantidade * sizeof(char *));
        arvores = realloc(arvores, quantidade * sizeof(TreeNode *));
        resultados = realloc(resultados, quantidade * sizeof(float));
        validos = realloc(validos, quantidade * sizeof(int));

        if (
            expressoes == NULL ||
            expressoesOriginais == NULL ||
            arvores == NULL ||
            resultados == NULL ||
            validos == NULL
        ) {

            printf("\nErro de memoria\n");

            return 1;
        }

        expressoes[quantidade - 1] = str;
        expressoesOriginais[quantidade - 1] = original;
        arvores[quantidade - 1] = arvore;
        resultados[quantidade - 1] = resultado;
        validos[quantidade - 1] = valido;

        freePilha(&pilhaOperadores);

        while (1) {
            printf("\nDeseja inserir outra expressao? (1 = sim / 0 = nao): ");
            
            if (scanf("%d", &continuar) != 1) {
                printf("Entrada invalida! Por favor, digite apenas o numero 0 ou 1.\n");
                while (getchar() != '\n');
                continue;
            }

            while (getchar() != '\n');

            if (continuar == 0 || continuar == 1) {
                break;
            } else {
                printf("Entrada invalida! Por favor, digite apenas o numero 0 ou 1.\n");
            }
        }
    }

    printf("\n========== RESULTADOS ==========\n");

    for (int i = 0; i < quantidade; i++) {

        printf("\nExpressao %d: %s\n", i + 1, expressoesOriginais[i]);

        printf("Posfixa: %s\n", expressoes[i]);

        printf("Estrutura da Arvore:\n");
        printTreeGrafico(arvores[i], 0);
        printf("\n");

        printf("PreOrder: ");
        printPreOrder(arvores[i]);

        printf("\nInOrder: ");
        printInOrder(arvores[i]);

        printf("\nPostOrder: ");
        printPostOrder(arvores[i]);

        if (validos[i]) {
            printf("\nResultado: %.2f\n", resultados[i]);
        }

        else {
            printf("\nResultado: Erro Matematico (Divisao por zero ou Raiz de numero negativo)\n");
        }

        freeTree(arvores[i]);
        free(expressoes[i]);
        free(expressoesOriginais[i]);
        printf("--------------------------------\n");
    }

    printf("\nPressione ENTER para encerrar o programa...");
    getchar();

    free(expressoes);
    free(expressoesOriginais);
    free(arvores);
    free(resultados);
    free(validos);

    return 0;
}