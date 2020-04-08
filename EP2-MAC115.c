/***************************************************/
/** Leonardo Machado Valadão   NUSP: 10299437     **/
/** Exercicio - Programa 02                       **/
/** Curso MAC-115 - Professora: Leliane de Nunes  **/
/***************************************************/

#include <stdio.h>

/* Definicao da funcao SENO */
double SIN (double x, double epsilon) {
    float sen=x, t=x;
    int k=1;

    while(t>epsilon || t<-epsilon) {
        t=-t*x*x/ ((2*k)*(2*k+1));
        sen=sen+t;
        k++;
    }
    return sen;
}
/* Definicao da funcao COSSENO */
double COS (double x, double epsilon) {
    float cos, t;
    int k=2;
    t=-((x*x)/(2));
    cos=1+t;

    while(t>epsilon || t<-epsilon) {
        t=t*((-x*x)/((2*k)*(2*k-1)));
        cos=cos+t;
        k++;
    }
    return cos;
}
/* Definicao da funcao ALTURA */
double ALTURA(double H , double teta) {
    /*teta esta em graus, precisamos passar para radianos*/
    double rad, seno, alt;
    rad=(3.141592653589793238462643383279/180)*teta;
    seno=SIN(rad,0.000001);
    alt=H*seno;
    return alt;
}
/* Definicao da funcao DISTANCIA */
double DISTANCIA(double H , double teta) {
    /*teta esta em graus, precisamos passar para radiano*/
    double rad, cosseno, dist;
    rad=(3.141592653589793238462643383279/180)*teta;
    cosseno=COS(rad,0.000001);
    dist=H*cosseno;
    return dist;
}
/* Definicao da funcao LOCALIZA */
int LOCALIZA(double *X, double *Y, double X1, double Y1, double D1, double X2, double Y2, double D2, double X3, double Y3, double D3) {
    double q13, q12, p12, p13;

    q13=(X1*X1-X3*X3+Y1*Y1-Y3*Y3-D1*D1+D3*D3)/(2*(X1-X3));
    q12=(X1*X1-X2*X2+Y1*Y1-Y2*Y2-D1*D1+D2*D2)/(2*(X1-X2));
    p12=(Y2-Y1)/(X1-X2);
    p13=(Y3-Y1)/(X1-X3);

    *Y=(q13-q12)/(p12-p13);
    *X=q12+(p12*(*Y));

    if ((X1-X2)==0 || (X1-X3)==0)
        return 0;
    else
        return 1;
}

int main () {
    int NUSP; /* numero USP do aluno localizado */
    int id1, id2, id3; /* identificadores de antenas */
    int NUSPultimo, Local; /* verificador de saida do programa e verificador de erro, respectivamente */
    double x1, x2, x3; /* coordenadas x das antenas */
    double y1, y2, y3; /* coordenadas y das antenas */
    double H1, H2, H3; /* distancias dos radares para o celular */
    double Teta1, Teta2, Teta3; /* angulos de incidencia horizontal */
    double X, Y; /* coordenadas absolutas do aluno */

    FILE *arq_entrada;

    /*abrir o arquivo de entrada */
    arq_entrada = fopen("entrada.txt", "r");
    if (arq_entrada == NULL) {
        /* caso arquivo nao encontrado */
        printf("ERRO: o arquivo entrada.txt nao foi encontrado\n");
        return 1;
    }
    else {
        /* caso arquivo seja encontrado */
        while (0==0) {
            /* leitura do NUSP do aluno localizado do arquivo de entrada */
            fscanf(arq_entrada, "%d", &NUSP);
            if (NUSPultimo!=NUSP) { /* caso este determinado NUSP ainda nao foi calculado */
                /* leitura dos dados das 3 antenas do arquivo de entrada */
                fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id1, &x1, &y1, &H1, &Teta1);
                fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id2, &x2, &y2, &H2, &Teta2);
                fscanf(arq_entrada, "%d %lf %lf %lf %lf", &id3, &x3, &y3, &H3, &Teta3);
                /* calculo da localizacao */
                Local = LOCALIZA(&X, &Y, x1, y1, (DISTANCIA(H1, Teta1)), x2, y2, (DISTANCIA(H2, Teta2)), x3, y3, (DISTANCIA(H3, Teta3)));
                /* Impressoes */
                if (Local==0)
                    printf("\n\nErro calculando posicao do aluno %d\n\n", NUSP);
                else {
                    printf("\nAntena %d, localizacao: ( %.4f, %.4f): \n", id1, x1, y1); printf("   Altura a1:      %.4f\n", ALTURA(H1, Teta1)); printf("   Distancia d1:   %.4f\n", DISTANCIA(H1, Teta1));
                    printf("\nAntena %d, localizacao: ( %.4f, %.4f): \n", id2, x2, y2); printf("   Altura a2:      %.4f\n", ALTURA(H2, Teta2)); printf("   Distancia d2:   %.4f\n", DISTANCIA(H2, Teta2));
                    printf("\nAntena %d, localizacao: ( %.4f, %.4f): \n", id3, x3, y3); printf("   Altura a3:      %.4f\n", ALTURA(H3, Teta3)); printf("   Distancia d3:   %.4f\n", DISTANCIA(H3, Teta3));
                    printf("\nLocalizacao absoluta do aluno de NUSP %d: (%.4f, %.4f)\n", NUSP, X, Y);
                }
                NUSPultimo=NUSP;
            }
            else {
                /* caso NUSP == NUSPultimo, o programa encerra */
                fclose(arq_entrada);
                return 0;
            }
        }
    }
}
