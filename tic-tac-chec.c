// Wagnysson Moura Luz - 12558471
// Bruno Dias Moreira - 12624905

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//ordem da matriz (3 linhas e 3 colunas, no caso)
#define N 3

//checa se um lance eh valido
int checarlance(int p1, int p2, char peca, char tab[N][N]){
	int i, j;
	int flag;
	flag = 0;

	//verifica se a condicao para que a peca escolhida se mova eh satisfeita
    switch(peca){
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
	if((tab[0][0]<85) && (tab[1][1]<85) && (tab[2][2]<85)){
		flag = 1;
	}
	else{
		if(tab[0][0]>95 && tab[1][1]>95 && tab[2][2]>95){
			flag  = -1;
		}
	}
	
	if(tab[0][2]<85 && tab[1][1]<85 && tab[2][0]<85){
		flag = 1;
	}
	else{
		if(tab[0][2]>95 && tab[1][1]>95 && tab[2][0]>95){
			flag  = -1;
		}
	}
	return(flag);
}

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

int main(){
    //declarando as varaveis
    char j1[20], j2[20]; // recebe o nome dos jogadores
    char tab[3][3];
    int i, j; //contador
    int p1, p2; //p1 - posiicao 1, p2 - posicao 2.
    char peca; // peca escolida
	
	//funcao que realiza um lance na segunda parte do jogo
	
    

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
		if(i%2==0){
			printf("Rodada %d\n", i/2);
		}
		if(i%2==0){ //se a rodada for par o jogador 1 joga
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
            }while((p1-1<0 || p1-1>3) || (p2-1<0 || p2-1>3) || (peca != 'B' && peca != 'C' && peca != 'T')||(checar(peca, tab)== '1')|| (tab[p1-1][p2-1] != '_'));
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
				
				if(peca != 'b' && peca != 'c' && peca != 't'){
					printf("Essa peca nao existe. Digite outra:\n");
				}
				else{
					if(tab[p1-1][p2-1] != '_'){
						printf("Essa casa ja esta ocupada. Digite outra:\n");
					}
				}
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
				printf("Rodada %d\n", i/2);
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
