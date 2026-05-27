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


    printf("Digite sua expressão: ");
    char *str = userInput(tamanho);
    str = ordenadora(str, pilhaOperadores);
    




    free(str);
    freePilha(&pilhaOperadores);
    return 0;
}