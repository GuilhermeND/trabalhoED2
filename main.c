#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
    int tamanho = 10;


    printf("Digite sua expressão: ");
    char *str = userInput(tamanho);




    free(str);
    return 0;
}