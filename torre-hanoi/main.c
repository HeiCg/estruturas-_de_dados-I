#include <string.h>
#include "TorreDeHanoi.h"

// funções relacionadas ao começo do jogo

// informação do limite da quantidade de pinos e discos
char *limites = "[3...5]";

/**
 * @brief função que imprime a mensagem de error serve tanto 
 *        para o erro da entrada quanto para o erro do movimento
 * 
 * @param info deve receber uma string {entrada ou movimento}
 */
void mensagemError(char *info) {
    printf("%s %s\n", info, info[0] == 69? "invalida" : "invalido");
}

/**
 * @brief verifica se a entrada está no intervalo [3..5]
 * 
 * @param quantidade 
 * @return int retornará 1 caso a entrada seja válida
 */
int validaEntrada(int quantidade){
    return (quantidade >= 3 && quantidade <= 5);
}

/**
 * @brief função que solicita a quantidade de discos ou de pinos
 *        recursivamente até ler um valor considerado válido
 * 
 * @param function 
 * @param info informa se a solicitação trata-se de pinos ou de discos
 * @return int retorna a quantidade lida
 */
int solicitaQtd(int (*function)(int), char* info) {
    printf("Insira a quantidade de %s: %s ", info, limites);

    int quantidade;
    scanf("%d", &quantidade);

    if(function(quantidade)) return quantidade;
    mensagemError("Entrada");
    return solicitaQtd(function, info);
}
    
// funções do jogo

/**
 * @brief cria um vetor de pinos
 * 
 * @param numPinos é a quantidade de pinos, no caso o tamanho do vetor
 * @return Pino** 
 */
Pino** criarPinos(int numPinos) {
    Pino** pinos = (Pino**)malloc(sizeof(Pino*)*numPinos);
    if(pinos == NULL) exit(1);
	for(unsigned short i = 0; i < numPinos; i++) {
		pinos[i] = criarPino();
	}
    return pinos;
}

/**
 * @brief Move o disco do pino de origem para o pino destino
 * 
 * @param pinos[] trata-se de um vetor de pinos
 * @param pinoOrigem  índice do pino de origem
 * @param pinoDestino  índice do pino de destino
 * @return int 0 caso não foi possível mover, 
 *             1 caso tenha sido bem sucedido
 */
int moverDisco(Pino **pinos, int pinoOrigem, int pinoDestino) {
    pinoOrigem--;
    pinoDestino--;
    if(pinos[pinoOrigem]->topo == NULL)
        return 0; // sem pino para ser movido
    if (pinos[pinoDestino]->topo != NULL && (pinos[pinoOrigem]->topo->tamDisco > pinos[pinoDestino]->topo->tamDisco))
        return 0; // movimento inválido pois o pino de origem é maior que o de destino
    push(pinos[pinoDestino], pop(pinos[pinoOrigem]));
    return 1; 
}

// funções de impressão, são utilizada para renderizar uma linha por vocês
// exemplo de um fluxo de renderização no primeiro pino, em um jogo com 3 discos e 3 pinos
//  ..._|_...
//  ..__|__..
//  .___|___.
//  ----|----
// cada linha pode ser composta por espaço vazio(representado por .)
// | que é utilizado o printf("|");
// e a metade do disco

/**
 * @brief função utilizada para imprimir os espaços em branco
 *        tanto da esquerda tanto da direita
 * 
 */
void espaçoVazio(int quantidadeVazio) {
    for(int j = 1; j <= quantidadeVazio; j++)
        printf(" ");
}

/**
 * @brief função que imprime a metade do disco tanto na direita
 *        quanto na esquerda
 * 
 * @param tamanhoDoDisco 
 */
void metadeDisco(int tamanhoDoDisco) {
    for(int j = 1; j <= tamanhoDoDisco; j++)
        printf("_");
}

/**
 * @brief 
 * 
 * @param tamanho 
 */
void linhaComDisco(int tamanho) {
    metadeDisco(tamanho);
    printf("|");
    metadeDisco(tamanho);
}

void imprimir(Pino** pinos,int numPinos, int numDiscos) {
    printf("\n");
    int tamanhoDoPino = numDiscos + 1, // tamanho vertical do pino
    tamDoPrimeiroDisco, qtdLinhaVazia;
    unsigned short i;
    for(unsigned short h = 0; h < numPinos; h++) {

        // calcula os espaços vazios no topo do pino
        qtdLinhaVazia = numDiscos - (pinos[h]->numDiscos - '0');

        // imprime as linhas vazias, seguindo o fluxo de renderização
        for(i = 0; i < qtdLinhaVazia; i++) {
            // uma linha sem discos é composta por ....|....
            espaçoVazio(tamanhoDoPino); // ....
            printf("|"); // |
            espaçoVazio(tamanhoDoPino); // ....
            printf("\n");
        }
        
        // verifica se o pino está totalmente vazio
        // caso não esteja imprime o que falta
        // pois como estava vazio, já foi impresso totalmente no primeiro laço
        if( !(qtdLinhaVazia == numDiscos) ) {

            tamDoPrimeiroDisco = pinos[h]->topo->tamDisco - '0';
            for(; i < numDiscos; i++) { // i começa após a impressão dos espaços vazios
                espaçoVazio(tamanhoDoPino-tamDoPrimeiroDisco);
                // metadeDisco(tamDoPrimeiroDisco);
                // printf("|");
                // metadeDisco(tamDoPrimeiroDisco);
                linhaComDisco(tamDoPrimeiroDisco);
                espaçoVazio(tamanhoDoPino-tamDoPrimeiroDisco);
                printf("\n");
                tamDoPrimeiroDisco++;
            }
        }

        linhaComDisco(i+1); // impressão da base
        printf("\n\n");
        espaçoVazio(tamanhoDoPino); // espaços vazios a direita
        printf("%d\n", h+1); // indice do pino
        printf("\n");
    }
}

/**
 * @brief função que verifica o estado de cada pino para ver se o jogador ganhou
 * 
 * @param pinos vetor de pinos
 * @param pinoDestino
 * @param numDiscos 
 * @return int 1 -> caso o jogador tenha ganho o jogo
 *             0 -> caso não
 */
int ganhou(Pino** pinos, int pinoDestino, int numDiscos){
    pinoDestino--;
    Disco* aux = pinos[pinoDestino]->topo;
    int quantDisco=0;
    while(aux != NULL){//verifica se tem disco no pino de destino
        quantDisco++;
        aux = aux->next;
    }
    // caso tenha sido passado todos os discos para outro pino que não seja o primeiro
    if((quantDisco == numDiscos) && (pinoDestino != 0)){
        return 1; 
    }
    return 0;
  
}

int main(int argc, char const *argv[]) {
    // começo do jogo
    int quantidadePinos = solicitaQtd(validaEntrada, "pinos");
    int quantidadeDiscos = solicitaQtd(validaEntrada, "discos");
    Pino** pinos = criarPinos(quantidadePinos);

    for(unsigned short i = quantidadeDiscos; i > 0; i--) {
        push(pinos[0], criarDisco(i));
    }
    // primeira impressão do estado da torre
    imprimir(pinos, quantidadePinos, quantidadeDiscos);

    int p1, p2, jogadas = 0;

    // jogo em andamento
    while(1){
        printf("Insira os pinos de origem e de destino: ");
        scanf("%d %d", &p1, &p2);
        if((p1 >= 1 && p1 <= quantidadePinos) && (p2>=1 && p2<=quantidadePinos) && (p1!=p2)){
            // verifica se o movimento é valido
            if(moverDisco(pinos, p1, p2)){
                // incrementa as jogadas válidas
                jogadas++;
                //verifica se o jogo acabou
                if(ganhou(pinos, p2, quantidadeDiscos)){
                    // caso o jogo tenha acabado
                    imprimir(pinos, quantidadePinos, quantidadeDiscos);
                    break;// sai do while(1)
                }
            }else{
                printf("Movimento invalido.\n");
            }
        }else{
            printf("Movimento invalido.\n");
        }
        imprimir(pinos, quantidadePinos, quantidadeDiscos);
    }

    // final do jogo
    printf("PARABENS VOCE CONSEGUIU\n");
    printf("TOTAL DE JOGADAS: %d\n", jogadas);
    for(unsigned short i = 0; i < quantidadePinos; i++) {
        excluirPino(pinos[i]);
    }
    return 0;
}