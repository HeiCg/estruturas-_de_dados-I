#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Estrutura Disco
 * @a next ponteiro para o próximo disco
 * @a tamDisco tamanho do disco
 */
typedef struct Disco{
    char tamDisco;
    struct Disco* next;
}Disco;

/**
 * @brief Estrutura Pino
 * @a topo ponteiro para o topo da pilha
 * @a numDiscos quantidade de discos
 */
typedef struct Pino{
    char numDiscos;
    Disco *topo;
}Pino;

Pino* criarPino();

Disco* criarDisco(int tamanhoDoDisco);

Disco* pop(Pino *pino);

void push(Pino *pino, Disco *disco);

void excluirPino(Pino *pino);
