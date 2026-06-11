#include "pilha.h"
#include "arvore.h"
#include <stdlib.h>

int soma(float num1, float num2, float *resultado){
    *resultado = num1 + num2;
    return 1;
}

int sub(float num1, float num2, float *resultado){
    *resultado = num1 - num2;
    return 1;
}

int multi(float num1, float num2, float *resultado){
    *resultado = num1 * num2;
    return 1;
}

int division(float num1, float num2, float *resultado){

    if (num2 == 0) {
        return 0;
    }

    *resultado = num1 / num2;

    return 1;
}

int powF(float base, float expo, float *resultado) {

    *resultado = 1;

    while (expo > 0) {

        *resultado *= base;

        expo--;
    }

    return 1;
}

int sqrtF(float n, float *resultado) {

    if (n < 0) {
        return 0;
    }

    if (n == 0) {

        *resultado = 0;

        return 1;
    }

    float x = n;
    float prev;
    float epsilon = 0.001f;

    do {

        prev = x;

        x = (x + n / x) / 2.0f;

    } while ((x - prev > epsilon) || (prev - x > epsilon));

    *resultado = x;

    return 1;
}

char *ordenadora(char *string, Pilha *pilha) {

    int tamanho = 0;

    while (*(string + tamanho) != '\0') {
        tamanho++;
    }

    char *ns = malloc((tamanho * 3 + 1) * sizeof(char));

    if (ns == NULL) {
        return NULL;
    }

    int i = 0;
    int j = 0;

    while (*(string + i) != '\0') {

        char c = *(string + i);

        // ignora espaços
        if (c == ' ') {
            i++;
            continue;
        }

        // sqrt
        if (*(string + i) == 'r') {
            push(pilha, 'r');
            i++;
            continue;
        }
        else if (
            *(string + i) == 's' &&
            *(string + i + 1) == 'q' &&
            *(string + i + 2) == 'r' &&
            *(string + i + 3) == 't'
        ) {

            push(pilha, 'r');

            i += 4;

            continue;
        }

        // número ou negativo
        if (

            (c >= '0' && c <= '9')

            ||

            (
                c == '-' &&
                (
                    i == 0 ||

                    *(string + i - 1) == '(' ||
                    *(string + i - 1) == '+' ||
                    *(string + i - 1) == '-' ||
                    *(string + i - 1) == '*' ||
                    *(string + i - 1) == '/' ||
                    *(string + i - 1) == '^' ||
                    *(string + i - 1) == '$'
                )
            )
        ) {

            // negativo unário
            if (c == '-') {

                *(ns + j) = '0';
                j++;

                *(ns + j) = ' ';
                j++;

                push(pilha, '-');

                i++;
            }

            while (*(string + i) >= '0' && *(string + i) <= '9') {

                *(ns + j) = *(string + i);

                i++;
                j++;
            }

            *(ns + j) = ' ';
            j++;

            continue;
        }

        // abre parenteses
        if (c == '(') {

            push(pilha, c);
        }

        // fecha parenteses
        else if (c == ')') {

            if (isEmpty(pilha)) {
                i++;
                continue;
            }

            int topo;

            peek(pilha, &topo);

            while (topo != '(') {

                pop(pilha, &topo);

                *(ns + j) = topo;
                j++;

                *(ns + j) = ' ';
                j++;

                if (isEmpty(pilha)) {
                    break;
                }

                peek(pilha, &topo);
            }

            // remove '('
            if (!isEmpty(pilha)) {
                peek(pilha, &topo);
                if (topo == '(') {
                    pop(pilha, &topo);
                }

                // se tiver raiz antes do parenteses
                if (!isEmpty(pilha)) {

                    peek(pilha, &topo);

                    if (topo == 'r') {

                        pop(pilha, &topo);

                        *(ns + j) = topo;
                        j++;

                        *(ns + j) = ' ';
                        j++;
                    }
                }
            }
        }

        // operadores
        else if (
            c == '+' ||
            c == '-' ||
            c == '*' ||
            c == '/' ||
            c == '^' ||
            c == '$'
        ) {

            int topo;

            while (
                !isEmpty(pilha) &&
                peek(pilha, &topo) &&
                topo != '(' &&
                (
                    (c == '+' || c == '-') &&
                    (
                        topo == '+' ||
                        topo == '-' ||
                        topo == '*' ||
                        topo == '/' ||
                        topo == '^' ||
                        topo == 'r' ||
                        topo == '$'
                    )

                    ||

                    (c == '*' || c == '/') &&
                    (
                        topo == '*' ||
                        topo == '/' ||
                        topo == '^' ||
                        topo == 'r' ||
                        topo == '$'
                    )
                )
            ) {

                pop(pilha, &topo);

                *(ns + j) = topo;
                j++;

                *(ns + j) = ' ';
                j++;
            }

            push(pilha, c);
        }

        i++;
    }

    int topo;

    while (!isEmpty(pilha)) {

        pop(pilha, &topo);

        *(ns + j) = topo;
        j++;

        *(ns + j) = ' ';
        j++;
    }

    *(ns + j) = '\0';

    free(string);

    return ns;
}

TreeNode *inserirExpressao(char *string) {

    int tamanho = 0;

    while (*(string + tamanho) != '\0') {
        tamanho++;
    }

    TreeNode **arvore = malloc(tamanho * sizeof(TreeNode *));

    if (arvore == NULL) {
        return NULL;
    }

    int topo = -1;

    int i = 0;

    while (*(string + i) != '\0') {

        char c = *(string + i);

        // ignora espaços
        if (c == ' ') {
            i++;
            continue;
        }

        // número
        if (c >= '0' && c <= '9') {

            int numero = 0;

            while (*(string + i) >= '0' && *(string + i) <= '9') {

                numero = numero * 10 + (*(string + i) - '0');

                i++;
            }

            arvore[++topo] = createNode(numero);

            continue;
        }

        // raiz quadrada
        if (c == 'r') {

            TreeNode *novo = createNode(c);

            novo->right = arvore[topo--];
            novo->left = NULL;

            arvore[++topo] = novo;
        }

        // operadores
        else if (
            c == '+' ||
            c == '-' ||
            c == '*' ||
            c == '/' ||
            c == '^' ||
            c == '$'
        ) {

            TreeNode *novo = createNode(c);

            novo->right = arvore[topo--];
            novo->left = arvore[topo--];

            arvore[++topo] = novo;
        }

        i++;
    }

    TreeNode *raiz = arvore[topo];

    free(arvore);

    return raiz;
}

int calcularExpressao(TreeNode *root, float *resultado) {

    if (root == NULL) {
        return 0;
    }

    // nó folha
    if (root->left == NULL && root->right == NULL) {

        *resultado = root->value;

        return 1;
    }

    if (root->value == 'r') {

        float direita;

        // Calcula o miolo de dentro da raiz primeiro
        if (!calcularExpressao(root->right, &direita)) {
            return 0;
        }

        if (direita < 0) {
            return 0; 
        }

        return sqrtF(direita, resultado);
    }

    float esquerda;
    float direita;

    if (!calcularExpressao(root->left, &esquerda)) {
        return 0;
    }

    if (!calcularExpressao(root->right, &direita)) {
        return 0;
    }

    int operacaoValida = 0;

    switch (root->value) {

        case '+':
            operacaoValida = soma(esquerda, direita, resultado);
            break;
        case '-':
            operacaoValida = sub(esquerda, direita, resultado);
            break;
        case '*':
            operacaoValida = multi(esquerda, direita, resultado);
            break;
        case '/':
            operacaoValida = division(esquerda, direita, resultado);
            break;
        case '^':
        case '$':
            operacaoValida = powF(esquerda, direita, resultado);
            break;
        default:
            return 0;
    }

    if (!operacaoValida) {
        return 0;
    }

    return 1;
}