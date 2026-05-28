#include "pilha.h"
#include "arvore.h"
#include <stdlib.h>

float soma(float num1, float num2){
    return num1 + num2;
}

float sub(float num1, float num2){
    return num1 - num2;
}

float multi(float num1, float num2){
    return num1 *  num2;
}

float division(float num1, float num2){
    return num1 / num2;
}

float powF(float base, float expo) {
    float resultado = 1;
    while (expo > 0) {
        resultado = multi(resultado, base);
        expo--;
    }
    return resultado;
}

float sqrtF(float n) {
    if (n < 0)
        return -1;

    if (n == 0)
        return 0;

    float x = n;
    float prev;
    float epsilon = 0.001f;

    do {
        prev = x;
        x = (x + n / x) / 2.0f;
    } while ((x - prev > epsilon) || (prev - x > epsilon));

    return x;
}


char *ordenadora(char *string, Pilha *pilha) {

    int tamanho = 0;

    while (*(string + tamanho) != '\0') {
        tamanho++;
    }

    char *ns = malloc((tamanho * 2 + 1) * sizeof(char));

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

        // número
        if (c >= '0' && c <= '9') {

            while (*(string + i) >= '0' && *(string + i) <= '9') {

                *(ns + j) = *(string + i);

                i++;
                j++;
            }

            *(ns + j) = ' ';
            j++;

            continue;
        }

        // parenteses
        if (c == '(') {
            push(pilha, c);
        }

        else if (c == ')') {

            int topo;

            peek(pilha, &topo);

            while (topo != '(') {

                pop(pilha, &topo);

                *(ns + j) = topo;
                j++;

                *(ns + j) = ' ';
                j++;

                peek(pilha, &topo);
            }

            // remove '('
            pop(pilha, &topo);

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

        // raiz quadrada
        else if (c == 'r') {
            push(pilha, c);
        }

        // operadores
        else if (
            c == '+' ||
            c == '-' ||
            c == '*' ||
            c == '/' ||
            c == '^'
        ) {

            int topo;

            while (
                !isEmpty(pilha) &&
                peek(pilha, &topo) &&
                topo != '(' &&
                (
                    (c == '+' || c == '-') &&
                    (topo == '+' || topo == '-' || topo == '*' || topo == '/' || topo == '^' || topo == 'r')

                    ||

                    (c == '*' || c == '/') &&
                    (topo == '*' || topo == '/' || topo == '^' || topo == 'r')

                    ||

                    (c == '^') &&
                    (topo == '^' || topo == 'r')
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

    TreeNode **pilha = malloc(tamanho * sizeof(TreeNode *));

    if (pilha == NULL) {
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

            pilha[++topo] = createNode(numero);

            continue;
        }

        // raiz quadrada
        if (c == 'r') {

            TreeNode *novo = createNode(c);

            novo->right = pilha[topo--];
            novo->left = NULL;

            pilha[++topo] = novo;
        }

        // operadores
        else if (
            c == '+' ||
            c == '-' ||
            c == '*' ||
            c == '/' ||
            c == '^'
        ) {

            TreeNode *novo = createNode(c);

            novo->right = pilha[topo--];
            novo->left = pilha[topo--];

            pilha[++topo] = novo;
        }

        i++;
    }

    TreeNode *raiz = pilha[topo];

    free(pilha);

    return raiz;
}

float calcularExpressao(TreeNode *root) {

    if (root == NULL) {
        return 0;
    }

    // nó folha = número
    if (root->left == NULL && root->right == NULL) {
        return root->value;
    }

    // raiz quadrada
    if (root->value == 'r') {
        return sqrtF(calcularExpressao(root->right));
    }

    float esquerda = calcularExpressao(root->left);
    float direita = calcularExpressao(root->right);

    switch (root->value) {

        case '+':
            return soma(esquerda, direita);

        case '-':
            return sub(esquerda, direita);

        case '*':
            return multi(esquerda, direita);

        case '/':
            return division(esquerda, direita);

        case '^':
            return powF(esquerda, direita);
    }

    return 0;
}