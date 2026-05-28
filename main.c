#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "arvore.h"
#include "pilha.h"
#include "matematica.h"

int main() {

    int continuar = 1;
    int quantidade = 0;
    int tamanho = 10;

    char **expressoes = NULL;
    TreeNode **arvores = NULL;
    float *resultados = NULL;
    int *validos = NULL;

    while (continuar) {

        Pilha pilhaOperadores;
        initPilha(&pilhaOperadores);

        printf("\nDigite sua expressao: ");

        char *str = userInput(tamanho);

        str = ordenadora(str, &pilhaOperadores);

        TreeNode *arvore = inserirExpressao(str);

        float resultado = 0;

        int valido = calcularExpressao(arvore, &resultado);

        quantidade++;

        expressoes = realloc(expressoes, quantidade * sizeof(char *));
        arvores = realloc(arvores, quantidade * sizeof(TreeNode *));
        resultados = realloc(resultados, quantidade * sizeof(float));
        validos = realloc(validos, quantidade * sizeof(int));

        if (
            expressoes == NULL ||
            arvores == NULL ||
            resultados == NULL ||
            validos == NULL
        ) {

            printf("\nErro de memoria\n");

            return 1;
        }

        expressoes[quantidade - 1] = str;
        arvores[quantidade - 1] = arvore;
        resultados[quantidade - 1] = resultado;
        validos[quantidade - 1] = valido;

        freePilha(&pilhaOperadores);

        printf("\nDeseja inserir outra expressao? (1 = sim / 0 = nao): ");
        scanf("%d", &continuar);

        getchar();
    }

    printf("\n========== RESULTADOS ==========\n");

    for (int i = 0; i < quantidade; i++) {

        printf("\nExpressao %d:\n", i + 1);

        printf("Posfixa: %s\n", expressoes[i]);

        printf("PreOrder: ");
        printPreOrder(arvores[i]);

        printf("\nInOrder: ");
        printInOrder(arvores[i]);

        printf("\nPostOrder: ");
        printPostOrder(arvores[i]);

        if (validos[i]) {
            printf("\nResultado: %f\n", resultados[i]);
        }

        else {
            printf("\nExpressao invalida\n");
        }

        freeTree(arvores[i]);
        free(expressoes[i]);
    }

    free(expressoes);
    free(arvores);
    free(resultados);
    free(validos);

    return 0;
}