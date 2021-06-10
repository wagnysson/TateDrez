// Wagnysson Moura Luz - 12558471
// Bruno Dias -

#include <stdio.h>
#include <math.h>

#define N 3

int main(){
    //declarando as varaveis
    char j1[20], j2[20]; // recebe o nome dos jogadores
    int pecasj1[3], pecasj2[3]; //recebe as pecas de cada jogador 
    int tab[3][3];
    int i, j; //contador

    //informacoes sobre o jogo
    printf("Bem vindos ao Tic Tac Chec! ");

    //jogadores dão entrada em seus nomes
    printf("Jogador 1, digite como deseja ser chamado: ");
    scanf("%s", j1);
    printf("Jogador 2, digite como deseja ser chamado: ");
    scanf("%s", j2);

    //ver quais os nomes dos jogadores
    // printf("Jogador 1: %s\n", j1);
    // printf("Jogador 2: %s\n", j2);

    //pecas, 1 = cavalo branco, 2 = torre branca, 3 = bispo branco, 4 = cavalo preto, 5 = torre preta, 6 = bispo preto. 
    for (i=0; i<3; i++){
        pecasj1[i] = i;
    }
    for (i=3; i<6; i++){
        pecasj2[i] = i;
    }
	
    //mostrando o tabuleiro
    do{
        for (i=0; i<N; i++){
            printf("|");
            for(j=0; j<N; j++){
                scanf("%s", tab[i][j]);
            }
            printf("|");
            printf("\n")
        }
    }

    //movimento do cavalo

    //movimento do bispo
    
    //movimento da torre
	
	//teste1
    
    return(0);
}