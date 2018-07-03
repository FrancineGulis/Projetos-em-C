#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>


/***variáveis globais***/

char mvelha[3][3];
char nivel;
int jogadas;
int ultima[2];

/***função que carrega a matriz***/
void Inicializa_Velha()
{
    int i,j;

    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            mvelha[i][j]= ' ';
}



/***função para escolher o simbolo do player***/
void Escolha_Simb(char *jog1, char *jog2)
{
    printf("Jogador 1, quem voce sera, X ou O?\n");
    scanf("%*c%c",jog1);
    *jog1= toupper(*jog1);

    if (*jog1 == 'X')
        *jog2= 'O';
    else
        *jog2= 'X';
}



/***função para escolher o oponente***/
int Menu()
{
    int p2;

    do
    {
        printf("\n***************   JOGO DA VELHA   ***************\n\n");
        printf("Vamos começar! Contra quem voce deseja jogar?\n");
        printf("1 - Computador\n");
        printf("2 - Um amigo\n");
        printf("3 - Sair do jogo\n\n");

        scanf("%d",&p2);

        switch (p2)
        {
        case 1:
            printf("\nVoce escolheu 'Computador'\n\n");
            sleep(3);
            system("clear");
            printf("\nQual nivel de dificuldade quer jogar?\n");
            printf("f - facil\n");
            printf("m - medio\n");
            printf("d - dificil\n\n");

            scanf("%*c%c",&nivel);

            switch (nivel)
            {
            case 'f':
                printf("\nOk, voce escolheu facil\n\n");
                break;
            case 'm':
                printf("\nInteressante, voce escolheu medio\n\n");
                break;
            case 'd':
                printf("\nGosta de desfios! Voce escolheu dificil\n\n");
                break;
            default:
                printf("\nEsta opcao e invalida");
                break;
            }
            break;
        case 2:
            printf("\nVoce escolheu 'Um amigo'\n");
            sleep(3);
            system("clear");
            break;
        case 3:
            printf("\nAte logo\n\n");
            break;

        default:
            printf("Esta opcao e invalida\n");
        }
    }
    while ( (p2 != 1) && (p2 != 2) && (p2 != 3) );

    return p2;
}

/***função q sorteia quem começa***/
int Quem_Comeca()
{
    int r;

    srand( (unsigned)time(NULL) );
    r=(rand()%2);

    printf("\nsorteando...\n");
    if (r == 1)
        printf("Jogador 1 começa\n\n");
    else
        printf("Jogador 2 começa\n\n");

    return r;
}



/***função para a jogada do usuario***/
int Jogada_Usuario(int lin, int col, char jog)
{
    int r= 0;

    if ( (lin > 3) || (col > 3) )
        r= 1;

    else if (mvelha[lin-1][col-1] != ' ')
        r= 2;
    else
        mvelha[lin-1][col-1]= jog;

    return r;
}


/***função que verifica quem ganhou***/
int Verifica_Ganhador(char jog)
{
    int g=0, i;

    for(i=0; i<3; i++)
        if ( (mvelha[i][0]==jog) && (mvelha[i][1]==jog) && (mvelha[i][2]==jog) )
        {
            g= 1;
            return g;
        }
    for(i=0; i<3; i++)
        if ( (mvelha[0][i]==jog) && (mvelha[1][i]==jog) && (mvelha[2][i]==jog) )
        {
            g= 1;
            return g;
        }
    if ( (mvelha[0][0]==jog) && (mvelha[1][1]==jog) && (mvelha[2][2]==jog) )
    {
        g= 1;
        return g;
    }
    else if ( (mvelha[0][2]==jog) && (mvelha[1][1]==jog) && (mvelha[2][0]==jog) )
    {
        g= 1;
        return g;
    }
    if ( (jogadas >= 9) && (g == 0) )
        g=2;


    return g;
}

/***função que imprime a matriz***/
void Imprime()
{
    printf("%c | %c | %c\n",mvelha[0][0], mvelha[0][1], mvelha[0][2]);
    printf("--+---+--\n");
    printf("%c | %c | %c\n",mvelha[1][0], mvelha[1][1], mvelha[1][2]);
    printf("--+---+--\n");
    printf("%c | %c | %c\n\n",mvelha[2][0], mvelha[2][1], mvelha[2][2]);
}


/***função contra o computador facil***/
void C_Facil(int *lin, int *col)
{
    int i, j, mat[9][2], l;

    l = 0;

    for(i=0; i<3; i++)
        for(j=0; j<3; j++)
            if (mvelha[i][j] == ' ')
            {
                mat[l][0] = i;
                mat[l][1] = j;
                l++;
            }

    srand( (unsigned)time(NULL) );
    l =(rand()%l);

    *lin = mat[l][0]+1;
    *col = mat[l][1]+1;
}


/***função contra o computador médio***/
void C_Medio(char jog2, int *lin, int *col);


/***função contra o computador difícil***/
void C_Dificil(char jog2, int *lin, int *col);


/***função de analise da primeira joogada***/
void Pri_Jog(char jog2, int *lin, int *col);





/*************************   função main   *************************/
int main ()

{
    char jog1= ' ', jog2= ' ', vez;
    int lin, col, e , m;

    system("clear");

    m = Menu();
    while (m != 3)
    {
        Inicializa_Velha();
        Escolha_Simb(&jog1, &jog2);

        printf("\njogador 1: %c\n",jog1);
        printf("jogador 2: %c\n",jog2);

        if (Quem_Comeca())
            vez= jog1;
        else
            vez= jog2;

        jogadas = 0;

        while ( ( !(Verifica_Ganhador(jog1)) )  && ( !(Verifica_Ganhador(jog2)) ) )
        {
            if ( (vez == jog1) || ( (vez == jog2) && (m == 2) ) )
            {
                printf("Jogador %c digite a linha e a coluna que deseja marcar\n", vez);
                scanf("%d",&lin);
                scanf("%d",&col);

                ultima[0] = lin;
                ultima[1] = col;

                printf("\n");
            }

            else
            {
                printf("Computador jogando...\n");
                sleep(3);

                if (nivel == 'f')
                    C_Facil(&lin, &col);

                else if (nivel == 'm')
                    C_Medio(vez, &lin, &col);

                else if (nivel == 'd')
                    C_Dificil(vez, &lin, &col);

                printf("\n");

            }

            e= (Jogada_Usuario(lin, col, vez));


            if (e == 0)
            {
                if (vez == 'X')
                    vez= 'O';
                else
                    vez= 'X';

                jogadas++;
            }
            else if (e == 1)
            {
                printf("Posicao invalida\n");
                sleep(2);
            }
            else
            {
                printf("Posicao ja preenchida\n");
                sleep(2);
            }


            system("clear");
            Imprime();

        }


        if ( ( (Verifica_Ganhador(jog1)) == 2 ) || ( (Verifica_Ganhador(jog2)) == 2 ) )
            printf("\n\n DEU VELHA!\n");

        if ( (Verifica_Ganhador(jog1)) == 1 )
            printf("\n\nJOGADOR 1, '%c', GANHOU!!\n", jog1);

        else if ( (Verifica_Ganhador(jog2)) == 1)
            printf("\n\nJOGADOR 2, '%c', GANHOU!!\n", jog2);

        m = Menu();
    }


    return 0;

}


/************************* função de analise da primeira jogada ****************************/
void Pri_Jog (char jog2, int *lin, int *col)
{
    int l;

    if (( (ultima[0]==1) && (ultima[1]==1) ) || ( (ultima[0]==1) && (ultima[1]==3) ) || ( (ultima[0]==3) && (ultima[1]==1) ) || ( (ultima[0]==3) && (ultima[1]==3) ))
    {
        if (mvelha[1][1] == ' ')
        {
            *lin= 2;
            *col= 2;
        }
        return;
    }

    else if ( (ultima[0] == 2) && (ultima[1] == 2) )
    {
        l = (rand()%2);
        if (l == 0)
            *lin = 1;
        else
            *lin = 3;


        l = (rand()%2);
        if (l == 0)
            *col = 1;
        else
            *col = 3;
        return;
    }

    else if (( (ultima[0]==1) && (ultima[1]==2) ) || ( (ultima[0]==2) && (ultima[1]==1) ) || ( (ultima[0]==2) && (ultima[1]==3) ) || ( (ultima[0]==3) && (ultima[1]==2) ))
    {
        l = (rand()%2);
        if (l == 0)
        {
            l = (rand()%2);
            if (l == 0)
                *lin = 1;
            else
                *lin = 3;

            l = (rand()%2);
            if (l == 0)
                *col = 1;
            else
                *col = 3;
        }

        else
        {
            *lin= 2;
            *col= 2;
        }
    }
}



/************************* função contra o computador médio ****************************/
void C_Medio(char jog2, int *lin, int *col)
{
    int i, j, mat[9][2], l, ai, aj;

    /*  Quando computador inicia o jogo */
    if (jogadas == 0)
    {
        *lin= 1;
        *col= 3;
        return;
    }

    /* Analise baseada na primeira jogada do jogador 1 */
    else if (jogadas == 1)
        Pri_Jog(jog2, lin, col);

    else if (jogadas > 1)
    {

        /* Laço que testa diagonal principal e ataca */
        j=0;
        for(i=0; i<3; i++)
        {
            ai = (i+1) % 3;
            aj = (j+1) % 3;
            if ( (mvelha[i][j] == mvelha[ai][aj]) && (mvelha[i][j] == jog2) )
            {
                ai = (ai+1) % 3;
                aj = (aj+1) % 3;
                if (mvelha[ai][aj] == ' ')
                {
                    *lin = ai+1;
                    *col = aj+1;
                    return;
                }
            }
            j++;
        }


        /* Trecho que testa diagonal secundária e ataca */
        if ( (mvelha[0][2] == mvelha [1][1]) && (mvelha[0][2] == jog2) && (mvelha[2][0] == ' ') )
        {
            *lin = 3;
            *col = 1;
            return;
        }
        else if ( (mvelha[0][2] == mvelha [2][0]) && (mvelha[0][2] == jog2) && (mvelha[1][1] == ' ') )
        {
            *lin = 2;
            *col = 2;
            return;
        }
        else if ( (mvelha[1][1] == mvelha [2][0]) && (mvelha[1][1] == jog2) && (mvelha[0][2] == ' ') )
        {
            *lin = 1;
            *col = 3;
            return;
        }
        /* Laço que testa diagonal principal e defende */
        j=0;
        for(i=0; i<3; i++)
        {
            ai = (i+1) % 3;
            aj = (j+1) % 3;
            if ( (mvelha[i][j] == mvelha[ai][aj]) && (mvelha[i][j] != jog2) )
            {
                ai = (ai+1) % 3;
                aj = (aj+1) % 3;
                if (mvelha[ai][aj] == ' ')
                {
                    *lin = ai+1;
                    *col = aj+1;
                    return;
                }
            }
            j++;
        }


        /* Trecho que testa diagonal secundária e defende */
        if ( (mvelha[0][2] == mvelha [1][1]) && (mvelha[0][2] != ' ') && (mvelha[0][2] != jog2) && (mvelha[2][0] == ' ') )
        {
            *lin = 3;
            *col = 1;
            return;
        }
        else if ( (mvelha[0][2] == mvelha [2][0]) && (mvelha[0][2] != ' ') && (mvelha[0][2] != jog2) && (mvelha[1][1] == ' ') )
        {
            *lin = 2;
            *col = 2;
            return;
        }
        else if ( (mvelha[1][1] == mvelha [2][0]) && (mvelha[1][1] != ' ') && (mvelha[1][1] != jog2) && (mvelha[0][2] == ' ') )
        {
            *lin = 1;
            *col = 3;
            return;
        }


        /* Demais jogadas */
        l = 0;
        for(i=0; i<3; i++)
            for(j=0; j<3; j++)
                if (mvelha[i][j] == ' ')
                {
                    mat[l][0] = i;
                    mat[l][1] = j;
                    l++;
                }

        srand( (unsigned)time(NULL) );
        l =(rand()%l);

        *lin = mat[l][0]+1;
        *col = mat[l][1]+1;

    }
}





/*************************  função contra o computador difícil *************************/
void C_Dificil(char jog2, int *lin, int *col)
{
    int i, j, ai, aj;

    srand( (unsigned)time(NULL) );

    /*  Quando computador inicia o jogo */
    if (jogadas == 0)
    {
        *lin= 1;
        *col= 3;
        return;
    }

    /* Analise baseada na primeira jogada do jogador 1 */
    else if (jogadas == 1)
        Pri_Jog(jog2, lin, col);

    /* Analise para as demais jogadas */
    else if (jogadas > 1)
    {

        /* Laço que testa diagonal principal e ataca */
        j=0;
        for(i=0; i<3; i++)
        {
            ai = (i+1) % 3;
            aj = (j+1) % 3;
            if ( (mvelha[i][j] == mvelha[ai][aj]) && (mvelha[i][j] == jog2) )
            {
                ai = (ai+1) % 3;
                aj = (aj+1) % 3;
                if (mvelha[ai][aj] == ' ')
                {
                    *lin = ai+1;
                    *col = aj+1;
                    return;
                }
            }
            j++;
        }


        /* Trecho que testa diagonal secundária e ataca */
        if ( (mvelha[0][2] == mvelha [1][1]) && (mvelha[0][2] == jog2) && (mvelha[2][0] == ' ') )
        {
            *lin = 3;
            *col = 1;
            return;
        }
        else if ( (mvelha[0][2] == mvelha [2][0]) && (mvelha[0][2] == jog2) && (mvelha[1][1] == ' ') )
        {
            *lin = 2;
            *col = 2;
            return;
        }
        else if ( (mvelha[1][1] == mvelha [2][0]) && (mvelha[1][1] == jog2) && (mvelha[0][2] == ' ') )
        {
            *lin = 1;
            *col = 3;
            return;
        }


        /* Laço que testa linhas e ataca */
        for(i=0; i<3; i++)
            for(j=0; j<3; j++)
            {
                aj = (j+1) % 3;
                if ( (mvelha[i][j] == mvelha[i][aj]) && (mvelha[i][j] == jog2) )
                {
                    aj = (aj+1) % 3;
                    if (mvelha[i][aj] == ' ')
                    {
                        *lin = i+1;
                        *col = aj+1;
                        return;
                    }
                }
            }

        /* Laço que testa colunas e ataca */
        for(j=0; j<3; j++)
            for(i=0; i<3; i++)
            {
                ai = (i+1) % 3;
                if ( (mvelha[i][j] == mvelha[ai][j]) && (mvelha[i][j] == jog2) )
                {
                    ai = (ai+1) % 3;
                    if (mvelha[ai][j] == ' ')
                    {
                        *lin = ai+1;
                        *col = j+1;
                        return;
                    }
                }
            }


        /* Laço que testa diagonal principal e defende */
        j=0;
        for(i=0; i<3; i++)
        {
            ai = (i+1) % 3;
            aj = (j+1) % 3;
            if ( (mvelha[i][j] == mvelha[ai][aj]) && (mvelha[i][j] != jog2) )
            {
                ai = (ai+1) % 3;
                aj = (aj+1) % 3;
                if (mvelha[ai][aj] == ' ')
                {
                    *lin = ai+1;
                    *col = aj+1;
                    return;
                }
            }
            j++;
        }


        /* Trecho que testa diagonal secundária e defende */
        if ( (mvelha[0][2] == mvelha [1][1]) && (mvelha[0][2] != ' ') && (mvelha[0][2] != jog2) && (mvelha[2][0] == ' ') )
        {
            *lin = 3;
            *col = 1;
            return;
        }
        else if ( (mvelha[0][2] == mvelha [2][0]) && (mvelha[0][2] != ' ') && (mvelha[0][2] != jog2) && (mvelha[1][1] == ' ') )
        {
            *lin = 2;
            *col = 2;
            return;
        }
        else if ( (mvelha[1][1] == mvelha [2][0]) && (mvelha[1][1] != ' ') && (mvelha[1][1] != jog2) && (mvelha[0][2] == ' ') )
        {
            *lin = 1;
            *col = 3;
            return;
        }


        /* Laço que testa linhas e defende */
        for(i=0; i<3; i++)
            for(j=0; j<3; j++)
            {
                aj = (j+1) % 3;
                if ( (mvelha[i][j] == mvelha[i][aj]) && (mvelha[i][j] != ' ') && (mvelha[i][j] != jog2) )
                {
                    aj = (aj+1) % 3;
                    if (mvelha[i][aj] == ' ')
                    {
                        *lin = i+1;
                        *col = aj+1;
                        return;
                    }
                }
            }

        /* Laço que testa colunas e defende */
        for(j=0; j<3; j++)
            for(i=0; i<3; i++)
            {
                ai = (i+1) % 3;
                if ( (mvelha[i][j] == mvelha[ai][j]) && (mvelha[i][j] != ' ') && (mvelha[i][j] != jog2) )
                {
                    printf("entrou!!!\n");
                    ai = (ai+1) % 3;
                    if (mvelha[ai][j] == ' ')
                    {
                        *lin = ai+1;
                        *col = j+1;
                        return;
                    }
                }
            }


        /* Laço que testa linhas e ataca */
        for(i=0; i<3; i++)
            for(j=0; j<3; j++)
            {
                if (mvelha[i][j] == jog2)
                {
                    aj = (j+1) % 3;
                    if (mvelha[i][aj] == ' ')
                    {
                        *lin = i+1;
                        *col = aj+1;
                        return;
                    }
                }
            }

        /* Laço que testa colunas e ataca */
        for(j=0; j<3; j++)
            for(i=0; i<3; i++)
            {
                if (mvelha[i][j] == jog2)
                {
                    ai = (i+1) % 3;
                    if (mvelha[ai][j] == ' ')
                    {
                        *lin = ai+1;
                        *col = j+1;
                        return;
                    }
                }
            }

        /* Laço que testa diagonal principal e ataca */
        j=0;
        for(i=0; i<3; i++)
        {
            if (mvelha[i][j] == jog2)
            {
                ai = (i+1) % 3;
                aj = (j+1) % 3;
                if (mvelha[ai][aj] == ' ')
                {
                    *lin = ai+1;
                    *col = aj+1;
                    return;
                }
            }
            j++;
        }


        /* Trecho que testa diagonal secundária e ataca */
        if ( (mvelha[0][2] == jog2) && (mvelha[1][1] == ' ') )
        {
            *lin = 2;
            *col = 2;
            return;
        }
        else if ( (mvelha[1][1] == jog2) && (mvelha[2][0] == ' ') )
        {
            *lin = 3;
            *col = 1;
            return;
        }
        else if ( (mvelha[2][0] == jog2) && (mvelha[0][2] == ' ') )
        {
            *lin = 1;
            *col = 3;
            return;
        }
    }
}

