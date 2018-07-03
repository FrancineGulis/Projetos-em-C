#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#define MAXTAM 1000

char *tokens[MAXTAM];
char prefixa[MAXTAM][100];

int tam_tokens;
int tam_prefixa;
int indicepre=0;



typedef struct {
  char Item[MAXTAM][100];
  int Topo;
} pilha;

typedef struct nodo{
  char Item[100];
  struct nodo *esq;
  struct nodo *dir;
} *arvore;



void inicializa(pilha *p)
{ p -> Topo = 0; } 

int vazia(pilha p)
{ return (p.Topo == 0); } 

void push(char x[100], pilha *p)
{ if (p -> Topo == MAXTAM) printf(" Erro   pilha esta  cheia\n");
  else { p->Topo++; strcpy(p->Item[p->Topo - 1], x); }
} 

void pop(pilha *p, char *Item)
{ if (vazia(*p)) printf(" Erro   pilha esta  vazia\n");
  else { strcpy(Item, p->Item[p->Topo - 1]); p->Topo--; }
} 

int tamanho(pilha p)
{ return (p.Topo); }  

arvore CriaNodo (char token[], arvore esq, arvore dir) {
	arvore x;
	x = (arvore)malloc(sizeof(arvore));
        strcpy(x->Item, token);
	x->esq = esq;
	x->dir = dir;
	return x;
}

/* funcao que tokenize uma string, armazenando na variavel global "tokens" */
void tokenize(char *inputS)
{   
	char buffer[MAXTAM];
	char  *next = buffer;
	char   c;
	int i;

	for (i = 0 ; i< MAXTAM ; i++)
		tokens[i] = malloc(100*sizeof(char));
	
	while ((c = *inputS++) != '\0')
	{ 
		tokens[tam_tokens++] = next;
		if (isdigit(c))
		{
			*next++ = c;
			while (isdigit(*inputS))
			{
				c = *inputS++;
				*next++ = c;
			}
			*next++ = '\0';
		}
		else
		{
			*next++ = c;
			*next++ = '\0';
		}
	}   

}


/* funcao que gera a prefixa na var. global "prefixa" a partir da var. global "tokens" */
void gera_prefixa()
{
	int i;	
	char aux[100];
	pilha p,q;
	  
	inicializa(&p);
	inicializa(&q);

	for (i = 0; i < tam_tokens; i++)
	{
		if (tokens[i][0] == ')')
		{   
			pop(&p, aux);			
			push(aux,&q);
		}
		if ((tokens[i][0] == '+') || (tokens[i][0] == '-') || (tokens[i][0] == '*') || (tokens[i][0] == '/') || (tokens[i][0] == '^')) 
			push(tokens[i], &p);			
		if ((tokens[i][0] >= '0') && (tokens[i][0] <= '9'))
			push(tokens[i],&q);		
	}

	tam_prefixa=0;
	for (i=0; !vazia(q); i++){
		pop(&q,prefixa[i]);
		tam_prefixa++;
	}	
	
}


/* funcao que constroi a árvore" */
arvore AnalisaExprConstroiArvore() {
	arvore x;
	char t[100];

	strcpy(t, prefixa[indicepre] );
	indicepre++;

	x = CriaNodo(t, NULL, NULL);

	if ((t[0] == '+') || ( t[0] == '-') || (t[0] == '*') || (t[0] == '/') || (t[0] == '^')) {
		x->dir = AnalisaExprConstroiArvore();		
		x->esq = AnalisaExprConstroiArvore();
	}
	return x;
}

/* funcao que imprime a árvore em inordem */
void imprime_inordem(arvore arv)
{
	if(!arv)
	return;
	imprime_inordem(arv->esq);
	printf(" %s", arv->Item);
	imprime_inordem(arv->dir);
}

/* funcao que imprime a árvore em preordem" */
void imprime_preordem(arvore arv)
{
	if(!arv)
	return;
	printf(" %s", arv->Item);
	imprime_preordem(arv->esq);
	imprime_preordem(arv->dir);
}

/* funcao que imprime a árvore em posordem */
void imprime_posordem(arvore arv)
{
	if(!arv)
	return;

	imprime_posordem(arv->esq);
	imprime_posordem(arv->dir);
	printf(" %s", arv->Item);
}

/* função que calcula a expressão a partir da árvore */
double Calcula(arvore arv){
	if (!arv)
		return -1;
	if (arv->Item[0] == '+')
		return (Calcula(arv->esq) + Calcula(arv->dir) );
	if (arv->Item[0] == '-')
		return (Calcula(arv->esq) - Calcula(arv->dir) );
	if (arv->Item[0] == '*')
		return (Calcula(arv->esq) * Calcula(arv->dir) );
	if (arv->Item[0] == '/')
		return (Calcula(arv->esq) / Calcula(arv->dir) );
	if (arv->Item[0] == '^')
		return (pow(Calcula(arv->esq) , Calcula(arv->dir)));

	return atof(arv->Item);
}


/******************/
/* funcao main()  */ 
/******************/
int main(void)
{
	char inputS[MAXTAM], aux[MAXTAM][100];
	int i, j, op;
	arvore Expre[1000];

	do{
		system("clear");
		printf("\n\n******************** ÁRVORES DE EXPRESSÃO ARITMÉTICA ********************\n");
		
		printf("\n1 - Entrar com as expressões a serem calculadas");
		printf("\n2 - Mostrar os resultados de todas as expressões");
		printf("\n3 - Mostrar o resultado de uma expressão");
		printf("\n4 - Sair do programa");
		printf("\nOpção: ");	
		
		scanf("%d", &op);        

        	switch( op )
        	{
			case 1:
				system("clear");
				printf("\n******************** INSTRUÇÕES ********************");
				printf("\n1 - Digite a expressão com parenteses para identificar as precedencias");
				printf("\n   Exemplo: 3*2+5/10 -> (((3*2)+5)/10)");
				printf("\n2 - Digite 'F' para encerrar a entrada de expressões\n\n");

	                        j=0;
				while((inputS[0] != 'F') && (inputS[0] != 'f')){
					printf("\nEntre com a expressão:\n");
					scanf("%s", inputS);

					strcpy(aux[j], inputS);

					tokenize(inputS);

					gera_prefixa();
					indicepre=0;

					Expre[j] = AnalisaExprConstroiArvore();
	
					j++;
				}
				strcpy(inputS, " ");
                		break;

			case 2:
				system("clear");
				printf("Todas as expressões");
				for(i=0; i<j-1; i++){	
					printf("\nExpressão %d: %s", i+1, aux[i]);

					printf("\nArvore inordem");
					imprime_inordem(Expre[i]);	

					printf("\nArvore preordem");
					imprime_preordem(Expre[i]);

					printf("\nArvore posordem");
					imprime_posordem(Expre[i]);

        				printf("\nResultado da espressão: %lf\n\n", Calcula(Expre[i]));
				}

				//sleep(10);
				__fpurge(stdin);
				getchar();
				break;

			case 3:
				system("clear");
				for(i=0; i<j-1; i++){	
					printf("\nExprressão %d: %s", i+1, aux[i]);
				}

				printf("\nQual a expressão deseja consultar:");
				scanf("%d",&i);

				printf("\nExprressão %d: %s", i, aux[i-1]);

				printf("\nArvore inordem");
				imprime_inordem(Expre[i-1]);	

				printf("\nArvore preordem");
				imprime_preordem(Expre[i-1]);

				printf("\nArvore posordem");
				imprime_posordem(Expre[i-1]);

       				printf("\nResultado da espressão: %lf\n\n", Calcula(Expre[i]));

				//sleep(5);
				__fpurge(stdin);
				getchar();
				break;	

			case 4:
				break;	

                  	default:
                		printf("\nOpção inválida!!\n");
				//sleep(2);
                
                		break;	
		}

	}while(op != 4);	

	printf("\n\nFim do programa\n\n");

	return 0;
}

//(((3+2)*(67-9))/100)
