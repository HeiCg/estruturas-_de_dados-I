#include "TorreDeHanoi.h"

Pino* criarPino() {
    Pino *pino = (Pino*)malloc(sizeof(Pino));
    if(pino == NULL) exit(1);

    pino->numDiscos = '0';
    pino->topo = NULL;

    return pino;
}

Disco* criarDisco(int tam) {
    Disco *disco = (Disco*)malloc(sizeof(Disco));
    if(!disco) exit(1);

    disco->next = NULL;
    disco->tamDisco = tam+'0';
    return disco;
}

Disco* pop(Pino *pino) {
    if(pino->topo == NULL)
        return NULL;
    Disco *aux = pino->topo;
	pino->numDiscos--;
	pino->topo = aux->next;
	return aux;
}

void push(Pino *pino, Disco *disco) {
    disco->next = pino->topo;
    pino->topo = disco;
    pino->numDiscos++;
}

void excluirPino(Pino *pino) {
    Disco *d;
    while(pino->topo != NULL) {
        d = pino->topo;
        pino->topo  = d->next;
        free(d);
    }
    free(pino);
}