#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
    [0, 8] : adjacências da coordenada
    -2 : sefa area
    -1 : espaço com bomba
*/

int N;

// <-- Mensagem de error default -->
void error_entrada() {printf("Entrada Invalida\n");}

//<-- Tamanho da matriz -->
int valida_entrada(int input) {
    if(input < 3 || input > 9) {
        error_entrada();
        printf("Sua entrada deve estar no intervalo [3, 9]\n");
        return 0;
    }
    return 1;
}

// <-- coordenadas validas -->
int valida_coordenadas(int l, int c)  {
    if(c >= 0 && c < N && l >= 0 && l < N) return 1;
    return 0;
}

// <-- Retorna a quantidade de bombas -->
int n_bombas(int l, int c, char M[][N], int n) {
    int quantidade = 0;
    for(int i = l-1; i <= l+1; i++) {
        for(int j = c-1; j <= c+1; j++) {
            if(i == l && j == c) continue;
            if( valida_coordenadas(i,j) ) {
                if(M[i][j] == -1) {
                    quantidade++;
                }
            }
        }
    }
    return quantidade;
}

// <-- Gera a matriz com as bombas -->
void gerar_campo(char campo[][N], int n) {
    int bombas = 0.2*n*n;
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            campo[i][j] = -2;
        }
    }
    int i, j;
    while(bombas != 0) {
        i = rand() % n;
        j = rand() % n;
        if(campo[i][j] == -2) {
            campo[i][j] = -1;
            --bombas;
        }
    }
}

// <-- Inicializador -->
void imprime_mat(char campo[][N], int n) {
    int bombas = 0.2*N*N;
    for (int i = 0; i < n; i++) {
        printf("%d |", i+1);
        for (int j = 0; j < n; j++) {
            if(campo[i][j] >= 0 && campo[i][j] <= 8) printf(" %d ", campo[i][j]);
            else {printf(" ? ");}
        }

        // <-- Formatação da saída-->
        printf("\t\n");
        int a = 0;
        if(i == n-1)  {
            for(int j = 0; j < 3*n+3; j++) {
                if(j <= 2) printf(" ");
                else {
                    printf("-");
                }
            }
            printf("\n");
            printf("    ");
            for(int j = 1; j <= n; j++) {
                printf("%d  ", j);
            }
            printf("\n");
        }
    }
}

// <-- Fim de jogo - Gabarito -->
void fim_de_jogo(char campo[][N], int n) {
    for (int i = 0; i < n; i++) {
        // <-- formatação lateral -->
        printf("%d |", i+1);
        // <-- saída -->
        for (int j = 0; j < n; j++) {
            if(campo[i][j] >= 0 && campo[i][j] <= 8) printf(" %d ", campo[i][j]);
            else if(campo[i][j] == -1) printf(" * ");
            else { printf(" ? "); }
            
        }

        //<-- Formatação da saída tabulada-->
        printf("\t\n");
        int a = 0;
        if(i == n-1)  {
            for(int j = 0; j < 3*n+3; j++) {
                if(j <= 2) printf(" ");
                else {
                    printf("-");
                }
            }
            printf("\n");
            printf("    ");
            for(int j = 1; j <= n; j++) {
                printf("%d  ", j);
            }
            printf("\n");
        }
    }
}


int main(int argc, char const *argv[]) {   

    N=0;

    // <-- Tamanho do Campo -->
    do{
        printf( "Digite o tamanho da matriz desejada: " );
        scanf( "%d", &N);
        printf("\n");
    }while ( !valida_entrada(N) );
    char M[N][N];
    gerar_campo(M, N);
    imprime_mat(M, N);

    int l, c, controle;
    int controle_endGame = N*N - 0.2*N*N +1;
    while(controle_endGame) {
        do{
            printf( "\nDigite a linha e a coluna desejada: " );
            scanf("%d %d", &l, &c);
            printf("\n");

            controle = !valida_coordenadas(--l, --c);
            if( controle ) {
                error_entrada();
                printf("Suas entradas devem estar no intervalo [1, %d]\n\n", N);
            }
        }while( controle );

        if(M[l][c] == -1) {
            printf("VOCE PERDEU! FIM DO JOGO.\n\n");
            fim_de_jogo(M, N);
            return 0;
        } else {
            if(M[l][c] == -2){
                M[l][c] = n_bombas(l, c, M, N);
                imprime_mat(M, N);
                controle_endGame--;
            } else {
                imprime_mat(M, N);
            }

        }
    }
    printf("\nPARABENS! VOCE VENCEU!.\n\n");
    fim_de_jogo(M, N);

    return 0;
}