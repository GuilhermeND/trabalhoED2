#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

void initPilha(Pilha* s) {
    s->top = NULL;
}

int isEmpty(Pilha* s) {
    return s->top == NULL;
}

int push(Pilha* s, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erro na alocação de memoria da pilha\n");
        return 0;
    }
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
    return 1;
}

int pop(Pilha* s, int* poppedValue) {
    if (isEmpty(s)) {
        printf("Nenhum elemento na pilha");
        return 0;
    }
    Node* temp = s->top;
    *poppedValue = temp->data;
    s->top = s->top->next;
    free(temp);
    return 1;
}

int peek(Pilha* s, int* topValue) {
    if (isEmpty(s)) {
        printf("Nenhum elemento na pilha\n");
        return 0;
    }
    *topValue = s->top->data;
    return 1;
}

void freePilha(Pilha* s) {
    Node* current = s->top;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    s->top = NULL;
}

