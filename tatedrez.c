// Wagnysson Moura Luz - 12558471
// Bruno Dias Moreira - 12624905

#include <stdio.h>
#include <math.h>

//ordem da matriz (3 linhas e 3 colunas, no caso)
#define N 3

//instrucoes de como jogar
void info(void){
	printf("Bem vindos ao TateDrez!\n\n");
	printf("COMO JOGAR?\nO jogo pode ser dividido em 2 fases, a FASE DE POSICIONAMENTO e a FASE DE JOGO nas quais os jogadores realizam LANCES.\n\n");
	printf("LANCE - Para fazer um lance o jogador da vez digita um comando no formato 'p1 p2 peca', onde p1 eh o numero da linha e p2 o da coluna do tabuleiro (para) onde o jogador deseja posicionar/movimentar a peca que eh definida pelo terceiro item do comando (peca).\n");
	printf("O jogador 1 joga apenas com as pecas de letra maiuscula e o jogador 2 joga apenas com as pecas de letra minuscula sendo elas:\n");
	printf("C, c - CAVALO\nB, b - BISPO\nT, t - TORRE\n\n");
	printf("FASE DE POSICIONAMENTO - Os jogadores fazem lances de posicionamento alternados começando pelo jogador 1. Eles podem colocar suas pecas em qualquer casa do tabuleiro que esteja vazia.\n\n");
	printf("FASE DE JOGO - Depois que todas as pecas estiverem posicionadas comeca a fase de jogo. Em cada rodada ha o turno do jogador 1 e o turno do jogador 2 e em cada um deles o jogador da vez movimenta uma de suas pecas. O OBJETIVO eh alinhar suas tres pecas como no jogo da velha (na diagonal, em linha ou em coluna), porem suas pecas se movimentam como no xadrez, ou seja, o CAVALO anda em L (uma casa na vertical ou na horizontal e outra na diagonal) e pode 'saltar' pecas que estejam no seu caminho, o BISPO anda apenas na diagonal quantas casas quiser sem poder 'saltar' pecas que estejam no seu caminho e a TORRE anda apenas na vertical ou na horizontal quantaas casas quiser sem poder 'saltar' pecas que estejam no seu caminho tambem.\n\n");
    printf("QUEM VENCE?\nO jogador que conseguir alinhas suas tres pecas em uma linha, coluna ou na diagonal primeiro vence.\n\n");
	printf("QUANDO DAH EMPATE?\nO empate ocorre quando nao ha movimentos possiveis para nenhuma peca de um jogador OU se depois de 30 rodadas (contando as rodadas de posicionamento, entao seria depois da 27a rodada de jogo) nenhum dos jogadores venceu.\n\n\n");
	
	return;
}

//funcao que mostra o atual estado do tabuleiro
char printTab(char tab[3][3]){
    int m, n;
	int c[3];
	
	//inicializando o vetor das colunas
	c[0] = 1;
	c[1] = 2;
	c[2] = 3;
	
    for (m=0; m<N; m++){
		if(m==0){
			printf("  %3d%3d%3d\n", c[0], c[1], c[2]);
		}
        printf("%d |", m+1);
        for(n=0; n<N; n++){
            printf("%3c", tab[m][n]);
        }
        printf("  |\n");
    }
	printf("\n");

    return(0);
}  

void erros(int i, int p1, int p2, char peca, char tab[N][N]){
	if((p1<1 || p1>3) || (p2<1 || p2>3)){
		printf("A casa que voce digitou nao existe. Faca outra jogada:\n");
	}
	if(i%2==0){

		if(peca != 'B' && peca != 'C' && peca != 'T'){
			printf("Essa peca nao existe. Faca outra jogada:\n");
		}
		else{
			if(tab[p1-1][p2-1] != '_'){
				printf("Essa casa ja esta ocupada. Faca outra jogada:\n");
			}
		}
	}else{
		if(peca != 'b' && peca != 'c' && peca != 't'){
			printf("Essa peca nao existe. Faca outra jogada:\n");
		}
		else{
			if(tab[p1-1][p2-1] != '_'){
				printf("Essa casa ja esta ocupada. Faca outra jogada:\n");
			}
		}
	}
	return;
}
//checa se um lance eh valido
int checarlance(int p1, int p2, char peca, char tab[N][N]){
	int i, j;
	int flag;
	flag = 0;

	//verifica se a condicao para que a peca escolhida se mova eh satisfeita
    switch(peca){
		//para o bispo (B e b), é
        case 'b':
            for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                    if(tab[i][j] == peca){
                        if(i != p1-1 && j != p2-1){
							if(tab[1][1] == '_' && tab[p1-1][p2-1] == '_'){
								flag = 0;
							}else{
								flag = 1;
							}
						}else{
							flag = 1;
						}
                    }
                }	
            }
            break;

        case 'c':
            for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                    if(tab[i][j] == peca){
                        if((sqrt(5)-0.1 < sqrt(pow((i+1)-p1,2)+pow((j+1)-p2,2))) && (sqrt(pow((i+1)-p1,2)+pow((j+1)-p2,2)) < sqrt(5)+0.1) && tab[p1-1][p2-1] == '_'){
                            flag = 0;
                        }
                        else{
                            flag = 1;
                        }
                    }
                } 
            }
            break;

        case 't':
            for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                    if(tab[i][j] == peca){
                        if((i != p1-1 && j != p2-1) || (i == p1-1 && j == p2-1)){
							flag = 1;
						}else{
							if((2-0.1 < sqrt(pow((i+1)-p1,2)+pow((j+1)-p2,2))) && (sqrt(pow((i+1)-p1,2)+pow((j+1)-p2,2)) < 2+0.1) && (tab[p1-1][p2-1] == '_')){
								if(p1-1 == i){
									if(tab[i][1] != '_'){
										flag = 1;
									}
								}else{
									if(p2-1 == j){
										if(tab[1][j] != '_'){
											flag = 1;
										}
									}
								}
							}else{
								if(tab[p1-1][p2-1] == '_'){
									flag = 0;
								}else{
									flag = 1;
								}
							}
						}
					}
                }
            }	   
        	break;
            
        case 'B':
            for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                    if(tab[i][j] == peca){
                        if(i != p1-1 && j != p2-1){
							if(tab[1][1] == '_' && tab[p1-1][p2-1] == '_'){
								flag = 0;
							}else{
								flag = 1;
							}
						}else{
							flag = 1;
						}
                    }
                }	
            }
            break;
            
        case 'C':
            for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                    if(tab[i][j] == peca){
                        if((sqrt(5)-0.1 < sqrt(pow((i+1)-p1,2)+pow((j+1)-p2,2))) && ((sqrt(pow((i+1)-p1,2)+pow((j+1)-p2,2)) < sqrt(5)+0.1)) && tab[p1-1][p2-1] == '_'){
                            flag = 0;
                        }
                        else{
                            flag = 1;
                        }   
                    }
                }	   
            }
            break;
            
        case 'T':
            for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                    if(tab[i][j] == peca){
                        if((i != p1-1 && j != p2-1) || (i == p1-1 && j == p2-1)){
							flag = 1;
						}else{
							if((2-0.1 < sqrt(pow((i+1)-p1,2)+pow((j+1)-p2,2))) && (sqrt(pow((i+1)-p1,2)+pow((j+1)-p2,2)) < 2+0.1) && (tab[p1-1][p2-1] == '_')){
								if(p1-1 == i){
									if(tab[i][1] != '_'){
										flag = 1;
									}
								}else{
									if(p2-1 == j){
										if(tab[1][j] != '_'){
											flag = 1;
										}
									}
								}
							}else{
								if(tab[p1-1][p2-1] == '_'){
									flag = 0;
								}else{
									flag = 1;
								}
							}
						}
					}
                }
            }	   
        	break;

        default:
            printf("Peca nao existe");	
    }

    return(flag);	
}

// confere se alguem venceu
int vencedor(char tab[3][3]){
	int i;
	int flag;
	flag=0;
	for(i=0;i<3;i++){
		if((tab[i][0]<85) && (tab[i][1]<85) && (tab[i][2]<85)){
			flag=1;
		}
		else{
			if((tab[i][0]>95) && (tab[i][1]>95) && (tab[i][2]>95)){
				flag = -1;
			}
		}
	}
	
	for(i=0;i<3;i++){
		if((tab[0][i]<85) && (tab[1][i]<85) && (tab[2][i])<85){
			flag=1;
		}
		else{
			if(tab[0][i]>95 && tab[1][i]>95 && tab[2][i]>95){
				flag = -1;
			}
		}	
	}
	if((tab[1][1]<85) && (tab[2][2]<85) && (tab[3][3]<85)){
		flag = 1;
	}
	else{
		if(tab[1][1]>95 && tab[2][2]>95 && tab[3][3]>95){
			flag  = -1;
		}
	}
	
	if(tab[1][3]<85 && tab[2][2]<85 && tab[3][1]<85){
		flag = 1;
	}
	else{
		if(tab[1][3]>95 && tab[2][2]>95 && tab[3][1]>95){
			flag  = -1;
		}
	}
	return(flag);
}


 //funcao que checa se uma peca ja esta no tabuleiro
char checar(char peca, char tab[3][3]){
	int i, j;
	char flag;
	flag='0';
	switch(peca){
		case 'b':
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){
					if(tab[i][j] == peca){
						flag='1';
					}
				}		
			}
			break;
		case 'c':
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){
					if(tab[i][j] == peca){
						flag='1';
					}
				}		
			}
	
			break;
		case 't':
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){
					if(tab[i][j] == peca){
						flag='1';
					}
				}		
			}
			break;
			
		case 'B':
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){
					if(tab[i][j] == peca){
						flag='1';
					}
				}	
			}
			break;
			
		case 'C':
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){
					if(tab[i][j] == peca){
						flag='1';
					}
				}	
			}
			break;
			
		case 'T':
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){
					if(tab[i][j] == peca){
						flag='1';
					}
				}	
			}
			break;
		default:
			printf("Peca nao existe");	
	}
	return(flag);
}	

//funcao que realiza um lance na segunda parte do jogo
char lance(int p1, int p2, char peca, char tab[N][N]){
		int i, j;
	
		switch(peca){
			case 'b':
				for(i=0;i<3;i++){
					for(j=0;j<3;j++){
						if(tab[i][j] == peca){
							tab[i][j] = '_';
						}
					}	
				}
				break;
                
			case 'c':
				for(i=0;i<3;i++){
					for(j=0;j<3;j++){
						if(tab[i][j] == peca){
							tab[i][j] = '_';
						}
					}	
				}
				break;

			case 't':
				for(i=0;i<3;i++){
					for(j=0;j<3;j++){
						if(tab[i][j] == peca){
							tab[i][j] = '_';
						}
					}	
					
				}
				break;
				
			case 'B':
				for(i=0;i<3;i++){
					for(j=0;j<3;j++){
						if(tab[i][j] == peca){
							tab[i][j] = '_';
						}
					}	
					
				}
				break;
				
			case 'C':
				for(i=0;i<3;i++){
					for(j=0;j<3;j++){
						if(tab[i][j] == peca){
							tab[i][j] = '_';
						}
					}	
					
				}
				break;
				
			case 'T':
				for(i=0;i<3;i++){
					for(j=0;j<3;j++){
						if(tab[i][j] == peca){
							tab[i][j] = '_';
						}
					}	
					
				}
				break;
			default:
				printf("Peca nao existe");	
		
		}
		tab[p1-1][p2-1]=peca;
		return(0);
    }

int empate1(char tab[N][N]){
	int i, j, flag = 0;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(checarlance(i+1, j+1, 'B', tab) == 1 && checarlance(i+1, j+1, 'C', tab) == 1 && checarlance(i+1, j+1, 'T', tab) == 1){
				flag = flag + 1;
			}
		}
	}
	return(flag);
}

int empate2(char tab[N][N]){
	int i, j, flag = 0;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(checarlance(i+1, j+1, 'b', tab) == 1 && checarlance(i+1, j+1, 'c', tab) == 1 && checarlance(i+1, j+1, 't', tab) == 1){
				flag = flag + 1;
			}
		}
	}
	return(flag);
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

int main(void){
    //declarando as varaveis
    char j1[20], j2[20]; // recebe o nome dos jogadores
    char tab[3][3]; //recebe o tabuleiro
    int i, j; //contadores
    int p1, p2; //p1 - linha do tabuleiro, p2 - coluna do tabuleiro.
    char peca; // peca escolhida para mover
	
	info();

	printf("FASE DE POSICIONAMENTO COMECOU!\n\n");
    //jogadores dão entrada em seus nomes
    printf("Jogador 1, digite como deseja ser chamado: ");
    scanf("%s", j1);
    printf("Jogador 2, digite como deseja ser chamado: ");
    scanf("%s", j2);

    //colocando casas vazias no tabuleiro que sao representadas por '_'
    for (i=0; i<N; i++){
        for(j=0; j<N; j++){
            tab[i][j] = '_';
		}
    }
	
	printTab(tab);
	
	//FASE DE POSICIONAMENTO
	for(i=0; i<6; i++){
		if(i%2==0){ //se a rodada for par o jogador 1 joga
			printf("\nRodada %d\n", i/2);
			do{
                printf("Turno de %s\n", j1);
				//le o lance de posicionamento do jogador 1
                scanf("%d %d  %c", &p1, &p2, &peca);
				
				erros(i, p1, p2, peca, tab);

            }while((p1<0 || p1>3) || (p2<0 || p2>3) || (peca != 'B' && peca != 'C' && peca != 'T')||(checar(peca, tab)== '1')|| (tab[p1-1][p2-1] != '_'));
			tab[p1-1][p2-1] = peca;
			if(vencedor(tab) == 1){
				printf("%s vence!\n", j1);
				i=7;
			}
		}
		else{ //se a rodada for impar o jogador 2 joga
            
            do{
                printf("Turno de %s\n", j2);
			    scanf("%d %d  %c", &p1, &p2, &peca);
				
				erros(i, p1, p2, peca, tab);

            }while((p1-1<0 || p1-1>3) || (p2-1<0 || p2-1>3) || (peca != 'b' && peca != 'c' && peca != 't')||(checar(peca, tab)== '1')||(tab[p1-1][p2-1] != '_'));
			tab[p1-1][p2-1] = peca;
			if(vencedor(tab) == -1){
				printf("%s vence!\n", j2);
				i=7;
			}
		}
        printTab(tab);
	}
	
	if(i != 8){
		printf("Fase de posicionamento acabou. Comeca fase de mover pecas\n");
		
		for(i=0; i<31; i++){
			if(i%2==0){ //se a rodada for par o jogador 1 joga
				printf("\nRodada %d\n", i/2);
				printf("%d", empate1(tab));
				if(empate1(tab)!=9){
					do{
						printf("Turno de %s\n", j1);
						scanf("%d %d  %c", &p1, &p2, &peca);
						
						if(peca != 'B' && peca != 'C' && peca != 'T'){
							printf("Essa peca nao existe. Digite outra:\n");
						}
						
						else{
							if(tab[p1-1][p2-1] != '_'){
								printf("Essa casa ja esta ocupada. Digite outra:\n");
							}
						}				
					}while((p1-1<0 || p1-1>3) || (p2-1<0 || p2-1>3) || (peca != 'B' && peca != 'C' && peca != 'T')||(checarlance(p1, p2, peca, tab)==1));
					lance(p1, p2, peca, tab);
					if(vencedor(tab) == 1){
						printf("%s vence!\n", j1);
						i=31;
					}
				}else{
					printf("EMPATE!\n");
					i = 40;
				}
			}
			else{ //se a rodada for impar o jogador 2 joga
				if(empate2(tab) !=9){
					do{
						printf("Turno de %s\n", j2);
						scanf("%d %d  %c", &p1, &p2, &peca);
						
						if(peca != 'b' && peca != 'c' && peca != 't'){
							printf("Essa peca nao existe. Digite outra:\n");
						}
						else{
							if(tab[p1-1][p2-1] != '_'){
								printf("Essa casa ja esta ocupada. Digite outra:\n");
							}
						}
					}while((p1-1<0 || p1-1>3) || (p2-1<0 || p2-1>3) || (peca != 'b' && peca != 'c' && peca != 't')||(tab[p1-1][p2-1] != '_')||(checarlance(p1, p2, peca, tab)==1));
					lance(p1, p2, peca, tab);
					if(vencedor(tab) == -1){
						printf("%s vence!\n", j2);
						i=31;
					}
				}else{
					printf("EMPATE!\n");
					i = 40;
				}
			}
			printTab(tab);
		
		}
	}
	
	
	
	
	
    //movimento do cavalo

    //movimento do bispo
    
    //movimento da torre
	
	//teste1
    
    return(0);
}
