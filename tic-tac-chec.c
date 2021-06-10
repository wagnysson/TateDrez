// Wagnysson Moura Luz - 12558471
// Bruno Dias -

#include <stdio.h>
#include <math.h>

#define N 3

int main(){
    //declarando as varaveis
    char j1[20], j2[20]; // recebe o nome dos jogadores
    char pecasj1[3], pecasj2[3]; //recebe as pecas de cada jogador 
    char tab[3][3];
    int i, j; //contador
    int p1, p2; //p1 - posiicao 1, p2 - posicao 2.
    char peca; // peca escolida

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

    //pecas, C = cavalo branco, T = torre branca, B = bispo branco, c = cavalo preto, t = torre preta, b = bispo preto. 
    // for (i=0; i<3; i++){
    //     pecasj1[i] = ;
    // }
    // for (i=3; i<6; i++){
    //     pecasj2[i] = i;
    // }
	
    //mostrando o tabuleiro
    for (i=0; i<N; i++){
        printf("|");
        for(j=0; j<N; j++){
            tab[i][j] = '_';
            // scanf("%s", tab[i][j]);
            printf("%3c", tab[i][j]);
        }
        printf("|");
        printf("\n");
    }
	
	//registro dos lances iniciais dos jogadores
	for(i=0;i<6;i++){
        
		if(i%2==0){ //se a rodada for par o jogador 1 joga
			do{
            scanf("%d %d  %c", &p1, &p2, &peca);
			tab[p1-1][p2-1] = peca;
            }while((p1-1>0 && p1-1<=3) || (peca != B && peca != C && peca != T))
		}
		else{ //se a rodada for impar o jogador 2 joga
			scanf("%d %d  %c", &p1, &p2, &peca);
			tab[p1][p2] = peca;
		}
		
	}

    //movimento do cavalo

    //movimento do bispo
    
    //movimento da torre
	
	//teste1
    
    return(0);
}
