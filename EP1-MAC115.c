/***************************************************************/
/**                                                           **/
/** Leonardo Valadão                         NUSP: 10299437   **/
/** EP 01                                                     **/
/** Professora: Leliane                                       **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
/* stdlib.h inclui as funcoes rand() e srand() */
int main () {
    /* declare aqui todas as variaveis do seu EP */
    int semente, jogada, tipodejogo, n, pontojogador, pontopc, numerojogador, contador, asterisco, c00, c01, c10, c11, nanterior, natual;
    /* inicializacoes das variaveis*/

    printf("Escolha o tipo de jogo (1: Facil; 2: Dificil): ");
    scanf("%d", &tipodejogo);
    printf("Entre com o numero de jogadas: ");
    scanf("%d", &n);
    contador = 1;
    pontojogador=0;
    pontopc=0;

    /* leitura da semente */
    printf("Entre com a semente: ");
    scanf("%d", &semente);
    /* inicializacao do gerador de numeros aleatorios */
    srand(semente);
    /* outras inicializacoes */

    /* escreva aqui o seu programa */
    /* Modo de jogo facil */
    if (tipodejogo==1) {
        printf("Modo de jogo: Facil");

        while (contador <= n) {
            jogada = rand() % 2;
        printf("\nA maquina ja fez sua previsao, faca sua %da jogada: ", contador);
        scanf("%d", &numerojogador);
        printf("jogador = %d maquina = %d ", numerojogador, jogada);
        if (numerojogador==jogada) {
            printf("Maquina ganha!");
            pontopc = pontopc+1;
        }
        else {
            printf("Jogador ganha!");
            pontojogador = pontojogador+1;
        }

        printf("\nJOGADOR: ");
        asterisco = 0;
        while (asterisco < pontojogador) {
            printf("*");
            asterisco=asterisco+1;
        }
        printf("\nMAQUINA: ");
        asterisco = 0;
        while (asterisco < pontopc) {
            printf("*");
            asterisco=asterisco+1;
        }
        contador = contador+1;
        }
        if (pontojogador>pontopc) {
            printf("\nVoce venceu!");
        }
        else if (pontopc>pontojogador) {
            printf("\nA maquina venceu!");
        }
    }
    /* Modo de jogo dificil */
    else if (tipodejogo==2) {
        printf("Modo de jogo: Dificil");

        while (contador<=n) {
            if (contador<=2) {
                jogada = rand() % 2;
                printf("\nA maquina ja fez sua previsao, faca sua %da jogada: ", contador);
                scanf("%d", &numerojogador);

                if (contador==1) {
                    if (numerojogador==0) {
                        nanterior=0;
                    }
                    if (numerojogador==1) {
                        nanterior=1;
                    }
                }
                if (contador==2) {
                    if (numerojogador==0) {
                        natual=0;
                    }
                    if (numerojogador==1) {
                        natual=1;
                    }
                }

                printf("jogador = %d maquina = %d ", numerojogador, jogada);
                if (numerojogador==jogada) {
                    printf("Maquina ganha!");
                    pontopc = pontopc+1;
                }
            else {
                printf("Jogador ganha!");
                pontojogador = pontojogador+1;
            }

            printf("\nJOGADOR: ");
            asterisco = 0;
            while (asterisco < pontojogador) {
                printf("*");
                asterisco=asterisco+1;
            }
            printf("\nMAQUINA: ");
            asterisco = 0;
            while (asterisco < pontopc) {
                printf("*");
                asterisco=asterisco+1;

            }
            contador=contador+1;
            }
            else if (contador>2) {

                /* Verificação de comportamento */
                if (nanterior==0 && natual==0) {
                    c00++;
                }
                else if (nanterior==0 && natual==1){
                    c01++;
                }
                else if (nanterior==1 && natual==0) {
                    c10++;
                }
                else if (nanterior==1 && natual==1) {
                    c11++;
                }

                /* Estrategia para saber a proxima jogada */
                if (natual==0) {
                    if (c01>c00){
                        jogada=1;
                    }
                    if (c01<c00) {
                        jogada=0;
                    }
                    if (c01==c00) {
                        jogada = rand() % 2;
                    }
                }
                if (natual==1) {
                    if (c11>c10) {
                        jogada=1;
                    }
                    if (c11<c10) {
                        jogada=0;
                    }
                    if (c11==c10) {
                        jogada = rand() % 2;
                    }
                }
                /* Continuando o jogo */


                printf("\nA maquina ja fez sua previsao, faca sua %da jogada: ", contador);
                scanf("%d", &numerojogador);
                printf("jogador = %d maquina = %d ", numerojogador, jogada);
                if (numerojogador==jogada) {
                    printf("Maquina ganha!");
                    pontopc = pontopc+1;
                }
                else {
                    printf("Jogador ganha!");
                    pontojogador = pontojogador+1;
                }

                printf("\nJOGADOR: ");
                asterisco = 0;
                while (asterisco < pontojogador) {
                    printf("*");
                    asterisco=asterisco+1;
                }
                printf("\nMAQUINA: ");
                asterisco = 0;
                while (asterisco < pontopc) {
                    printf("*");
                    asterisco=asterisco+1;
                }


                contador = contador+1;
            }
        }
        if (pontojogador>pontopc) {
            printf("\nVoce venceu!");
        }
        else if (pontopc>pontojogador) {
            printf("\nA maquina venceu!");
        }
    }
    else {
        printf("Opcao invalida");
    }

    return 0;
}
