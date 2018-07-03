#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define livre 1
#define parede 2
#define visitada 3
#define beco 4
#define saida 5
#define max 30
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//Estrutura
typedef struct Nodo_Pilha
{
	int elemento;
	struct Nodo_Pilha *prox;
}*NODOPTR;

//Variável Global
int labirinto[max][max];

NODOPTR pilha= NULL;


//Funções

//Função que Aloca Memória para o Nodo
NODOPTR Cria_Nodo()
{
	NODOPTR p;
	p = (NODOPTR) malloc(sizeof(struct Nodo_Pilha));
	if(!p)
	{
		printf("Problemas na Alocação!!!");
		exit(0);
	}
	return p;
}

//Função que carrega a matriz
void carrega_matriz(){
int i, j, k;

    for (j = 0; j < max; j++){
		labirinto[0][j]= parede;
		labirinto[29][j]= parede;
		labirinto[j][0]= parede;
        labirinto[j][29]= parede;
	}
	for(i=1; i < max-1; i++){
		for(j=1; j < max-1; j++)
			labirinto[i][j] = livre;
	}
	
	for(i=1; i < max-1; i++){
		for(j=1; j < max-1; j++){			
			if(rand()%4 == 1){
				labirinto[i][j] = parede;
			}	
			else
				labirinto[i][j] = livre;
		}
	}
	
	labirinto[1][1] = livre;
	labirinto[1][2] = livre;
	labirinto[2][1] = livre;	
	labirinto[2][2] = livre;
	
	//Sorteio da saida
	k = (rand()%28) + 1;
	if(rand()%2 == 1){
		labirinto[29][k] = saida;
		labirinto[28][k] = livre;
	}
	else{
		labirinto[k][29] = saida;
		labirinto[k][28] = livre;	
	}	
}

//Função que Imprime a matriz
 void imprime_matriz(int k, int l)
{
 int i,j;
 
	printf("\n ----------------------- LABIRINTO -----------------------\n");
	printf(" ------------------ EM BUSCA DA SOLUÇÃO ------------------\n");
	
    for (i = 0; i < max; i++)
	{	for (j = 0; j < max; j++){
			if(labirinto[i][j] == parede){
				printf(ANSI_COLOR_BLUE    "# "    ANSI_COLOR_RESET);
			}
			else if((i == k) && (j == l))
				printf(ANSI_COLOR_YELLOW    "@ "    ANSI_COLOR_RESET);
			else if(labirinto[i][j] == livre)
				printf("  ");
			else if(labirinto[i][j] == visitada)
				printf(". ");			
			else if(labirinto[i][j] == beco)
				printf(ANSI_COLOR_RED    ". "    ANSI_COLOR_RESET);
			else if(labirinto[i][j] == saida)
				printf("  ");
			else
				printf("E ");
		}
        printf("\n");
    }
}

//Função Push - Empilha
void push(int dado)
{
	NODOPTR nodo;
	nodo= Cria_Nodo( );
	nodo->elemento = dado;
	nodo->prox = pilha;
	pilha = nodo;
}

//Função Pop - Desempilha
int pop( )
{
	NODOPTR nodo;
	int elem;
	if(!pilha)
	{
		printf("A pilha está vazia!!!");
		return -1;
	}
	nodo = pilha;
	elem = nodo->elemento;
	pilha = nodo->prox;
	free(nodo);
	return elem;
}

//Função que gera inteiro a partir das coordenadas
int calc_empilha(int i, int j){
	int coordenada= i * 100 + j;
	
	return coordenada;
}

//Função que gera coordenadas a partir do inteiro
void calc_desempilha(int *i, int *j, int coordenada){
	*i = coordenada / 100;
	*j = coordenada % 100;
}
	
//Função que indica posições válidas para caminhar no labirinto
int posicao_valida(int i, int j){
	if(labirinto[i][j] == parede)
		return 0;
	else if(labirinto[i][j] == visitada)
		return 0;
	else if(labirinto[i][j] == beco)
		return 0;
	else if(labirinto[i][j] == saida)
		return 2;
	else
		return 1;
}

//Função que caminha no labirinto
void cria_caminho(){
int i, j, k, p, v=0, aux[4];
	i = j = 1;

	labirinto[i][j] = visitada;
	
	do{		
		imprime_matriz(i, j);
		
		k=0;
		//testes
		//Norte
		if( posicao_valida (i-1, j) == 1 ){
			aux[k]= calc_empilha(i-1, j);
			k++;
		}
		else if(posicao_valida (i-1, j) == 2){
			i = i-1; 
			v = 1;
			break;
		}	

        //Sul
		if( posicao_valida (i+1, j) == 1){
			aux[k]= calc_empilha(i+1, j);
			k++;
		}
		else if(posicao_valida (i+1, j) == 2){
			i = i+1;
			v = 1;
			break;
		}	
			
        //Leste
		if( posicao_valida (i, j-1) == 1){
			aux[k]= calc_empilha(i, j-1);
			k++;
		}
		else if(posicao_valida (i, j-1) == 2){
			j = j-1;
			v = 1;
			break;
		}
		
		//Oeste
		if( posicao_valida (i, j+1) == 1){
			aux[k]= calc_empilha(i, j+1);
			k++;
		}
		else if(posicao_valida (i, j+1) == 2){
			j = j+1;
			v = 1;
			break;
		}
		
		if((k == 0) && (pilha != NULL)){	
			calc_desempilha( &i, &j, pop());
			labirinto[i][j] = beco;	
		}
		
		else if (k > 0)
		{   p= rand() % k;
			push(aux[p]);
			calc_desempilha(&i, &j, aux[p]);
			labirinto[i][j] = visitada;
		}	
		
		usleep(200000);
		system("clear");
											
	}while((labirinto[i][j] != saida) && (pilha != NULL));
	
	if(v){
		imprime_matriz(i, j);
		printf("\nPARABÉNS, SAIDA ENCONTRADA!!\n");
		sleep(2);
	}
	else{
		imprime_matriz(i, j);
		printf("\nSAIDA NAO ENCONTRADA!!\n");
		sleep(2);
	}
} 

int menu(){
int a;
	
	system("clear");
	printf("******************** O RATO E O LABIRINTO ********************\n\n");
	printf("Entre com a opção desejada: \n\n");
	printf("1 - Executar o labirinto\n");
	printf("2 - Sair do programa\n");
	
	scanf(" %d", &a);
	
	switch(a)
	{
		case 1:
			system("clear");
			carrega_matriz();
			cria_caminho();
			break;
		
		case 2:
			system("clear");
			printf("PROGRAMA FINALIZADO\n\n");
			break;
		default:
			system("clear");
            printf("\nOpcao Invalida!!!");	
	}
	return a;
}

void main(){
int a;

 srand( (unsigned)time(NULL) );
 
 do{
	 a = menu(); 
	 
 }while(a != 2);
}
