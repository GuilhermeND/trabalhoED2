#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "arvore.h"
#include "pilha.h"
#include "matematica.h"

int main() {
    Pilha pilhaOperadores;
    initPilha(&pilhaOperadores);

    int tamanho = 10;
    float resultado = 0.0;


    printf("Digite sua expressao: ");
    char *str = userInput(tamanho);
    str = ordenadora(str, pilhaOperadores);
    TreeNode *arvore = inserirExpressao(str);
    resultado = calcularExpressao(arvore);
    printf("\nO resultado da expressao e: %f", resultado);


    free(arvore);
    free(str);
    return 0;
}