// Wagnysson Moura Luz - 12558471
// Bruno Dias Moreira - 12624905

#include <stdio.h>
#include <math.h>

#define N 3

//funcao que escreve o tabuleiro
char printTab(char tab[3][3]){
    int m, n;

    for (m=0; m<N; m++){
        printf("|");
        for(n=0; n<N; n++){
            printf("%3c", tab[m][n]);
        }
        printf("  |");
        printf("\n");
    }

    return(0);
}    

/*
Valores da Tabela ASCII utilizados no programa
B = 66
C = 67
T = 84
b = 98
c = 99
t = 116
_ = 95*/

int main(){
    //declarando as varaveis
    char j1[20], j2[20]; // recebe o nome dos jogadores
    char tab[3][3];
    int i, j; //contador
    int p1, p2; //p1 - posiicao 1, p2 - posicao 2.
    char peca; // peca escolida

    

    //informacoes sobre o jogo
    printf("Bem vindos ao Tic Tac Chec! O jogador 1 joga primeiro e joga com as pecas de letra maiuscula, o jogador 2 joga com as pecas de letra\n");

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
	
    //colocando casas "vazias" no tabuleiro
    for (i=0; i<N; i++){
        for(j=0; j<N; j++){
            tab[i][j] = '_';
	}
    }
	    printTab(tab);
	
	//registro dos lances iniciais dos jogadores
	for(i=0;i<6;i++){
        printf("Rodada %d\n", i);
		if(i%2==0){ //se a rodada for par o jogador 1 joga
			do{
                printf("Turno de %s\n", j1);
                scanf("%d %d  %c", &p1, &p2, &peca);
			    tab[p1-1][p2-1] = peca;
            }while((p1-1<0 || p1-1>3) || (p2-1<0 || p2-1>3) || (peca != 'B' && peca != 'C' && peca != 'T'));
		}
		else{ //se a rodada for impar o jogador 2 joga
            
            do{
                printf("Turno de %s\n", j2);
			    scanf("%d %d  %c", &p1, &p2, &peca);
			    tab[p1-1][p2-1] = peca;
            }while((p1-1<0 || p1-1>3) || (p2-1<0 || p2-1>3) || (peca != 'b' && peca != 'c' && peca != 't'));
		}
        printTab(tab);
	}

    //movimento do cavalo

    //movimento do bispo
    
    //movimento da torre
	
	//teste1
    
    return(0);
}
