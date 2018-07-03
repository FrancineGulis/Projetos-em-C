#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

/*variáveis globais*/
char palavras[10][15];


/***função que converte string para maiusculo***/
void maiusc(char s[])
{ 
  int i,j;
    
    j= strlen(s);
    for(i=0;i<j;i++)
    {   
	if(s[i]>96 && s[i]<123)
        s[i]=s[i]-32;
    }
}


/***função que carrega a matriz***/
void CarregaMtz(void)
{ int i;

  printf("Carregar as palavras.(max 10 caracteres)\n\n");
  
  for(i=0; i<3; i++)
  {
  	printf("Palavra %d: ",i+1);
        printf("\n");
 	scanf("%s",palavras[i]);
        maiusc(palavras[i]);
  }

}


/***função que verifica caracteres na palavrra***/
int carac(char str1[], char str2[], char a, int tam)
{
    int j,c= 0;
    
    for(j=0;j<tam;j++)
    {
        if (str2[j] == a)
        {
            str1[j]= a;
            c++;
         }
     } 

    return c;
}


/***função ganhou***/
int ganhou(char str[],int tam) 
{
    int j,c;
    
    for(j=0;j<tam;j++)
    {
        if (str[j] == '_')
        {    
		c=0;
		break;
        }
        else
		c=1;
    }

    return c;	
}


/***função menu***/
int Menu()
{ int opcao;
	
	do
	{
		printf("\n***************   JOGO DA FORCA   ***************\n\n");
		printf("Vamos lá!\n");
		printf("1 - Jogar\n");
		printf("2 - Sair do jogo\n\n");

		scanf("%d",&opcao);
	}
	while ( (opcao != 1) && (opcao != 2) );

  return opcao;
}




/******************************função main******************************/
int main()
{
  char c,resposta[11], deposito[23];
  int i,j,l,e,r,k;

  CarregaMtz();
  
  system("clear"); 


  while (Menu() == 1)
  {
        
	srand( (unsigned)time(NULL) );
        r=rand()%3;

	l= strlen(palavras[r]);
        
        
        for(i=0; i<l; i++)
  		resposta[i]= '_';
  	for(;i<11; i++)
        	resposta[i]= ' ';
        

        system("clear");

  	printf("\nAdivinhe qual e a palavra!!\n");
  	printf("Ela possui %d letras\n",l);
 	printf("Voce tera 6 chances para escolher as letras certas\n\n\n");
        sleep(8);

	j=0;
	i=0;
        c= ' ';
	do
 	{	
		system("clear");
	
  		printf("PALAVRA:\n");
        	printf("%s\n\n\n",resposta);

                /*trecho q monta o deposito*/
		
		deposito[i]= c;
		printf("Deposito de letras\n");
		for(k=0; k<=i; k++)
			printf("%c - ",deposito[k]); 
		i++;
		printf("\n\n\n");


        	printf("DIGITE UMA LETRA: \n");
        	scanf("%*c%c",&c);

        	c = toupper(c);

        	e = carac(resposta, palavras[r], c, l);

        	if (e == 0)
        	{	j++;
        		printf("A palavra nao contem a letra %c\n", c);
			printf("Voce tem mais %d chances\n\n", 6-j);

		}

		else 
			printf("A letra %c aparece %d vezes nessa palavra\n\n", c, e);

		sleep(3); 
 
  	 }
 	 while( (j < 6) && !(ganhou(resposta,l)) );


         if (j == 6)
	 	printf("\nVOCE PERDEU!. A palavra era '%s'.\n\n",palavras[r]);
        
	 else
	 	printf("\nVOCE GANHOU!!. A palavra e '%s'.PARABENS!\n\n\n",palavras[r]);
	 sleep(5);

	 system ("clear");

   }
  

  return 0;
}
