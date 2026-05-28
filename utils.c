#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

char *userInput(int buffer){

        int i = 0;

    char *str = malloc(buffer * sizeof(char));

    if (str == NULL) {
        printf("Erro de memoria\n");
        return NULL;
    }

    char c;

    while ((c = getchar()) != '\n') {
        if (i >= buffer - 1) {
            buffer *= 2;

            char *temp = realloc(str, buffer);

            if (temp == NULL) {
                free(str);
                printf("Erro de memoria\n");
                return NULL;
            }

            str = temp;
        }

        str[i++] = c;
    }

    str[i] = '\0';
    return str;
}