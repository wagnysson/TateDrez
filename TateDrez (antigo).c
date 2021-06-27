// Wagnysson Moura Luz - 12558471
// Bruno Dias Moreira - 12624905

#include <stdio.h> //usada no geral
#include <math.h> //usada para funcao pow e sqrt
#include <stdlib.h> //usada para a funcao abs
#include <string.h> //usada para a funcao strcmp

//instrucoes de como jogar
void info(void){
	printf("Bem vindos ao TateDrez!\n\n");
	printf("COMO JOGAR?\nO jogo pode ser dividido em 2 fases, a FASE DE POSICIONAMENTO e a FASE DE MOVIMENTAR PECAS nas quais os jogadores realizam LANCES.\n\n");
	printf("LANCE - Para fazer um lance o jogador da vez digita um comando no formato 'p1 p2 peca', onde p1 eh o numero da linha e p2 o da coluna do tabuleiro (para) onde o jogador deseja posicionar/movimentar a peca que eh definida pelo terceiro item do comando (peca).\n");
	printf("RESTRICAO DOS VALORES\n1<=p1<=3\n1<=p2<=3\n");
	printf("O jogador 1 joga apenas com as pecas de letra maiuscula e o jogador 2 joga apenas com as pecas de letra minuscula sendo elas:\n");
	printf("C, c - CAVALO\nB, b - BISPO\nT, t - TORRE\n\n");
	printf("FASE DE POSICIONAMENTO - Os jogadores fazem lances de posicionamento alternados começando pelo jogador 1. Eles podem colocar suas pecas em qualquer casa do tabuleiro que esteja vazia.\n\n");
	printf("FASE DE MOVIMENTAR PECAS - Depois que todas as pecas estiverem posicionadas comeca a FASE DE MOVIMENTAR PECAS. Em cada rodada ha o turno do jogador 1 e o turno do jogador 2 e em cada um deles o jogador da vez movimenta uma de suas pecas. O OBJETIVO eh alinhar suas tres pecas como no jogo da velha (na diagonal, em linha ou em coluna), porem suas pecas se movimentam como no xadrez, ou seja, o CAVALO anda em L (uma casa na vertical ou na horizontal e outra na diagonal) e pode 'saltar' pecas que estejam no seu caminho, o BISPO anda apenas na diagonal quantas casas quiser sem poder 'saltar' pecas que estejam no seu caminho e a TORRE anda apenas na vertical ou na horizontal quantaas casas quiser sem poder 'saltar' pecas que estejam no seu caminho tambem.\n\n");
    printf("QUEM VENCE?\nO jogador que conseguir alinhas suas tres pecas em uma linha, coluna ou na diagonal primeiro vence.\n\n");
	printf("QUANDO DAH EMPATE?\nO empate ocorre quando nao ha movimentos possiveis para nenhuma peca de um jogador OU se depois de 30 rodadas (sem contar a fase de posicionamento) nenhum dos jogadores venceu.\n\n");
	printf("Para SAIR DO JOGO tecle ctrl+C\n\n\n");
	return;
}

//funcao que mostra o atual estado do tabuleiro
void printTab(char tab[3][3]){
    int m, n;
	int c[3];
	
	//inicializando o vetor das colunas
	c[0] = 1;
	c[1] = 2;
	c[2] = 3;
	
    for (m=0; m<3; m++){
		if(m==0){//escreve os numeros das colunas
			printf("   %3d%3d%3d\n", c[0], c[1], c[2]);
		}
        printf("%d |", m+1);//escreve o numero da linha e uma barra para separar
        for(n=0; n<3; n++){//escreve a matriz do tabuleiro
            printf("%3c", tab[m][n]);
        }
        printf("  |\n");//barra da direita
    }
	printf("\n");//espaco

    return;
}  

 //funcao que checa se uma peca ja esta no tabuleiro. flag = 1 a peca ja esta no tabuleiro, flag = 0 a peca ainda nao esta no tabuleiro, e flag = 2 a peca nao existe
int checar(char peca, char tab[3][3]){
	int i, j;
	char flag = 0;

	if((peca != 'c' && peca != 'b' && peca != 't' && peca != 'C' && peca != 'B' && peca != 'T')||peca == '_'){
		flag = 2;
	}
	else{
		//para cada posição do tabuleiro, checa se a peca ja esta la
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				if(tab[i][j] == peca){
					flag = 1;
				}
			}		
		}
	}
	return(flag);
}	



// confere se alguem venceu
int vencedor(char tab[3][3]){
	int i;
	int flag = 0;
	/*
	Valores da Tabela ASCII utilizados no programa
	B = 66
	C = 67
	T = 84
	b = 98
	c = 99
	t = 116
	_ = 95
	*/
	/*nessa repeticao eh verificado se em todas as posicoes de uma linha ha pecas que correspondem a valores menores que 85,
	ja que pela correspondecia da tabela ASCII as letras maiusculas utilizadas no codigo (B, C, T) tem valores menores que 85,
	se isso acontecer entao as letras que tem na linha sao as maiusculas utilizadas no codigo e como foi restringido que as 
	letras maiusculas que ha no tabuleiro sao apenas B, C e T, entao significa que na coluna ha essas letras e o jogador 1 que usa
	as maiusculas venceu. Isto eh testado para todas as linhas do tabuleiro com a repeticao.
	Se a condicao dos valores de pecas serem menores que 85 nao for satisfeita entao eh testado se as pecas no tabuleiro sao 
	maiores que 95, o que significa que na linha ha apenas as pecas minusculas do jogador 2 pela correspondencia com a tabela ASCII e
	usando o mesmo raciocinio da condicao anterior.
	Para indicar quem venceu ha uma variavel flag que recebe 1 se as condicoes que envolvem as letras maiusculas forem satfeitas
	e isso indica que o jogador 1 venceu e se isso nao acontecer mas as condicoes que envolvem as letras minusculas forem satisfeitas
	entao a flag recebe -1 indicando que o jogador 2 venceu*/
	for(i=0;i<3;i++){
		if((tab[i][0]<85) && (tab[i][1]<85) && (tab[i][2]<85)){
			flag = 1;
		}
		else{
			if((tab[i][0]>95) && (tab[i][1]>95) && (tab[i][2]>95)){
				flag = -1;
			}
		}
	}
	//pelo mesmo raciocinio acima aqui sao testadas as colunas
	for(i=0;i<3;i++){
		if((tab[0][i]<85) && (tab[1][i]<85) && (tab[2][i])<85){
			flag = 1;
		}
		else{
			if(tab[0][i]>95 && tab[1][i]>95 && tab[2][i]>95){
				flag = -1;
			}
		}	
	}
	//pelo mesmo raciocinio acima aqui eh testada a diagonal principal
	if((tab[0][0]<85) && (tab[1][1]<85) && (tab[2][2]<85)){
		flag = 1;
	}
	else{
		if(tab[0][0]>95 && tab[1][1]>95 && tab[2][2]>95){
			flag  = -1;
		}
	}
	//pelo mesmo raciocinio acima aqui eh testada a diagonal secundaria
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

//checa se um lance eh valido
int checarlance(int p1, int p2, char peca, char tab[3][3]){
	int i, j;
	int flag;
	flag = 0;
	
	//confere se a casa digitada esta vazia. Se nao esta, ja considera o lance invalido
	if(tab[p1-1][p2-1] != '_'){
		flag=1;
	}
	//se esta vazia, as demais checagens sao realizadas
	else{
	//verifica se a condicao para que a peca escolhida se mova eh satisfeita e devolve uma flag. se flag = 0 o movimento eh valido, se flag = 1 o movimento nao eh valido
		switch(peca){
			//para o bispo (B e b), é
			case 'b':
				for(i=0;i<3;i++){
					for(j=0;j<3;j++){
						if(tab[i][j] == peca){
							//primeiro, eh checado se o movimento foi de fato uma diagonal
							//eh possivel descobrir isso comparando o modulo das diferencas entre a casa digitada e a casa presente
							if(abs((p1-1)-i) == abs((p2-1)-j)){
								//depois, confere-se se o bispo esta tentando se movimentar mais de uma casa
								if(abs((p1-1)-i) == 2 && abs((p2-1)-j) == 2){
									//se esta, com certeza ira passar pela casa central do tabuleiro, entao checa-se se esta casa esta vazia
									if(tab[1][1] != '_'){
										flag = 1;
									}
								}else{
									flag = 0;
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
							//o movimento do cavalo sempre ocorre de tal forma que percorre distancia euclidiana de sqrt(5), entao checa-se isso
							//a condicao nao usa um simples == para evitar imprecisoes de float
							if((sqrt(5)-0.1 < sqrt(pow((i+1)-p1,2)+pow((j+1)-p2,2))) && (sqrt(pow((i+1)-p1,2)+pow((j+1)-p2,2)) < sqrt(5)+0.1)){
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
							//se o movimento digitado de fato foi de uma torre, entao com certeza ou a coordenada i ou a j se mantera constante
							//entao se as duas forem diferentes ja eh considerado invalido
							if((i != p1-1 && j != p2-1)){
								flag = 1;
							}else{
								//eh conferido se a torre andou mais de duas casas
								if(abs(p1-1-i) == 2 || abs(p2-1-j) == 2){
									//se andou duas casa pela linha i, entao passou pela coluna 1
									if(p1-1 == i){
										//assim, se a casa [i][1] nao esta vazia, o lance eh considerado invalido
										if(tab[i][1] != '_'){
											flag = 1;
										}
									//mesmo raciocinio caso andou-se duas casas pela coluna j
									}else{
										if(p2-1 == j){
											if(tab[1][j] != '_'){
												flag = 1;
											}
										}
									}
								//caso nao tenha andado duas casas, o lance ja eh considerado valido, pois ja foi checado antes se a casa desejada esta ocupada
								}else{
									flag=0;
								}
							}
						}
					}
				}	   
				break;
				
			//para o bispo do j1, acontece o mesmo que para o bispo do j2
			case 'B':
				for(i=0;i<3;i++){
					for(j=0;j<3;j++){
						if(tab[i][j] == peca){
							if(abs((p1-1)-i) == abs((p2-1)-j)){
								if(abs((p1-1)-i) == 2){
									if(tab[1][1] != '_'){
										flag = 1;
									}
								}else{
									flag = 0;
								}
							}else{
								flag = 1;
							}
						}
					}	
				}
				break;
				
			//para o cavalo do j1, acontece o mesmo que para o cavalo do j2
			case 'C':
				for(i=0;i<3;i++){
					for(j=0;j<3;j++){
						if(tab[i][j] == peca){
							if((sqrt(5)-0.1 < sqrt(pow((i+1)-p1,2)+pow((j+1)-p2,2))) && ((sqrt(pow((i+1)-p1,2)+pow((j+1)-p2,2)) < sqrt(5)+0.1))){
								flag = 0;
							}
							else{
								flag = 1;
							}   
						}
					}	   
				}
				break;
				
			//para a torre do j1, acontece o mesmo que para a torre do j2
			case 'T':
				for(i=0;i<3;i++){
					for(j=0;j<3;j++){
						if(tab[i][j] == peca){
							if((i != p1-1 && j != p2-1)){
								flag = 1;
							}else{
								if(abs(p1-1-i) == 2 || abs(p2-1-j) == 2){
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
									flag=0;
								}
							}
						}
					}
				}	   
				break;
				
			default:
				flag = 2; //o valor de 2 ao inves de 1 aqui eh importante para a funcao erros escrever "peca nao existe" ao inves de "movimento invalido"
		}
	}

    return(flag);	
}

//funcao que testa a posicao e a peca digitada pelo jogador e mostra mensagens de erro caso 
void erros(int vez, int p1, int p2, char peca, char tab[3][3], int jogo){
	int erro = 0;
	if((p1<1 || p1>3) || (p2<1 || p2>3)){
		printf("A casa que voce digitou nao existe. Faca outro lance:\n");
	}else{
		if(vez == 1){
			if((peca == 'b') || (peca == 'c') || (peca == 't')){
				printf("Essa peca nao eh sua. Faca outro lance:\n");
				erro = 1;
			}
		}else{
			if((peca == 'B') || (peca == 'C') || (peca == 'T')){
				printf("Essa peca nao eh sua. Faca outro lance:\n");
				erro = 1;
			}
		}
		if((checar(peca, tab) == 1) && (erro != 1) && (jogo == 1)){
			printf("Esta peca ja estah no tabuleiro. Faca outro lance:\n");
		}else{
			if((p1>=1 && p1<=3) && (p2>=1 && p2<=3) && (erro != 1) && (jogo == 1 || jogo == 2)){
				if((checarlance(p1, p2, peca, tab) == 1) && jogo == 2){
					printf("Movimento invalido. Faca outro lance:\n");
				}else{
					if(tab[p1-1][p2-1] != '_' && checar(peca, tab) != 2){
						printf("Essa casa ja esta ocupada. Faca outro lance:\n");
					}
					if(checar(peca, tab) == 2){
							printf("Peca nao existe. Faca outro lance:\n");
					}
					
				}
			}
		}
	}
	
	return;
}

//funcao que realiza um lance na segunda parte do jogo
//a funcao le a peca, procura onde essa peca esta no tabuleiro, substitui a posicao por um espaco vazio e faz a peca ocupar o lugar desejado
void lance(int p1, int p2, char peca, char tab[3][3]){
		int i, j;
	
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				if(tab[i][j] == peca){
					tab[i][j] = '_';
				}
			}	
		}
		tab[p1-1][p2-1]=peca;
		
		return;
    }

//checa se houve empate na vez do jogador 1 por falta de lances legais
int empate1(char tab[3][3]){
	int i, j, flag = 0;
	//para todas as casas, sera conferido se cada peca pode se movimentar para essa casa
	//caso exista pelo menos uma possibilidade, entao no final flag<9
	//assim, eh usado como criterio de empate se a funcao eh igual ou diferente de 9
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			if(checarlance(i+1, j+1, 'B', tab) != 0 && checarlance(i+1, j+1, 'C', tab) != 0 && checarlance(i+1, j+1, 'T', tab) != 0){
				flag = flag + 1;
			}
		}
	}
	return(flag);
}

//checa se houve empate na vez do jogador 2 por falta de lances legais
int empate2(char tab[3][3]){
	int i, j, flag = 0;
	//funciona da mesma forma que empate1, exceto que para as pecas do jogador 2
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			if(checarlance(i+1, j+1, 'b', tab) != 0 && checarlance(i+1, j+1, 'c', tab) != 0 && checarlance(i+1, j+1, 't', tab) != 0){
				flag = flag + 1;
			}
		}
	}
	return(flag);
}

//le o lance desejado e confere, atraves de criterios e outras funcoes, se eh valido
void leitura(char tab[3][3], int jogo, int vez){
	int p1, p2; //p1 - linha do tabuleiro, p2 - coluna do tabuleiro.
    char peca; // peca escolhida para mover
	
	printf("Faca um lance:\n");
	
	if(jogo == 1){
		if(vez == 1){
			//o jogador fica preso no looping do/while ateh que ele faca um lance valido
			do{
				//le o lance de posicionamento do jogador 1
				scanf("%d %d  %c", &p1, &p2, &peca);

				erros(vez, p1, p2, peca, tab, jogo);
			/*nesse while eh checado se: 
			a casa digitada nao existe, ou seja, se esta fora da faixa de 1 a 3 (que depois eh convertida para 0 a 2 para trabalhar com as matrizes);
			se a peca nao existe ou nao eh do jogador da vez;
			se a casa digitada ja esta ocupada;
			se a peca digitada ja esta no tabuleiro;
			respectivamente e analogo para os outros whiles, se uma dessas condicoes for verdadeira o lance eh invalido e o jogador da vez deve fazer outro lance*/
			}while((p1<1 || p1>3) || (p2<1 || p2>3) || (peca != 'B' && peca != 'C' && peca != 'T') || (tab[p1-1][p2-1] != '_') || (checar(peca, tab) != 0));
			//depois de o jogador fazer um lance valido a peca eh colocada no tabuleiro na posicao escolhida
			tab[p1-1][p2-1] = peca;
			printTab(tab);
		}
		else{
			
			do{
					scanf("%d %d  %c", &p1, &p2, &peca);
					
					erros(vez, p1, p2, peca, tab, jogo);

				}while((p1<1 || p1>3) || (p2<1 || p2>3) || (peca != 'b' && peca != 'c' && peca != 't') || (tab[p1-1][p2-1] != '_') || (checar(peca, tab) != 0));
				tab[p1-1][p2-1] = peca;
				printTab(tab);
			
		}
	}
	else{
		if(vez == 1){
			
			//nesse do while acontece o mesmo que no do wile do primeiro momento do jogo,
			//exceto que eh usada a funcao checarlance ao inves da checar
			do{
				scanf("%d %d  %c", &p1, &p2, &peca);
				
				erros(vez, p1, p2, peca, tab, jogo);	

			}while((p1<1 || p1>3) || (p2<1 || p2>3) || (peca != 'B' && peca != 'C' && peca != 'T')||(checarlance(p1, p2, peca, tab) != 0));
			lance(p1, p2, peca, tab);
			printTab(tab);
		}
		else{
			
			do{
						scanf("%d %d  %c", &p1, &p2, &peca);
						
						erros(vez, p1, p2, peca, tab, jogo);	

					}while((p1<1 || p1>3) || (p2<1 || p2>3) || (peca != 'b' && peca != 'c' && peca != 't') || (tab[p1-1][p2-1] != '_') || (checarlance(p1, p2, peca, tab) != 0));
					lance(p1, p2, peca, tab);
					printTab(tab);
			
		}
		
	}
}

int main(void){
    //declarando as varaveis
    char j1[20], j2[20]; // recebe o nome dos jogadores
    char tab[3][3]; //recebe o tabuleiro
    int i, j; //contadores
	int vez = 0; //indica de quem eh a vez de jogar, se vez = 1 entao eh a vez do jogador 1, se v = 2 eh a vez do jogador 2
	int jogo = 0; //indica qual fase do jogo esta acontecendo, se for a fase de posicionamento entao jogo = 1, se for a fase de movimentacao de pecas entao jogo = 2
	
	
	info();
	
    //jogadores dão entrada em seus nomes
	printf("Jogador 1, digite como deseja ser chamado: ");
	scanf("%s", j1);
	do{
		printf("Jogador 2, digite como deseja ser chamado: ");
		scanf("%s", j2);
	}while(strcmp(j1, j2) == 0);

    //colocando casas vazias no tabuleiro que sao representadas por '_'
    for (i=0; i<3; i++){
        for(j=0; j<3; j++){
            tab[i][j] = '_';
		}
    }
	printf("FASE DE POSICIONAMENTO COMECOU!\n\n");
	//neste programa o usuario da entrada nas posicoes das pecas de 1 a 3 para que seja mais intuitivo para ele, mas na hora de utilizar estas entradas nas matrizes do programa nos subtraimos 1 para que os valores sejam colocados nos lugares corretos
	//FASE DE POSICIONAMENTO
	//essa repeticao vai do 1 ao 6 para que ocorram 3 rodadas de posicionamento ja que as rodadas iniciam quando eh a vez de o jogador 1 fazer o lance, no caso, quando i eh par
	for(i=0; i<6; i++){
		jogo = 1;
		if(i%2 == 0){
			//printa a rodada atual
			printf("\nRodada %d\n", (i/2)+1);
			printf("Turno de %s\n", j1);
			printTab(tab);
			vez = 1;
			leitura(tab, jogo, vez);
			//verifica se o jogador 1 eh o vencedor, se for printa que ele venceu e i recebe 7 para sair do looping da fase de posicionamento
			if(vencedor(tab) == 1){
				printTab(tab);
				printf("%s vence!\n", j1);
				i=7;
			}//se o jogador 1 nao venceu entao eh o turno do jogador 2 e o codigo abaixo eh executado. Eh analogo ao trecho de cima mas para o jogador 2
			else{
				printf("Turno de %s\n", j2);
				vez = 2;
				leitura(tab, jogo, vez);
				if(vencedor(tab) == -1){
					printTab(tab);
					printf("%s venceu!\n", j2);
					i=7;
				}
			}
		}
	}

	//FASE DE MOVIMENTAR PECAS
	if(i != 8){
		printf("FASE DE POSICIONAMENTO ACABOU.\nCOMECA FASE DE MOVER PECAS!\n");
		
		for(i=0; i<60; i++){
			jogo = 2;
			if(i%2==0){ //se o i eh par o jogador 1 joga
				printf("\nRodada %d\n", (i/2)+1);
				//antes de pedir um lance para o jogador, eh checado se houve empate
				if(empate1(tab)!=9){
					printf("Turno de %s\n", j1);
					vez = 1;
					leitura(tab, jogo, vez);
					//depois que leu-se a jogada, eh checado se houve vitoria
					if(vencedor(tab) == 1){
						printf("%s vence!\n", j1);
						i=70;
					}
				}else{
					printf("EMPATE: %s nao tem lances possiveis\n", j1);
					i = 70;
				}
			}
			else{ //se o i for impar o jogador 2 joga
			
				//antes de pedir um lance para o jogador, eh checado se houve empate
				if(empate2(tab) !=9){
					printf("Turno de %s\n", j2);
					vez = 2;
					leitura(tab, jogo, vez);
					//depois que leu-se a jogada, eh checado se houve vitoria
					if(vencedor(tab) == -1){
						printf("%s vence!\n", j2);
						i=70;
					}
				}else{
					printf("EMPATE: %s nao tem lances possiveis\n", j2);
					i = 70;
				}
			}
		
		}
	}
	//caso tenha um empate por falta de lance ou uma vitoria, i != 31
	//entao o empate de jogadas de mais so acontece se o for anterior acabar no i=31
	if(i == 60){
		printf("EMPATE: Ocorreram mais de 30 jogadas e nao houve vitorias");
	}
	
	
    return(0);
}
