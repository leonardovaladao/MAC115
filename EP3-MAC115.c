/***************************************************/
/**                                               **/
/** Leonardo Machado Valadão   NUSP: 10299437     **/
/** Exercicio - Programa 03                       **/
/** Curso MAC-115 - Professora: Leliane de Nunes  **/
/**                                               **/
/***************************************************/

#include <stdio.h>
#define MAX 8 /*N<9*/

/* Prototipos das funcoes */
void le_mundo(int Mundo[MAX][MAX], int *N);
void imprime_percepcao(int Percebe[MAX][MAX], int N, int Ag_Lin, int Ag_Col, char Ag_Or);
void imprime_mundo(int Mundo[MAX][MAX], int N);
void atualiza_percepcaoEagente(int Percebe[MAX][MAX], int Mundo[MAX][MAX], int N, int *Wumpus, int *Flecha, int *Ouro, char Acao, int *Ag_Lin, int *Ag_Col, char *Ag_Or, int *Pontos);

/* Definicao das funcoes */
void le_mundo(int Mundo[MAX][MAX], int *N) {
    int i, j, item;

    /*abrir o arquivo de entrada */
    FILE *arq_entrada;
    arq_entrada = fopen("entrada.txt", "r");
    if (arq_entrada == NULL) {
        /* caso arquivo nao encontrado */
        printf("\nArquivo entrada.txt nao encontrado.\n");
    }
    /* caso arquivo seja encontrado */
    /*********************************************************************/
    else {
        fscanf(arq_entrada, "%d", N); N=*N; /*Le N */

        /* Percorre matriz Mundo preenchendo com zeros */
        /*********************************************************************/
        for(i=0;i<=N;i++) {
            for(j=0;j<=N;j++){
                Mundo[i][j]=0;
            }
        }
        /*********************************************************************/


        /* Percorre entrada.txt e preenche matriz com P(1), W(2), ou O(3) */
        /*********************************************************************/
        while(-1==-1){
            fscanf(arq_entrada, "%d %d %d", &i, &j, &item);
            Mundo[i][j]=item;
            if (feof(arq_entrada)) { /* Verifica se entrada.txt chegou ao fim */
                break;
            }
        }
        /*********************************************************************/
    }
    /*********************************************************************/
}
void imprime_mundo(int Mundo[MAX][MAX], int N) {
    int i, j, k;

    for (i=0;i<N*8+1;i++) printf("-"); /*Irá imprimir a borda superior da tabela */
    printf("\n");


    /* Percorre a matriz Mundo, imprimindo conforme o item no elemento */
    /*********************************************************************/
    for(i=1;i<=N;i++) {
            for(j=1;j<=N;j++){
                if(Mundo[i][j]==0)
                    printf("|       ");
                if(Mundo[i][j]==1)
                    printf("|   P   ");
                if(Mundo[i][j]==2)
                    printf("|   W   ");
                if(Mundo[i][j]==3)
                    printf("|   O   ");
            }
            printf("|\n"); /* Imprime separador de coluna */
            for (k=0;k<N*8+1;k++) printf("-"); /* Imprime borda que separa cada linha */
            printf("\n");
    }
    /*********************************************************************/
}
void imprime_percepcao(int Percebe[MAX][MAX], int N, int Ag_Lin, int Ag_Col, char Ag_Or) {
    int i, j, k;

    /*********************************************************************/
    for (i=0;i<N*8+1;i++) printf("-"); /*Irá imprimir a borda superior da tabela */
    printf("\n");
    /*********************************************************************/


    /* Percorre a matriz, imprimindo conforme o item no elemento */
    /*********************************************************************/
    for(i=1;i<=N;i++) {
            for(j=1;j<=N;j++){
                printf("|  ");
                if(i==Ag_Lin && j==Ag_Col) {
                    /* Se o agente estiver nesta casa, imprimira a orientacao dele */
                    printf("%c", Ag_Or);
                } else {
                    printf(" "); /* Se o agente nao estiver nesta casa, imprimira espaço em branco */
                }

                /* Imprime conforme elemento na matriz Percebe */
                /*********************************************************************/
                if(Percebe[i][j]== -1)  printf("?   ");
                if(Percebe[i][j]==000)  printf("    ");
                if(Percebe[i][j]==100)  printf("F   ");
                if(Percebe[i][j]==010)  printf("B   ");
                if(Percebe[i][j]==001)  printf("R   ");
                if(Percebe[i][j]==110)  printf("FB  ");
                if(Percebe[i][j]==011)  printf("BR  ");
                if(Percebe[i][j]==101)  printf("FR  ");
                if(Percebe[i][j]==111)  printf("FBR ");
                /*********************************************************************/

            }
            printf("|\n"); /* Imprime separador de coluna */
            for (k=0;k<N*8+1;k++) printf("-"); /* Imprime borda que separa cada linha */
            printf("\n");
    }
    /*********************************************************************/
}
void atualiza_percepcaoEagente(int Percebe[MAX][MAX], int Mundo[MAX][MAX], int N, int *Wumpus, int *Flecha, int *Ouro, char Acao, int *Ag_Lin, int *Ag_Col, char *Ag_Or, int *Pontos) {
    int i, Fedor=0, Brisa=0, Reflexo=0; /* Inicialmente, e considerado que nao ha Fedor, Brisa ou Reflexo */
    char UltimaPercepcao=0;


    /*Atualiza a posicao do agente e sua Percepcao (Opcao M) */
    /*********************************************************************/
    if(Acao=='M') {
        /* Muda posicao do agente */
        /*********************************************************************/
        if(*Ag_Or=='^') {
            if(*Ag_Lin==1) { /* Caso agente esteja na borda, recebera um choque */
                UltimaPercepcao='C';
            } else { /* Caso agente nao estiver na borda, se movera */
                *Ag_Lin=*Ag_Lin-1;
            }
        }
        if(*Ag_Or=='v') {
            if(*Ag_Lin==N) { /* Caso agente esteja na borda, recebera um choque */
                UltimaPercepcao='C';
            } else { /* Caso agente nao estiver na borda, se movera */
                *Ag_Lin=*Ag_Lin+1;
            }
        }
        if(*Ag_Or=='<') {
            if(*Ag_Col==1) { /* Caso agente esteja na borda, recebera um choque */
                UltimaPercepcao='C';
            } else { /* Caso agente nao estiver na borda, se movera */
                *Ag_Col=*Ag_Col-1;
            }
        }
        if(*Ag_Or=='>') {
            if(*Ag_Col==N) { /* Caso agente esteja na borda, recebera um choque */
                UltimaPercepcao='C';
            } else { /* Caso agente nao estiver na borda, se movera */
                *Ag_Col=*Ag_Col+1;
            }
        }
        /*********************************************************************/



        /* Verifica se ha Fedor, Brisa ou Reflexo */
        /*********************************************************************/
        if(Mundo[*Ag_Lin][*Ag_Col-1]==2 || Mundo[*Ag_Lin][*Ag_Col+1]==2 || Mundo[*Ag_Lin-1][*Ag_Col]==2 || Mundo[*Ag_Lin+1][*Ag_Col]==2)
            Fedor=1;

        if(Mundo[*Ag_Lin][*Ag_Col-1]==1 || Mundo[*Ag_Lin][*Ag_Col+1]==1 || Mundo[*Ag_Lin-1][*Ag_Col]==1 || Mundo[*Ag_Lin+1][*Ag_Col]==1)
            Brisa=1;

        if(Mundo[*Ag_Lin][*Ag_Col]==3)
            Reflexo=1;
        /*********************************************************************/



        /* Atualiza Matriz Percepcao caso haja Fedor, Brisa ou Reflexo */
        /*********************************************************************/
        if(Fedor==0 && Brisa==0 && Reflexo==0 && UltimaPercepcao!='C') {
            Percebe[*Ag_Lin][*Ag_Col]=000;
            UltimaPercepcao=' ';
        }
        if(Fedor==1 && Brisa==0 && Reflexo==0 && UltimaPercepcao!='C') {
            Percebe[*Ag_Lin][*Ag_Col]=100;
            UltimaPercepcao='F';
        }
        if(Fedor==0 && Brisa==1 && Reflexo==0 && UltimaPercepcao!='C') {
            Percebe[*Ag_Lin][*Ag_Col]=010;
            UltimaPercepcao='B';
        }
        if(Fedor==0 && Brisa==0 && Reflexo==1 && UltimaPercepcao!='C') {
            Percebe[*Ag_Lin][*Ag_Col]=001;
            UltimaPercepcao='R';
        }
        if(Fedor==1 && Brisa==1 && Reflexo==0 && UltimaPercepcao!='C') {
            Percebe[*Ag_Lin][*Ag_Col]=110;
            UltimaPercepcao='FB';
        }
        if(Fedor==0 && Brisa==1 && Reflexo==1 && UltimaPercepcao!='C') {
            Percebe[*Ag_Lin][*Ag_Col]=011;
            UltimaPercepcao='BR';
        }
        if(Fedor==1 && Brisa==0 && Reflexo==1 && UltimaPercepcao!='C') {
            Percebe[*Ag_Lin][*Ag_Col]=101;
            UltimaPercepcao='FR';
        }
        if(Fedor==1 && Brisa==1 && Reflexo==1 && UltimaPercepcao!='C') {
            Percebe[*Ag_Lin][*Ag_Col]=111;
            UltimaPercepcao='FBR';
        }
        /*********************************************************************/
    }
    /*********************************************************************/




    /* Atualiza orientacao do agente (Opcao E e D) */
    /*********************************************************************/
    i=0; /* Contador que permite que ele se mova uma vez por comando */
    if (Acao=='E') {
        if(*Ag_Or=='^' && i==0) {
            *Ag_Or='<'; i=1;
        }
        if(*Ag_Or=='v' && i==0) {
            *Ag_Or='>'; i=1;
        }
        if(*Ag_Or=='<' && i==0) {
            *Ag_Or='v'; i=1;
        }
        if(*Ag_Or=='>' && i==0) {
            *Ag_Or='^'; i=1;
        }
    }
    if (Acao=='D') {
        if(*Ag_Or=='^' && i==0) {
            *Ag_Or='>'; i=1;
        }
        if(*Ag_Or=='v' && i==0) {
            *Ag_Or='<'; i=1;
        }
        if(*Ag_Or=='<' && i==0) {
            *Ag_Or='^'; i=1;
        }
        if(*Ag_Or=='>' && i==0) {
            *Ag_Or='v'; i=1;
        }
    }
    /*********************************************************************/




    /* Atira flecha e mata Wumpus (Opcao T) */
    /*********************************************************************/
    if (Acao=='T' && *Flecha==0) {
        if( (*Ag_Or=='^' && Mundo[*Ag_Lin-1][*Ag_Col]==2) || (*Ag_Or=='v' && Mundo[*Ag_Lin+1][*Ag_Col]==2) || (*Ag_Or=='<' && Mundo[*Ag_Lin][*Ag_Col-1]==2) || (*Ag_Or=='>' && Mundo[*Ag_Lin][*Ag_Col+1]==2) ){
            UltimaPercepcao='U';
            *Wumpus=1;
            *Pontos=*Pontos+50;
        }
        *Flecha=1;
    }
    /*********************************************************************/

    /* Pega Ouro (Opcao G) */
    /*********************************************************************/
    if (Acao=='G' && *Ouro==0) {
        if(Mundo[*Ag_Lin][*Ag_Col]==3)
            *Ouro=1;
    }
    /*********************************************************************/

    /* Imprime qual foi a ultima percepcao do jogador */
    /*********************************************************************/
    printf("Percepção após a última opção:\n[%c]\n", UltimaPercepcao);
    /*********************************************************************/
}

int main () {
    /* Inicializacoes */
    /*********************************************************************/
    int Mundo[MAX][MAX], Percebe[MAX][MAX], N, Ag_Lin, Ag_Col, Pontos=0, i, j;
    int Wumpus=0, Flecha=0, Ouro=0; /* 0=Condicao Inicial; 1=Condicao modificada */
    char Ag_Or='^', Acao;
    /*********************************************************************/



    /* Leitura de mundo */
    /*********************************************************************/
    le_mundo(Mundo, &N);
    Ag_Lin=N;Ag_Col=1; /* Posicao inicial do agente */
    /*********************************************************************/


    /* Preenche percepcao inicial*/
    /*********************************************************************/
    for(i=1;i<=N;i++) {
        for(j=1;j<=N;j++)
            Percebe[i][j]=-1;
    }
    Percebe[N][1]=000; /* Percepcao da sala inicial eh nula */
    /*********************************************************************/




    while(-1==-1) { /* Codigo ira se repetir ate que programa encerre */
        printf("\n");

        /* Atualiza percepcao e agente com a ultima acao obtida */
        /*********************************************************************/
        atualiza_percepcaoEagente(Percebe, Mundo, N, &Wumpus, &Flecha, &Ouro, Acao, &Ag_Lin, &Ag_Col, &Ag_Or, &Pontos);
        /*********************************************************************/


        /* Se o agente decide sair do jogo */
        /*********************************************************************/
        if(Acao=='S' && Ag_Lin==N && Ag_Col==1) {
            if(Ouro==1) {
                Pontos=Pontos+100;
            } else if(Ouro==0) {
                Pontos=Pontos-10000;
            }
            printf("\nMundo completo:\n\n");
            imprime_mundo(Mundo, N);
            printf("Fim de jogo! Pontuação final: %d\n", Pontos);
            return 0;
        }
        /*********************************************************************/

        /* Se agente entrar num poco ou sala do Wumpus */
        /*********************************************************************/
        if((Mundo[Ag_Lin][Ag_Col]==2) || (Mundo[Ag_Lin][Ag_Col]==1)) {
            Pontos=Pontos-10000;
            printf("\nMundo completo:\n\n");
            imprime_mundo(Mundo, N);
            printf("Fim de jogo! Pontuação final: %d\n", Pontos);
            return 0;
        }
        /*********************************************************************/



        /* Caso programa nao encerre, imprimira matriz Percebe e perguntara a proxima acao do agente */
        /*********************************************************************/
        printf("Mundo conhecido pelo agente:\n\n");
        imprime_percepcao(Percebe, N, Ag_Lin, Ag_Col, Ag_Or);
        printf("Digite a opção desejada (M/T/D/E/G/S): ");
        scanf(" %c", &Acao);
        Pontos=Pontos-1; /* Ponto perdido por realizar acao */
        /*********************************************************************/
    }
}
