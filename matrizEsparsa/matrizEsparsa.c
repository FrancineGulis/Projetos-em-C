#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bloco {
	float dado;
	int i,j;
	struct Bloco *prox;
}Nodo;

typedef struct lst{
	int numlin;
	int numcol;
	Nodo *end;
	struct lst *prox;
}Lista;

typedef struct oper{
	char tipo[7];
	Nodo *origA;
	int la;
	int ca;
	Nodo *origB;
	int lb;
	int cb;
	Nodo *end;
	int numlin;
	int numcol;
	struct oper *prox;
}Operacoes;

Nodo * busca_lista_indice(int i, int j, Nodo *N);
int multiplica(Nodo *A, Nodo *B, Nodo **R, int m1, int n1, int m2, int n2);
int numero_itens(Nodo *N);
Lista * Cria_Lista();
Nodo * Cria_Nodo();
Operacoes * Cria_Operacoes();
void deletar_matriz(Lista **L);
void deletar_item(Nodo **N);
void imprime_diagonal_principal(Nodo *N, int m, int n);
void imprime_lista_matriz(Nodo *N);
void imprime_matriz(Nodo *N, int m, int n);
int insere_item(Nodo **N, float valor, int lin, int col);
Nodo * insere_itens(Nodo **N, int maxlin, int maxcol);
void insere_matriz(Lista **M);
void inserir_novo_item(Nodo **N, int maxlin, int maxcol);
int lista_matrizes(Lista *N);
void matriz(Nodo **N, int lin, int col);
void menu();
void menumtr();
void menuoper();
void operac(Operacoes **O, Lista *L);
void pre_calculo(Operacoes **O, Lista *L, int op);
void pre_transposta(Operacoes **O, Lista *L);
void selecionar_matriz(Lista **N, int op);
int soma_subtrai(Nodo *A, Nodo *B, Nodo **R, int a, int m1, int n1, int m2, int n2);
void transposta(Nodo *A, Nodo **R);
void visualizar(Operacoes *O, Lista *L);

void main(){
	
	Lista *matrizes=NULL;
	Operacoes *contas_matr=NULL;
	int var;
	
	do{
		menu();
		//fflush(stdin);
		__fpurge(stdin);
		var = getchar();
		if((var == 70)||(var == 102)){
			printf("\nFinalizando o programa\n");
		}else if(var == 49){
			insere_matriz(&matrizes);
		}else if(var == 50){
			selecionar_matriz(&matrizes, 1);
		}else if(var == 51){
			deletar_matriz(&matrizes);
		}else if(var == 52){
			operac(&contas_matr, matrizes);
		}
	}while((var != 70) && (var!=102));
}

void deletar_matriz(Lista **L){
	
	Lista *temp=NULL, *anterior=NULL;
	int op,count;
	
	temp = *L;
	if(!(lista_matrizes(temp))){
		return;
	}
	printf("\nEscolha a matriz para ser deletada\nou 0 para apagar todas: ");
	scanf("%d", &op);
	if(op==0){
		*L = NULL;
	}
	else if(op==1){
		*L = temp->prox;
	}else{
		count=1;
		while((temp!=NULL)&&(op!=count)){
			anterior=temp;
			temp=temp->prox;
			count++;
		}
		if(temp==NULL){
			printf("\nDado não existe");
			//fflush(stdin);
			__fpurge(stdin);
			getchar();
		}else{
			anterior->prox=temp->prox;
			free(temp);
		}
	}
}

void deletar_item(Nodo **N){
	
	Nodo *temp=NULL, *anterior=NULL;
	int op,count;
	
	temp = *N;
	if(temp==NULL){
		printf("\nMatriz vazia!");
		return;
	}
	imprime_lista_matriz(temp);
	printf("\nEscolha o dado para ser deletado\nou 0 para apagar todos: ");
	scanf("%d", &op);
	if(op==0){
		*N = NULL;
	}
	else if(op==1){
		*N = temp->prox;
	}else{
		count=1;
		while((temp!=NULL)&&(op!=count)){
			anterior=temp;
			temp=temp->prox;
			count++;
		}
		if(temp==NULL){
			printf("\nDado não existe");
			//fflush(stdin);
			__fpurge(stdin);
			getchar();
		}else{
			anterior->prox=temp->prox;
			free(temp);
		}
	}
}

void inserir_novo_item(Nodo **N, int maxlin, int maxcol){
	
	Nodo *destino=NULL;
	float valor;
	int lin, col, maxitens, nv=0;
	
	maxitens = maxlin * maxcol;
	destino = *N;
	nv = numero_itens(destino);
	//system("cls");
	system("clear");
	if(nv >= maxitens){
		printf("\nExcedeu-se o número máximo de itens\n");
		//fflush(stdin);
		__fpurge(stdin);
		getchar();
		return;
	}
	do{
		printf("\nDigite o valor: ");
		scanf("%f", &valor);
			if(valor==0){
				printf("\nValor 0 não precisa ser inserido ");
			}
	}while(valor == 0);
	do{
		printf("\nDigite a linha: ");
		scanf("%d", &lin);
		if((lin>maxlin)||(lin<1)){
			printf("\nValor de linha inválido: ");
		}
	}while((lin>maxlin)||(lin<1));
	do{
		printf("\nDigite a coluna: ");
		scanf("%d", &col);
		if((col>maxcol)||(col<1)){
			printf("\nValor de coluna inválido: ");
		}
	}while((col>maxcol)||(col<1));
	insere_item(&destino, valor, lin, col);
	*N = destino;
}



void selecionar_matriz(Lista **N, int op){
	
	Lista *aux=NULL;
	int opc, count;
	aux = *N;
	if(!(lista_matrizes(aux))){
		return;
	}
	printf("\nSelecione uma matriz:");
	scanf("%d", &opc);
	count=1;
	while((aux->prox!=NULL)&&(count!=opc)){
		aux = aux->prox;
		count++;
		if(aux==NULL){
			printf("\nMatriz não encontrada");
			return;
		}
	}
	if(op==1){
		matriz(&aux->end, aux->numlin, aux->numcol);
	}
}


void imprime_lista_matriz(Nodo *N){
	
	Nodo *aux;
	int cont=0;
	aux = N;
	if(aux==NULL){
		printf("\nMatriz não possui dados");
	}
	while(aux!=NULL){
		cont++;
		printf("\n%d) %f(%d,%d) [%p]", cont, aux->dado, aux->i, aux->j, aux);
		aux=aux->prox;
	}
}

void imprime_diagonal_principal(Nodo *N, int m, int n){

	Nodo *aux;
	int i, j, caux, calc;
	//system("cls");
	system("clear");
	aux = N;
	if (N == NULL) {
		printf("\n A matriz está vazia!!");
	}else{
		aux = N;
		caux = aux->i * 100 + aux->j;
		for(i=1; i<=m; i++){
			for (j = 1; j<=n; j++){
				calc = i * 100 + j;
				if(calc == caux){
					if(i==j){
						printf("%f ",aux->dado);
					}else{
						printf("         ");
					}
					if(aux->prox!=NULL){
						aux=aux->prox;
						caux = aux->i * 100 + aux->j;
					}
				}else{
					if(i==j){
						printf("%f ",0.00);
					}else{
						printf("         ");
					}
				}
			}
			printf("\n");
		}
	}
	//fflush(stdin);
	__fpurge(stdin);
	getchar();
}

void imprime_matriz(Nodo *N, int m, int n){

	Nodo *aux;
	int i, j, caux, calc;
	aux = N;
	if (N == NULL) {
		printf("\n A matriz está vazia!!");
	}else{
		aux = N;
		printf("\nMatriz [%p]\n",aux);
		caux = aux->i * 100 + aux->j;
		for(i=1; i<=m; i++){
			for (j = 1; j<=n; j++){
				calc = i * 100 + j;
				if(calc == caux){
					printf("%f ",aux->dado);
					if(aux->prox!=NULL){
						aux=aux->prox;
						caux = aux->i * 100 + aux->j;
					}
				}else{
					printf("%f ",0.00);
				}
			}
			printf("\n");
		}
	}
}

int soma_subtrai(Nodo *A, Nodo *B, Nodo **R, int a, int m1, int n1, int m2, int n2)
{
	Nodo *auxA=NULL, *auxB=NULL;
	Nodo *destino=NULL;
	float soma;
	int ia, ja, ib, jb;

	auxA= A;
	auxB= B;
	destino = *R;

	if( (m1 != m2) || (n1 != n2) ){
	    //system("cls");
	    system("clear");
		printf("Matrizes de tamanhos diferentes, operacao invalida.\n");
		//fflush(stdin);
		__fpurge(stdin);
		getchar();
		return 0;
	}else{
		while((auxA != NULL) && (auxB != NULL)){
			soma= 0.0;
			ia= auxA->i;
			ja= auxA->j;
			ib= auxB->i;
			jb= auxB->j;

			if(ia == ib){
				if(ja == jb){
					if(a == 1)
						soma= auxA->dado + auxB->dado;
					else if(a == 2)
						soma= auxA->dado - auxB->dado;
					insere_item(&destino, soma, ia, ja);
					auxA= auxA->prox;
					auxB= auxB->prox;
				}
				else if(ja > jb){
					soma= auxB->dado;
					if(a == 2)
						soma= (0.0 - auxB->dado);
					insere_item(&destino, soma, ib, jb);
					auxB= auxB->prox;
				}
				else{
					soma= auxA->dado;
					insere_item(&destino, soma, ia, ja);
					auxA= auxA->prox;
				}
			}

			else if(ia > ib){
				soma= auxB->dado;
				if(a == 2)
					soma= (0.0 - auxB->dado);
				insere_item(&destino, soma, ib, jb);
				auxB= auxB->prox;
			}

			else{
				soma= auxA->dado;
				insere_item(&destino, soma, ia, ja);
				auxA= auxA->prox;
			}
		}
		while(auxA != NULL){
			ia= auxA->i;
			ja= auxA->j;
			soma= auxA->dado;
			insere_item(&destino, soma, ia, ja);
			auxA= auxA->prox;
		}
		while(auxB != NULL){
			ib= auxB->i;
			jb= auxB->j;
			soma= auxB->dado;
			if(a == 2)
				soma= (0.0 - auxB->dado);
			insere_item(&destino, soma, ib, jb);
			auxB= auxB->prox;
		}
	}
	*R = destino;
	return 1;
}

void pre_calculo(Operacoes **O, Lista *L, int op){
	
	Operacoes *novo=NULL, *temp;
	int p, s, calc, count;
	Lista *auxA=NULL;
	Lista *auxB=NULL;
	Nodo *mt;
	auxA = L;
	auxB = L;
	
	mt = Cria_Nodo();
	novo = Cria_Operacoes();
	if(!(lista_matrizes(L))){
		return;
	}
	printf("\nSelecione a primeira matriz:");
	scanf("%d", &p);
	count=1;
	while((auxA!=NULL)&&(p!=count)){
		auxA = auxA->prox;
		count++;
	}
	if(auxA==NULL){
		printf("\nPrimeira matriz não encontrada");
		return;
	}
	printf("\nSelecione a segunda matriz:");
	scanf("%d", &s);
	count=1;
	while((auxB!=NULL)&&(s!=count)){
		auxB = auxB->prox;
		count++;
	}
	if(auxB==NULL){
		printf("\nSegunda matriz não encontrada");
		return;
	}
	//system("cls");
	system("clear");
	if(op==3){
		calc = multiplica(auxA->end, auxB->end, &mt, auxA->numlin, auxA->numcol, auxB->numlin, auxB->numcol);
	}else{
		calc = soma_subtrai(auxA->end, auxB->end, &mt, op, auxA->numlin, auxA->numcol, auxB->numlin, auxB->numcol);
	}
	if(calc){
		imprime_matriz(auxA->end, auxA->numlin, auxA->numcol);
		imprime_matriz(auxB->end, auxB->numlin, auxB->numcol);
		imprime_matriz(mt, auxA->numlin, auxB->numcol);
		//fflush(stdin);
		__fpurge(stdin);
		getchar();
		if(op == 1){
			strcpy(novo->tipo,"SOMA");
		}else if(op == 2){
			strcpy(novo->tipo,"SUBTR");
		}else if(op == 3){
			strcpy(novo->tipo,"MULT");
		}else{
			strcpy(novo->tipo,"VERIF");
		}
		novo->origA = auxA->end;
		novo->la = auxA->numlin;
		novo->ca = auxA->numcol;
		novo->origB = auxB->end;
		novo->lb = auxB->numlin;
		novo->cb = auxB->numcol;
		novo->end = mt;
		novo->numlin=auxA->numlin;
		novo->numcol=auxB->numcol;
		novo->prox=NULL;
		if (*O == NULL) {
			*O = novo;
		}else {
			temp = *O;
			while (temp->prox != NULL) {
				temp = temp->prox;
			}
			temp->prox = novo;
		}
	}
}

void transposta(Nodo *A, Nodo **R){
	
	Nodo *auxA=NULL;
	Nodo *destino=NULL;
	auxA=A;
	destino = *R;
	while(auxA != NULL){
		insere_item(&destino, auxA->dado, auxA->j, auxA->i);
		auxA = auxA->prox;
	}
	*R = destino;
}

void pre_transposta(Operacoes **O, Lista *L){
	
	Operacoes *novo=NULL, *temp;
	int it, count;
	Lista *aux=NULL;
	Nodo *mt=NULL;
	aux = L;
	
	mt = Cria_Nodo();
	novo = Cria_Operacoes();
	if(!(lista_matrizes(L))){
		return;
	}
	printf("\nSelecione uma matriz:");
	scanf("%d", &it);
	count=1;
	while((aux->prox!=NULL)&&(it!=count)){
		aux = aux->prox;
		count++;
		if(aux==NULL){
			printf("\nMatriz não encontrada");
			return;
		}
	}
	transposta(aux->end, &mt);
	//system("cls");
	system("clear");
	imprime_matriz(aux->end, aux->numlin, aux->numcol);
	imprime_matriz(mt, aux->numcol, aux->numlin);
	//fflush(stdin);
	__fpurge(stdin);
	getchar();
	strcpy(novo->tipo,"TRANSP");
	novo->origA = aux->end;
	novo->la=aux->numlin; 
	novo->ca=aux->numcol;
	novo->origB=NULL;
	novo->end = mt;
	novo->numlin=L->numcol;
	novo->numcol=L->numlin;
	novo->prox=NULL;
	if (*O == NULL) {
		*O = novo;
	}else {
		temp = *O;
		while (temp->prox != NULL) {
			temp = temp->prox;
		}
		temp->prox = novo;
	}
}

int multiplica(Nodo *A, Nodo *B, Nodo **R, int m1, int n1, int m2, int n2)
{
	Nodo *achouA=NULL, *achouB=NULL, *destino=NULL;
	float mult;
	int i, j, k;
	destino = *R;

	if(n1 != m2){
		//system("cls");
	    system("clear");
		printf("\nDimensoes das matrizes invalidas, operação invalida.\n");
		//fflush(stdin);
		__fpurge(stdin);
		getchar();
		return 0; 
	}else{
			for(i=1; i<m1+1; i++)
				for(j=1; j<n2+1; j++){
					mult= 0.0;
					for(k=1; k<n1+1; k++){
						achouA= busca_lista_indice(i, k, A);
						achouB= busca_lista_indice(k, j, B);
						if((achouA != NULL) && (achouB != NULL))
							mult= mult + ((achouA->dado) * (achouB->dado));
						else
							mult= mult + 0.0;
					}
					insere_item(&destino, mult, i, j);
				}
	}
	*R = destino;
	return 1;
}

Nodo * busca_lista_indice(int i, int j, Nodo *N){
	Nodo *b;

	b= N;
	while(b != NULL){
		if((b->i == i) && (b->j == j)){
			break;
		}
		else
			b= b->prox;
	}
	return b;
}

void operac(Operacoes **O, Lista *L){
	Operacoes *aux;
	int var;
	aux = *O;
	do{
		menuoper();
		//fflush(stdin);
		__fpurge(stdin);
		var = getchar();
		if(var == 49){
			pre_transposta(&aux, L);
		}else if(var == 50){
			pre_calculo(&aux, L, 1);
		}else if(var == 51){
			pre_calculo(&aux, L, 2);
		}else if(var == 52){
			pre_calculo(&aux, L, 3);
		}else if(var == 53){
			visualizar(aux, L);
		}
		*O = aux;
	}while((var != 86) && (var!=118));
}

void matriz(Nodo **N, int lin, int col){
	
	Nodo *aux;
	int var;
	aux = *N;
	do{
		menumtr();
		//fflush(stdin);
		__fpurge(stdin);
		var = getchar();
		if(var == 49){
			//system("cls");
	        system("clear");
			imprime_matriz(aux, lin, col);
			//fflush(stdin);
			__fpurge(stdin);
			getchar();
		}else if(var == 50){
			//system("cls");
	        system("clear");
			imprime_lista_matriz(aux);
			//fflush(stdin);
			__fpurge(stdin);
			getchar();
		}else if(var == 51){
			imprime_diagonal_principal(aux, lin, col);
		}else if(var == 52){
			inserir_novo_item(&aux, lin, col);
		}else if(var == 53){
			deletar_item(&aux);
		}
	}while((var != 86) && (var!=118));
}

int lista_matrizes(Lista *N){
	
	Lista *aux=NULL;
	int count;
	//system("cls");
	system("clear");
	if (N == NULL) {
		printf("\n Não existe matriz cadastrada!!");
		return 0;
	}else {
		count=1;
		for (aux = N; aux != NULL; aux = aux->prox){
			printf("\n%d) %dX%d [%p] ", count, aux->numlin, aux->numcol, aux->end);
			count++;
		}
	}
	printf("\n");
	return 1;
}

int insere_item(Nodo **N, float valor, int lin, int col){
	
	Nodo *novo=NULL, *aux=NULL, *anterior=NULL;
	int count, cnov, caux;

	if(valor==0){
		return 0;
	}
	novo = Cria_Nodo();
	novo->dado = valor;
	novo->i = lin;
	novo->j = col;
	novo->prox = NULL;
	cnov = lin * 100 + col;
	if((*N == NULL)||(((*N)->dado == 0.0))){
		*N = novo;
		return 1;
	}else{
		aux = *N;
		count = 0;
		do{
			caux = aux->i * 100 + aux->j;
			if(cnov==caux){
				printf("\nJá existe dado na posição da matriz");
				return 0;
			}else if(cnov<caux){
				if(count == 0){
					if(aux->prox == NULL){
						novo->prox = aux;
						*N = novo;
						return 1;
					}else{
						anterior = *N;
						novo->prox = anterior;
						*N = novo;
						return 1; 
					}
				}else{
					novo->prox = aux;
					anterior->prox=novo;	
					return 1; 
				}
			}else if(aux->prox == NULL){
					aux->prox = novo;
					return 1;
			}else{
				anterior = aux;
				aux = aux->prox;
			}
			count++;
		}while(aux!=NULL);
	}
	return 0;
}

int numero_itens(Nodo *N){
	
	Nodo *aux=NULL;
	int count=0;
	
	aux=N;
	if(aux==NULL){
		return 0;
	}
	while(aux!=NULL){
		aux=aux->prox;
		count++;
	}
	return count;
}

Nodo * insere_itens(Nodo **N, int maxlin, int maxcol){
	
	float valor;
	int lin, col, var, maxitens, count;
	Nodo *aux=NULL;
	
	maxitens = maxlin * maxcol;
	aux = *N;
	if(aux!=NULL){
		count = numero_itens(aux);
	}else{
		count=0;
	}
	do{
	    //system("cls");
	    system("clear");
		if(count >= maxitens){
			printf("\nExcedeu-se o número máximo de itens\n");
			//fflush(stdin);
			__fpurge(stdin);
			getchar();
			return aux;
		}
		do{
			printf("\nDigite o valor: ");
			scanf("%f", &valor);
			if(valor==0){
				printf("\nValor 0 não precisa ser inserido ");
			}
		}while(valor == 0);
		do{
			printf("\nDigite a linha: ");
			scanf("%d", &lin);
			if((lin>maxlin)||(lin<1)){
				printf("\nValor de linha inválido: ");
			}
		}while((lin>maxlin)||(lin<1));
		do{
			printf("\nDigite a coluna: ");
			scanf("%d", &col);
			if((col>maxcol)||(col<1)){
				printf("\nValor de coluna inválido: ");
			}
		}while((col>maxcol)||(col<1));
		if(insere_item(&aux, valor, lin, col)){
			count++;
		}
		/*Nodo *novo=NULL;
		novo = aux;
		while(novo!=NULL){
			printf("\n%f,%d,%d,%p", novo->dado, novo->i, novo->j, novo);
			novo=novo->prox;
		}//Visualização de itens inseridos.*/
		printf("\nTecle <Enter> para inserir novo valor\nou E para encerrar inserção de itens\nOpcao: ");
		//fflush(stdin);
		__fpurge(stdin);
		var = getchar();
	}while((var != 69) && (var!=101));
	return aux;
}

void insere_matriz(Lista **M){
	
	int lin, col;
	Lista *novo, *aux;
	Nodo *teste=NULL, *temp=NULL;
	
	novo = Cria_Lista();
	
	//system("cls");
	system("clear");
	printf("\nQual a dimensão da matriz: ");
	printf("\nNúmero de linhas: ");
	scanf("%d", &lin);
	printf("\nNúmero de colunas: ");
	scanf("%d", &col);
	novo->numlin = lin;
	novo->numcol = col;
	novo->end = insere_itens(&temp,lin,col);
	novo->prox = NULL;
	teste = novo->end;
	if (*M == NULL) {
		*M = novo;
	}else {
		aux = *M;
		while (aux->prox != NULL) {
			aux = aux->prox;
		}
		aux->prox = novo;
	}
}


Lista * Cria_Lista(){
	
	Lista *p;
	
	p = (Lista *) malloc(sizeof(Lista));
	if(!p)
	{printf("\nProblema de alocação");
		exit(0);
	}
	return p;
}

Nodo * Cria_Nodo(){
	Nodo *p;
	p = (Nodo *) malloc(sizeof(Nodo));
	if(!p)
	{printf("\nProblema de alocação");
		exit(0);
	}
	return p;
}

Operacoes * Cria_Operacoes(){
	Operacoes *p;
	p = (Operacoes *) malloc(sizeof(Operacoes));
	if(!p)
	{printf("\nProblema de alocação");
		exit(0);
	}
	return p;
}

void visualizar(Operacoes *O, Lista *L){
	
	Lista *auxL=NULL;
	int count=0, var;
	Operacoes *auxO=NULL;
	//system("cls");
	system("clear");
	if (O == NULL) {
		printf("\n Não existe matriz cadastrada!!");
	}else {
		do{
		    //system("cls");
	        system("clear");
			count=0;
			for (auxO = O; auxO != NULL; auxO = auxO->prox){
				count++;
				printf("\n%d) %s - [%p][%p][%p] l:%d c:%d", count, auxO->tipo, auxO->origA, auxO->origB, auxO->end, auxO->numlin, auxO->numcol);
			}
			printf("\nEscolha um resultado\nou V para voltar: ");
			//fflush(stdin);
			__fpurge(stdin);
			var=getchar();
			auxO=O;
			count=1;
			while((count!=(var - 48))&&(auxO!=NULL)){
				auxO = auxO->prox;
				count++;
			}
			if(auxO!=NULL){
				//system("cls");
	            system("clear");
				imprime_matriz(auxO->origA, auxO->la, auxO->ca);
				if(auxO->origB!=NULL){
					imprime_matriz(auxO->origB, auxO->lb, auxO->cb);
				}
				imprime_matriz(auxO->end, auxO->numlin, auxO->numcol);
				//fflush(stdin);
				__fpurge(stdin);
				getchar();
			}
		}while((var != 86) && (var!=118));
	}
}


void menuoper(){
	//system("cls");
	system("clear");
	printf("\nEstrutura de Dados");
	printf("\n1 - Matriz Transposta");
	printf("\n2 - Somar 2 Matrizes");
	printf("\n3 - Subtrair 2 Matrizes");
	printf("\n4 - Multiplicar 2 Matrizes");
	printf("\n5 - Visualizar Resultados");
	printf("\nV - Voltar");
	printf("\n Digite sua opção: ");
}


void menumtr(){
	//system("cls");
	system("clear");
	printf("\nEstrutura de Dados");
	printf("\n1 - Imprimir matriz");
	printf("\n2 - Imprimir lista de dados");
	printf("\n3 - Imprimir Diagonal Principal");
	printf("\n4 - Inserir novo dado");
	printf("\n5 - Deletar dado");
	printf("\nV - Voltar");
	printf("\n Digite sua opção: ");
}

void menu(){
	//system("cls");
	system("clear");
	printf("\nEstrutura de Dados");
	printf("\n1 - Inserir matriz");
	printf("\n2 - Listar matrizes");
	printf("\n3 - Deletar matriz");
	printf("\n4 - Calcular");
	printf("\nF - Finalizar");
	printf("\n Digite sua opção: ");
}
