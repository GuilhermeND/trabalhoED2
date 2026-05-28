#ifndef PILHA_H
#define PILHA_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct _pilha{
    Node* top;
} Pilha;

void initPilha(Pilha* s);

int isEmpty(Pilha* s);

int push(Pilha* s, int value);

int pop(Pilha* s, int* poppedValue);

int peek(Pilha* s, int* topValue);

void freePilha(Pilha* s); 

#endif