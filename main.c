#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "arvore.h"
#include "pilha.h"
#include "matematica.h"

int main() {

    int continuar = 1;

    while (continuar) {

        Pilha pilhaOperadores;
        initPilha(&pilhaOperadores);

        int tamanho = 10;
        float resultado = 0.0;

        printf("\nDigite sua expressao: ");
        char *str = userInput(tamanho);

        str = ordenadora(str, &pilhaOperadores);
        printf("%s", str);

        TreeNode *arvore = inserirExpressao(str);
        resultado = calcularExpressao(arvore);

        printf("\nO resultado da expressao e: %f\n", resultado);

        freeTree(arvore);
        free(str);
        freePilha(&pilhaOperadores); //desnecessário mas ok

        printf("\nDeseja continuar? (1 = sim / 0 = nao): ");
        scanf("%d", &continuar);

        getchar();
    }

    return 0;
}