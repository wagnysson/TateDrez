// Wagnysson Moura Luz - 12558471
// Bruno Dias Moreira - 12624905

#include <stdio.h> //usada no geral
#include <math.h> //usada para funcao pow e sqrt
#include <stdlib.h> //usada para a funcao abs
#include <string.h> //usada para a funcao strcmp
#include <time.h>//usada para o funcionamento correto da funcao rand()

//struct que guarda informacoes que serao usadas nas funcoes de lances do computador
typedef struct{
	int p1;
	int p2;
	char peca;
}lanceC;

//instrucoes de como jogar
void info(void){
	printf("Bem vindos ao TateDrez!\n\n");
	printf("COMO JOGAR?\nO jogo pode ser dividido em 2 fases, a FASE DE POSICIONAMENTO e a FASE DE MOVIMENTAR PECAS nas quais os jogadores realizam LANCES.\n\n");
	printf("LANCE - Para fazer um lance o jogador da vez digita um comando no formato 'p1 p2 peca', onde p1 eh o numero da linha e p2 o da coluna do tabuleiro (para) onde o jogador deseja posicionar/movimentar a peca que eh definida pelo terceiro item do comando (peca).\n");
	printf("RESTRICAO DOS VALORES\n1<=p1<=3\n1<=p2<=3\n");
	printf("O jogador 1 joga apenas com as pecas brancas (de letra maiuscula) e o jogador 2 joga apenas com as pecas pretas (de letra minuscula) sendo elas:\n");
	printf("C, c - CAVALO\nB, b - BISPO\nT, t - TORRE\n\n");
	printf("FASE DE POSICIONAMENTO - Os jogadores fazem lances de posicionamento alternados começando pelo jogador 1. Eles podem colocar suas pecas em qualquer casa do tabuleiro que esteja vazia.\n\n");
	printf("FASE DE MOVIMENTAR PECAS - Depois que todas as pecas estiverem posicionadas comeca a FASE DE MOVIMENTAR PECAS. Em cada rodada ha o turno do jogador 1 e o turno do jogador 2 e em cada um deles o jogador da vez movimenta uma de suas pecas. O OBJETIVO eh alinhar suas tres pecas como no jogo da velha (na diagonal, em linha ou em coluna), porem suas pecas se movimentam como no xadrez, ou seja, o CAVALO anda em L (uma casa na vertical ou na horizontal e outra na diagonal) e pode 'saltar' pecas que estejam no seu caminho, o BISPO anda apenas na diagonal quantas casas quiser sem poder 'saltar' pecas que estejam no seu caminho e a TORRE anda apenas na vertical ou na horizontal quantas casas quiser sem poder 'saltar' pecas que estejam no seu caminho tambem.\n\n");
	printf("QUEM VENCE?\nO jogador que conseguir alinhas suas tres pecas em uma linha, coluna ou na diagonal primeiro vence.\n\n");
	printf("QUANDO DAH EMPATE?\nO empate ocorre quando nao ha movimentos possiveis para nenhuma peca de um jogador OU se depois de 30 rodadas (sem contar a fase de posicionamento) nenhum dos jogadores venceu.\n\n");
	printf("Para SAIR DO JOGO tecle ctrl+C\n\n\n");
	return;
}

//funcao que mostra o atual estado do tabuleiro
void printTab(char tab[3][3]){
    int m, n;//contadores
	int c[3];//vetor que guarda os numeros das colunas
	
	//inicializando o vetor que guarda os numeros das colunas
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
	printf("\n");//pula linha

    return;
}  

 //funcao que checa se uma peca ja esta no tabuleiro. flag = 1 a peca ja esta no tabuleiro, flag = 0 a peca ainda nao esta no tabuleiro, e flag = 2 a peca nao existe (a explicacao das flags esta dentro e fora da funcao para que facilite a leitura do codigo dentro das funcoes e depois na funcao main)
int checar(char peca, char tab[3][3]){
	int i, j;//contadores
	char flag = 0;//variavel flag que indica as coisas citadas na explicacao da funcao

	//se a peca for diferente das pecas dos dois jogadores flag recebe 2 indicando que a peca nao existe
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

// confere se alguem venceu. se a flag = 1 entao o jogador 1 venceu, se flag = -1 o jogador 2 venceu
int vencedor(char tab[3][3]){
	int i;//contador
	int flag = 0; // variavel flag que indica o que foi citado no comentario explicando a funcao
	/*
	Valores da Tabela ASCII utilizados no programa (nao necessariamente foram usados no programa, mas foram usados para pensar no algoritmo)
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
	maiores que 95, o que significa que na linha ha apenas as pecas minusculas do jogador 2 - pela correspondencia com a tabela ASCII e
	usando o mesmo raciocinio da condicao anterior.
	Para indicar quem venceu ha uma variavel flag que recebe 1 se as condicoes que envolvem as letras maiusculas forem satisfeitas
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

//checa se um lance eh valido. se for flag = 0 e se nao for flag = 1
int checarlance(int p1, int p2, char peca, char tab[3][3]){
	int i, j; //contadores
	int flag;// indica o que foi citado na breve explicacao da funcao acima
	//inicializando a flag
	flag = 0;
	
	//verifica se a condicao para que a peca escolhida se mova eh satisfeita e devolve uma flag. se flag = 0 o movimento eh valido, se flag = 1 o movimento nao eh valido
	//nao eh checado se a casa esta vazia, para proposito de mensagens de erro na funcao erros
	//a casa estar vazia ou nao eh checado separadamente toda vez que necessario
	switch(peca){
		//para o bispo (B e b), é
		case 'b':
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){
					//verifica em que local do tabuleiro a peca esta para que seus indices sejam utilizados mais a frente (isto ocorre em todas as verificacoes desta funcao)
					if(tab[i][j] == peca){
						//primeiro, eh checado se o movimento foi de fato uma diagonal
						//eh possivel descobrir isso comparando o modulo das diferencas entre a casa digitada e a casa presente. O bispo deve se movimentar a mesma quantidade de casas na horizontal e na vertical para que haja o movimento em diagonal corretamente
						if(abs((p1-1)-i) == abs((p2-1)-j)){
							//depois, eh conferido se o bispo esta tentando se movimentar mais de uma casa
							if(abs((p1-1)-i) == 2 && abs((p2-1)-j) == 2){
								//se estah, com certeza ira passar pela casa central do tabuleiro, entao checa-se se esta casa esta vazia, se nao estiver, entao flag = 1, caso contrario flag = 0.
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
								if(p1-1 == i){
									//assim, se a casa [i][1] nao esta vazia, o lance eh considerado invalido
									if(tab[i][1] != '_'){
										flag = 1;
									}
								//mesmo raciocinio caso tenha andado duas casas pela coluna j
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

    return(flag);	
}

//funcao que testa a posicao e a peca digitada pelo jogador e mostra mensagens de erro caso seja necessario 
void erros(int vez, int p1, int p2, char peca, char tab[3][3], int jogo){
	int erro = 0; // indica se uma peca do jogador adversario foi usada e recebe 1 para indicar isto. eh importante para que nao apareca a algumas mensagens de erro a mais quando isto acontecer.
	//verifica se a linha e a coluna digitada pelo jogador da vez esta na faixa designada (1 a 3)
	if((p1<1 || p1>3) || (p2<1 || p2>3)){
		printf("A casa que voce digitou nao existe. Faca outro lance:\n");
	}else{
		//caso esteja na faixa, verifica se eh a vez do jogador 1 e se ele tiver digitado as pecas do jogador 2 aparece uma mensagem dizendo que estas pecas nao sao dele
		if(vez == 1){
			if((peca == 'b') || (peca == 'c') || (peca == 't')){
				printf("Essa peca nao eh sua. Faca outro lance:\n");
				erro = 1;
			}
		//o mesmo ocorre para o jogador 2
		}else{
			if((peca == 'B') || (peca == 'C') || (peca == 'T')){
				printf("Essa peca nao eh sua. Faca outro lance:\n");
				erro = 1;
			}
		}
		//verifica se a peca ja estah no tabuleiro, se nao foi mostrada alguma mensagem de erro logo antes desta e se estah na fase de posicionamento, jah que esta mensagem so deve aparecer na fase de posicionamento (jogo = 1)
		if((checar(peca, tab) == 1) && (erro != 1) && (jogo == 1)){
			printf("Esta peca ja estah no tabuleiro. Faca outro lance:\n");
		}else{
			if((erro != 1)){
				//se a casa digitada esta ocupada, mas o lance nao seria valido, teremos flag = 1
				//se nao esta ocupada, mas o lance seria invalido, teremos flag = 1
				//se esta ocupada, e o lance seria valido, teremos flag = 0
				if((checarlance(p1, p2, peca, tab) == 1) && jogo == 2){
					printf("Movimento invalido. Faca outro lance:\n");
				}else{
					if(checarlance(p1,p2,peca,tab)==0 && (tab[p1-1][p2-1] != '_') && jogo == 2){
						printf("Essa casa ja esta ocupada. Faca outro lance:\n");
					}
					//checa se a casa jah estah ocupada e mostra a mensagem de erro caso jah esteja
					if(tab[p1-1][p2-1] != '_' && checar(peca, tab) != 2 && jogo == 1){
						printf("Essa casa ja esta ocupada. Faca outro lance:\n");
					}
					//checa se a peca existe, se nao, mostra a mensagem de erro
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
		int i, j;//contadores
	
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

//checa se houve empate na vez do jogador 1 por falta de lances possiveis
int empate1(char tab[3][3]){
	int i, j, flag = 0;
	//para todas as casas, sera conferido se cada peca pode se movimentar para essa casa
	//caso exista pelo menos uma possibilidade, entao no final flag<9
	//assim, eh usado como criterio de empate se a funcao eh igual ou diferente de 9
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			if((checarlance(i+1, j+1, 'B', tab) != 0 && checarlance(i+1, j+1, 'C', tab) != 0 && checarlance(i+1, j+1, 'T', tab) != 0)||(tab[i][j] != '_')){
				flag = flag + 1;
			}
		}
	}
	return(flag);
}

//checa se houve empate na vez do jogador 2 por falta de lances possiveis
int empate2(char tab[3][3]){
	int i, j, flag = 0;
	//funciona da mesma forma que empate1, exceto que para as pecas do jogador 2
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			if((checarlance(i+1, j+1, 'b', tab) != 0 && checarlance(i+1, j+1, 'c', tab) != 0 && checarlance(i+1, j+1, 't', tab) != 0) || (tab[i][j] != '_')){
				flag = flag + 1;
			}
		}
	}
	return(flag);
}

//checa as jogadas possiveis do jogador 2 no modo de jogo jogador vs computador, guarda a jogada com que o jogador 2 venceria se for possivel(na primeira fase de jogo) e retorna 1 se o jogador 2 venceria com essa jogada e 0 se ele nao tem como vencer
int posvit2(char tab[3][3], int jogo, lanceC jogada[1]){
	char taba[3][3];//tabuleiro de analise, os testes de jogadas possiveis serao feitos nele
	lanceC lances[27];//guarda os lances possiveis de serem feitos
	int i, j, k, l, m;//contadores
	
    //tabela de analise recebe o estado atual da tabela do jogo
	for(i=0; i<3;i++){
		for(j=0; j<3; j++){
			taba[i][j] = tab[i][j];
		}
	}
	
	//k inicia com 0 porque contara a quantidade de jogadas que o vetor lances vai conter
	k=0;
    //se o jogo estiver na fase de posicionamento sao guardados as posicoes (coordenadas p1 e p2 da casa e a peca) possiveis de cada peca do jogador no vetor lances, isto caso ela nao esteja no tabuleiro ainda	
	if(jogo==1){
		if(checar('b', tab)==0){
			for(i=0; i<3; i++){
				for(j=0; j<3; j++){				
					lances[k].p1 = i;
					
					lances[k].p2 = j;
					
					lances[k].peca = 'b';
					k++;
				}
			}
		}
		if(checar('c', tab)==0){
			for(i=0; i<3; i++){
				for(j=0; j<3; j++){
					lances[k].p1 = i;
					
					lances[k].p2 = j;
					
					lances[k].peca = 'c';
					k++;
				}
			}
		}
		if(checar('t', tab)==0){
			for(i=0; i<3; i++){
				for(j=0; j<3; j++){
					lances[k].p1 = i;
					
					lances[k].p2 = j;
					
					lances[k].peca = 't';
					k++;
				}
			}
		}
	}else{
        //se o jogo estiver na fase de movimentar pecas sao guardados os lances possiveis de cada peca do jogador no vetor lances
		for(i=0; i<3; i++){
			for(j=0; j<3; j++){		
				if(tab[i][j] == '_' && checarlance(i+1, j+1, 'b', tab) == 0){		
					lances[k].p1 = i;
					
					lances[k].p2 = j;
					
					lances[k].peca = 'b';
					k++;
				}
			}
		}
		for(i=0; i<3; i++){
			for(j=0; j<3; j++){
				if(tab[i][j] == '_' && checarlance(i+1, j+1, 'c', tab) == 0){
					lances[k].p1 = i;
					
					lances[k].p2 = j;
					
					lances[k].peca = 'c';
					k++;
				}
			}
		}
		for(i=0; i<3; i++){
			for(j=0; j<3; j++){
				if(tab[i][j] == '_' && checarlance(i+1, j+1, 't', tab) == 0){
					lances[k].p1 = i;
					
					lances[k].p2 = j;
					
					lances[k].peca = 't';
					k++;
				}
			}
		}
	}
    //se estiver na fase de posicionamento as jogadas guardadas no vetor lances sao feitas quando possivel
	if(jogo==1){
		for(i=0;i<k;i++){
			if(taba[lances[i].p1][lances[i].p2] == '_'){
				taba[lances[i].p1][lances[i].p2] = lances[i].peca;
			}
            //depois que a jogada eh feita, eh verificado se o jogador venceu, se sim, a jogada eh guardada no vetor jogada e a funcao retorna 1
			if(vencedor(taba) == -1){
				jogada[0].p1 = lances[i].p1;
				jogada[0].p2 = lances[i].p2;
                //verifica se a torre ou o cavalo do computador jah estao no tabuleiro, se um dos dois ainda nao estiver, entao eh colocado na posicao em que o jogador ganharia para evitar que o computador perca
                if(checar('T', tab) == 0){
                    jogada[0].peca = 'T';
                    return(1);
                }
                if(checar('C', tab) == 0){
                    jogada[0].peca = 'C';
                    return(1);
                }
				return(1);
			}
			else{
                //se o jogador nao venceu, entao o tabuleiro volta para o estado anterior e outra jogada ou posicionamento eh testado
				for(l=0; l<3;l++){
					for(m=0; m<3; m++){
						taba[l][m]= tab[l][m];
					}
				}
			}
		}
        //caso o jogador nao venca de forma alguma na rodada, a funcao retorna 0 
		return(0);
	}
	else{
        //se for a fase de movimentar pecas os lances guardados no vetor lances sao feitos
		for(i=0;i<k;i++){
			lance(lances[i].p1 +1, lances[i].p2 +1, lances[i].peca, taba);
			if(vencedor(taba) == -1){
				return(1);
			}
			else{
				for(l=0; l<3;l++){
					for(m=0; m<3; m++){
						taba[l][m]= tab[l][m];
					}
				}
			}
		}
	}
	return(0);
	
}

//verifica as jogadas possiveis do computador e guarda a melhor possivel no vetor jogada, se nao der para fazer a melhor jogada entao guarda uma jogada aleatoria no vetor jogada
void lancepc(char tab[3][3], int jogo, lanceC jogada[1]){
	
	lanceC lances[18], lancesBons[10];//vetores que guardam os lances
	int i, j, k, k2, l, m;//contadores
	char taba[3][3];//tabela de analise, analoga a da funcao posvit2
	//define a seed da funcao rand() usando o horario no momento de execucao
    srand(time(NULL));
    //tabela de analise recebe o estado atual do tabuleiro	
	for(i=0; i<3;i++){
		for(j=0; j<3; j++){
			taba[i][j]= tab[i][j];
		}
	}
	//k conta quantas jogadas o vetor lances vai guardar
	k=0;
    //se o jogo estiver na fase de posicionamentos, sao guardados os posicionamentos possiveis do cavalo e da torre caso eles nao estejam no tabuleiro ainda, ja que o bispo sempre eh a primeira jogada do computador
	if(jogo==1){
		if(checar('C', tab)==0){
			for(i=0; i<3; i++){
				for(j=0; j<3; j++){
					lances[k].p1 = i;
					
					lances[k].p2 = j;
					
					lances[k].peca = 'C';
					k++;
				}	
			}
		}
		if(checar('T', tab)==0){
			for(i=0; i<3; i++){
				for(j=0; j<3; j++){
					lances[k].p1 = i;
					
					lances[k].p2 = j;
					
					lances[k].peca = 'T';
					k++;
				}
			}
		}
	}else{
        //se estiver na fase de movimentar pecas, entao sao guardados os lances possiveis para as 3 pecas do computador
		for(i=0; i<3; i++){
			for(j=0; j<3; j++){
				if(tab[i][j] == '_' && checarlance(i+1, j+1, 'B', tab) == 0){
					lances[k].p1 = i;
					
					lances[k].p2 = j;
					
					lances[k].peca = 'B';
					k++;
				}
			}	
		}
		for(i=0; i<3; i++){
			for(j=0; j<3; j++){
				if(tab[i][j] == '_' && checarlance(i+1, j+1, 'C', tab) == 0){
					lances[k].p1 = i;
					
					lances[k].p2 = j;
					
					lances[k].peca = 'C';
					k++;
				}
			}	
		}
		for(i=0; i<3; i++){
			for(j=0; j<3; j++){
				if(tab[i][j] == '_' && checarlance(i+1, j+1, 'T', tab) == 0){
				lances[k].p1 = i;
				
				lances[k].p2 = j;
				
				lances[k].peca = 'T';
				k++;
				}
			}
		}
	}

	if(jogo==1){
		for(i=0;i<k;i++){
			if(taba[lances[i].p1][lances[i].p2] == '_'){
                //faz os lances guardados no vetor lances na tabela de analise
				taba[lances[i].p1][lances[i].p2] = lances[i].peca;
			}
            //verifica se o computador venceu com o lance feito, se sim, retorna o lance dentro do vetor jogada
			if(vencedor(taba)==1){
				jogada[0].p1 = lances[i].p1;
				jogada[0].p2 = lances[i].p2;
				jogada[0].peca = lances[i].peca;
				return;
			}else{
                //se nao venceu, volta o tabuleiro de analise para o estado anterior e testa a proxima jogada
				for(l=0; l<3;l++){
					for(m=0; m<3; m++){
						taba[l][m]= tab[l][m];
					}
				}
			}
		}
        //verifica as jogadas do jogador, caso ele possa vencer com alguma jogada, essa jogada eh guardada e o computador tenta colocar uma peca nessa casa de modo a impedir o jogador de ganhar
		if(posvit2(taba, jogo, jogada)==1){
			return;
		}
        //caso nao haja jogada que venca para que os testes acima gerem jogadas, eh feita uma jogada aleatoria
		do{
			jogada[0].p1 = (rand() % 3);
			jogada[0].p2 = (rand() % 3);
			if((rand() % 2)==0){
				jogada[0].peca = 'C';
			}else{
				jogada[0].peca = 'T';
			}
		}while(tab[jogada[0].p1][jogada[0].p2] != '_' || checar(jogada[0].peca, tab) != 0);
		return;
	}
	else{
        //se estiver na fase de movimentar pecas as jogadas guardadas no vetor lances sao testadas e se com alguma delas o computador vencer, ela eh guardada no vetor jogada e a funcao se encerra
		for(i=0;i<k;i++){
			lance(lances[i].p1 +1, lances[i].p2 +1, lances[i].peca, taba);
			
			if(vencedor(taba)==1){
				jogada[0].p1 = lances[i].p1;
				jogada[0].p2 = lances[i].p2;
				jogada[0].peca = lances[i].peca;
				return;
			}else{
				for(l=0; l<3;l++){
					for(m=0; m<3; m++){
						taba[l][m]= tab[l][m];
					}
				}
			}
		}
		k2=0; //o contador do numero de lances que impedem vitoria eh colocado como 0
		for(i=0; i<k; i++){
			
			//cada lance possivel eh realizado em taba
			lance(lances[i].p1 +1, lances[i].p2 +1, lances[i].peca, taba);
			//se ao realizar esse lance o oponente nao tem como ganhar imediatamente, guarda-se esse lance no vetor lancesBons e adiciona-se 1 a k2
			if(posvit2(taba, jogo, jogada)!=1){
				lancesBons[k2].p1 = lances[i].p1;
				lancesBons[k2].p2 = lances[i].p2;
				lancesBons[k2].peca = lances[i].peca;
				k2++;
			}
			//depois do lance ser analizado, o tabuleiro de analise volta a ser igual ao tabuleiro inicial
			for(l=0; l<3;l++){
				for(m=0; m<3; m++){
					taba[l][m]= tab[l][m];
				}
			}
		}
		//ao final dessa repeticao, todos os lances que nao levam a uma derrota imediata estarao armazenados em lancesBons
		
		//se k2 eh menor que 1, nao foi encontrado nenhum lance que impede derrota imediata, entao eh jogado um lance aleatorio dentre os disponiveis
		if(k2<1){
		i= rand()%k;
		jogada[0].p1 = lances[i].p1;
		jogada[0].p2 = lances[i].p2;
		jogada[0].peca = lances[i].peca;
		return;
		}
		//caso contrario, escolhe-se um lance aleatorio dentre aqueles que nao levam a uma derrota imediata
		i= rand()%k2;
		jogada[0].p1 = lancesBons[i].p1;
		jogada[0].p2 = lancesBons[i].p2;
		jogada[0].peca = lancesBons[i].peca;
		return;
		
	}
}

//faz as jogadas do computador
void pcjoga(int i, char tab[3][3], int jogo, lanceC jogada[1]){
	if(jogo == 1){
        //se estiver na fase de posicionamentos com primeira jogada coloca o Bispo branco na casa do meio do tabuleiro
		if(i == 0){
			tab[1][1] = 'B';
            return;
		}
        //na fase de posicionamentos se for a segunda jogada do computador ele verifica se tem alguma peca nos cantos, se tiver ele verifica qual a melhor jogada
        //jah que se as pecas estiverem exatamente em cima, embaixo, a esquerda ou a direita do Bispo branco jah ha um algoritmo pronto pra o computador vencer
        //que eh justamente o que vem logo abaixo 
		if(i == 2){
			if((tab[0][0] != '_' || tab[0][2] != '_' || tab[2][0] != '_' || tab[2][2] != '_')){
                lancepc(tab, jogo, jogada);
                tab[jogada[0].p1][jogada[0].p2] = jogada[0].peca;
                jogada[0].p1 = -1;// essa variavel eh usada como flag para checar depois se o computador joga pela lancepc ou pelo algoritmo pronto
                return;
		    }
			//caso o oponente nao tenha colocado uma peca no canto, coloca-se um cavalo em um canto do lado da peca do oponente
			if(tab[0][1] != '_'){
				tab[0][0] = 'C';
				return;
			}
			if(tab[1][0] != '_'){
				tab[0][0] = 'C';
				return;
			}
			if(tab[1][2] !='_'){
				tab[2][2] = 'C';
				return;
			}
			if(tab[2][1] != '_'){
				tab[2][2] = 'C';
				return;
			}
		}
        //no terceiro posicionamento do computador ele verifica se entrou no fluxo das pecas do canto, se sim, ele executa o primeiro if, se nao entao eh o fluxo da peca exatamente a direita/esquerda/abaixo/acima do bispo branco
		if(i == 4){
			if(jogada[0].p1==-1){
				lancepc(tab, jogo, jogada);
				tab[jogada[0].p1][jogada[0].p2] = jogada[0].peca;
				jogada[0].p1 = -1;
				return;
			}
			if(tab[0][0] == 'C' && tab[2][2] == '_' && checar('T', tab)==0){
				tab[2][2] = 'T';
				return;
			}else{
				if(tab[0][1] == '_' && checar('T', tab)==0 && tab[0][0] == 'C'){
					tab[0][1] = 'T';
					return;
				}else{
					if(checar('T', tab)==0 && tab[0][0] == 'C'){
						tab[1][0] = 'T';
						return;
					}
				}
			}
			if(tab[2][2] == 'C' && tab[0][0] == '_' && checar('T', tab)==0){
				tab[0][0] = 'T';
				return;
			}else{
	
				if(tab[2][1] == '_' && checar('T', tab)==0 && tab[2][2] == 'C'){
					tab[2][1] = 'T';
					return;
				}else{
					if(checar('T', tab)==0 && tab[2][2] == 'C'){
						tab[1][2] = 'T';
						return;
					}
				}
			}
			//ao final do algoritmo pronto, sera criada uma ameaca dupla de vitoria do j1, e o j2 nao consegue impedir as duas ao mesmo tempo
			//assim, na fase dois de jogo, a lancepc encontrara o lance que vence e ira joga-lo
		}
	}else{
        //na fase de mover pecas eh feita a verificacao das melhores jogadas possiveis na funcao lancepc e depois eh feito o lance com a jogada obtida
		lancepc(tab, jogo, jogada);
		lance(jogada[0].p1+1, jogada[0].p2+1, jogada[0].peca, tab);
	}
	return;
}
//le o lance desejado e confere, atraves de criterios e outras funcoes, se eh valido
void leitura(int i, char tab[3][3], int jogo, int vez, int mododejogo, lanceC jogada[1]){
	char p1, p2; //p1 - linha do tabuleiro, p2 - coluna do tabuleiro.
    char peca; // peca escolhida para mover
	int intermediario;
	
	if(mododejogo == 1){
		printf("Faca um lance:\n");
		
		if(jogo == 1){
			if(vez == 1){
				//o jogador fica preso no looping do/while ateh que ele faca um lance valido
				do{
					//le o lance de posicionamento do jogador 1
					scanf(" %c  %c  %c", &p1, &p2, &peca);
					
					
					if(p1 == 'B' || p1 == 'C' || p1 == 'T'){
						intermediario = peca;
						peca = p1;
						p1 = p2;
						p1 = p1 - '0';
						p2 = intermediario;
						p2 = p2 - '0';
					}else{
						p1 = p1 - '0';
						p2 = p2 - '0';
					}
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
				//o mesmo acontece para o jogador 2
				do{
					scanf(" %c  %c  %c", &p1, &p2, &peca);
						
					if(p1 == 'b' || p1 == 'c' || p1 == 't'){
						intermediario = peca;
						peca = p1;
						p1 = p2;
						p1 = p1 - '0';
						p2 = intermediario;
						p2 = p2 - '0';
					}else{
						p1 = p1 - '0';
						p2 = p2 - '0';
					}
					erros(vez, p1, p2, peca, tab, jogo);
				}while((p1!=1 && p1!=2 && p1!=3) || (p2!=1 && p2!=2 && p2!=3) || (peca != 'b' && peca != 'c' && peca != 't') || (tab[p1-1][p2-1] != '_') || (checar(peca, tab) != 0));
				tab[p1-1][p2-1] = peca;
				printTab(tab);
			}
		}
		else{
			if(vez == 1){
				
				//nesse do while acontece o mesmo que no do wile do primeiro momento do jogo,
				//exceto que eh usada a funcao checarlance ao inves da checar
				do{
					scanf(" %c  %c  %c", &p1, &p2, &peca);
						
					if(p1 == 'B' || p1 == 'C' || p1 == 'T'){
						intermediario = peca;
						peca = p1;
						p1 = p2;
						p1 = p1 - '0';
						p2 = intermediario;
						p2 = p2 - '0';
					}else{
						p1 = p1 - '0';
						p2 = p2 - '0';
					}
					erros(vez, p1, p2, peca, tab, jogo);
				}while((p1!=1 && p1!=2 && p1!=3) || (p2!=1 && p2!=2 && p2!=3) || (peca != 'B' && peca != 'C' && peca != 'T')||(checarlance(p1, p2, peca, tab) != 0)||(tab[p1-1][p2-1] != '_') );
				lance(p1, p2, peca, tab);
				printTab(tab);
			}
			else{
				
				do{
					scanf(" %c  %c  %c", &p1, &p2, &peca);
								
					if(p1 == 'b' || p1 == 'c' || p1 == 't'){
						intermediario = peca;
						peca = p1;
						p1 = p2;
						p1 = p1 - '0';
						p2 = intermediario;
						p2 = p2 - '0';
					}else{
						p1 = p1 - '0';
						p2 = p2 - '0';
					}
					erros(vez, p1, p2, peca, tab, jogo);
				}while((p1!=1 && p1!=2 && p1!=3) || (p2!=1 && p2!=2 && p2!=3) || (peca != 'b' && peca != 'c' && peca != 't') || (tab[p1-1][p2-1] != '_') || (checarlance(p1, p2, peca, tab) != 0));
				lance(p1, p2, peca, tab);
				printTab(tab);	
			}
		}
	}else{
		if(mododejogo == 2){
			if(jogo == 1){
				if(vez == 1){
					pcjoga(i, tab, jogo, jogada);
					printTab(tab);
				}else{
					do{
						scanf(" %c  %c  %c", &p1, &p2, &peca);
							
						if(p1 == 'b' || p1 == 'c' || p1 == 't'){
							intermediario = peca;
							peca = p1;
							p1 = p2;
							p1 = p1 - '0';
							p2 = intermediario;
							p2 = p2 - '0';
						}else{
							p1 = p1 - '0';
							p2 = p2 - '0';
						}
						erros(vez, p1, p2, peca, tab, jogo);
					}while((p1!=1 && p1!=2 && p1!=3) || (p2!=1 && p2!=2 && p2!=3) || (peca != 'b' && peca != 'c' && peca != 't') || (tab[p1-1][p2-1] != '_') || (checar(peca, tab) != 0));
					tab[p1-1][p2-1] = peca;
					printTab(tab);
				}
			}else{
				if(vez == 1){
					pcjoga(i, tab, jogo, jogada);
					printTab(tab);
				}else{
					do{
						scanf(" %c  %c  %c", &p1, &p2, &peca);
									
						if(p1 == 'b' || p1 == 'c' || p1 == 't'){
							intermediario = peca;
							peca = p1;
							p1 = p2;
							p1 = p1 - '0';
							p2 = intermediario;
							p2 = p2 - '0';
						}else{
							p1 = p1 - '0';
							p2 = p2 - '0';
						}
						erros(vez, p1, p2, peca, tab, jogo);
					}while((p1!=1 && p1!=2 && p1!=3) || (p2!=1 && p2!=2 && p2!=3) || (peca != 'b' && peca != 'c' && peca != 't') || (tab[p1-1][p2-1] != '_') || (checarlance(p1, p2, peca, tab) != 0));
					lance(p1, p2, peca, tab);
					printTab(tab);	
				}
			}
		}
	}
	return;
}

int main(void){
    //declarando as varaveis
    char j1[20], j2[20]; // recebe o nome dos jogadores
    char tab[3][3]; //recebe o tabuleiro
    int i, j; //contadores
	int vez = 0; //indica de quem eh a vez de jogar, se vez = 1 entao eh a vez do jogador 1, se v = 2 eh a vez do jogador 2
	int jogo = 0; //indica qual fase do jogo esta acontecendo, se for a fase de posicionamento entao jogo = 1, se for a fase de movimentacao de pecas entao jogo = 2
    int mododejogo;//se o mododejogo for 1, então eh jogador VS jogador, se for 2 eh computador VS jogador
	lanceC jogada[1]; //vetor que serve para realizar as jogadas do computador
	
	info();
    printf("Menu:\n");
	do{
		printf("(1) Jogador VS Jogador\n");
		printf("(2) Computador VS Jogador\n");
		printf("Selecione o tipo de jogo: ");
		scanf("%d", &mododejogo);
	}while(mododejogo != 1 || mododejogo != 2);
	printf("\n");
	if(mododejogo == 1){
		printf("Jogador VS Jogador\n");
        //jogadores dão entrada em seus nomes
        printf("Jogador 1, digite como deseja ser chamado: ");
        scanf("%s", j1);
        //se os nomes do jogador 2 for igual ao do jogador 1 entao o jogador 2 fica preso nesse looping ateh digitar um nome diferente
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
                leitura(i, tab, jogo, vez, mododejogo, jogada);
                //verifica se o jogador 1 eh o vencedor, se for printa que ele venceu e i recebe 7 para sair do looping da fase de posicionamento
                if(vencedor(tab) == 1){
                    printTab(tab);
                    printf("%s vence!\n", j1);
                    i=7;
                }//se o jogador 1 nao venceu entao eh o turno do jogador 2 e o codigo abaixo eh executado. Eh analogo ao trecho de cima mas para o jogador 2
                else{
                    printf("Turno de %s\n", j2);
                    vez = 2;
                    leitura(i, tab, jogo, vez, mododejogo, jogada);
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
                    //antes de pedir um lance para o jogador, eh checado se houve empate, se nao houve, o jogo continua, se houve, o jogo eh encerrado e aparece uma mensagem avisando que houve empate e diz quem estah sem movimentos
                    if(empate1(tab)!=9){
                        printf("Turno de %s\n", j1);
                        vez = 1;
                        leitura(i, tab, jogo, vez, mododejogo, jogada);
                        //depois que leu-se a , eh checado se houve vitoria
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
                        leitura(i, tab, jogo, vez, mododejogo, jogada);
                        //depois que leu-se a , eh checado se houve vitoria
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
        //entao o empate de s de mais so acontece se o for anterior acabar no i=31
        if(i == 60){
            printf("EMPATE: Ocorreram mais de 30 s e nao houve vitorias");
        }
    }else{
		if(mododejogo == 2){
			printf("Computador VS Jogador\n\n");
			printf("Jogador, digite como deseja ser chamado: ");
        	scanf("%s", j2);

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
					printf("Turno do Computador\n");
					vez = 1;
					leitura(i, tab, jogo, vez, mododejogo, jogada);
					//verifica se o jogador 1 eh o vencedor, se for printa que ele venceu e i recebe 7 para sair do looping da fase de posicionamento
					if(vencedor(tab) == 1){
						printTab(tab);
						printf("Computador vence!\n");
						i=7;
					}//se o jogador 1 nao venceu entao eh o turno do jogador 2 e o codigo abaixo eh executado. Eh analogo ao trecho de cima mas para o jogador 2
					else{
						printf("Turno de %s\n", j2);
						vez = 2;
						leitura(i, tab, jogo, vez, mododejogo, jogada);
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
						//antes de pedir um lance para o jogador, eh checado se houve empate, se nao houve, o jogo continua, se houve, o jogo eh encerrado e aparece uma mensagem avisando que houve empate e diz quem estah sem movimentos
						if(empate1(tab)!=9){
							printf("Turno do Computador\n");
							vez = 1;
							leitura(i, tab, jogo, vez, mododejogo, jogada);
							//depois que leu-se a , eh checado se houve vitoria
							if(vencedor(tab) == 1){
								printf("Computador vence!\n");
								i=70;
							}
						}else{
							printf("EMPATE: Computador nao tem lances possiveis\n");
							i = 70;
						}
					}
					else{ //se o i for impar o jogador 2 joga
					
						//antes de pedir um lance para o jogador, eh checado se houve empate
						if(empate2(tab) !=9){
							printf("Turno de %s\n", j2);
							vez = 2;
							leitura(i, tab, jogo, vez, mododejogo, jogada);
							//depois que leu-se a , eh checado se houve vitoria
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
			//entao o empate de s de mais so acontece se o for anterior acabar no i=31
			if(i == 60){
				printf("EMPATE: Ocorreram mais de 30 s e nao houve vitorias");
			}
		}
    }
	
    return(0);
}