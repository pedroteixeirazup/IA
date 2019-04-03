/*Este programa se encontra em um LOOP, pois ele encontra um mínimo local*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000000
#define N 4


int verificaCustoRainha(int rainhas[N]){
    int custo = 0,i,j;
    int cont;

    for(i = 0; i < N - 1; i++){
        cont = 1;
        for(j =  i + 1; j < N; j++){
            if(rainhas[i] == rainhas[j] || rainhas[j] == rainhas[i] + cont || rainhas[j] ==  rainhas[i] - cont)
                custo++;
            cont++;
        }
    }
    return custo;
}

int proxPasso(int rainhas[N]){

    int lAux[N], possVisited[N];
    int velho = MAX,posRainha, posTabela, conflitoRainha, aux;;

    memcpy(lAux, rainhas, sizeof(int)*N);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            lAux[i] = j;
            conflitoRainha = verificaCustoRainha(lAux);
            aux = conflitoRainha - 1;

            if(aux < velho && rainhas[i] != j){
                velho = aux;
                posRainha = i;
                posTabela = j;
                printf("Posicao da rainha: %d, \nPosicao da tabela: %d, \nvelho: %d\n", posRainha, posTabela, velho);
                printf("\n-------------------------------------------------------\n");
                system("pause");
            }
        }
    }
        rainhas[posRainha] = posTabela;
        conflitoRainha = verificaCustoRainha(rainhas);
        if(conflitoRainha == 0)
            return 1;
        if(proxPasso(rainhas))
            return 1;
    return 0;
}

int main(){
    int rainhas[N];
    int conflitoRainha;

    for(int i = 0; i < N; i++)
        rainhas[i] = 0;

    proxPasso(rainhas);

    for(int i = 0; i < N; i++){
        printf("%d ", rainhas[i]);
    }
    printf("\n");
    conflitoRainha = verificaCustoRainha(rainhas);
    printf("O numero de rainhas em conflito e: %d", conflitoRainha);

    return 0;
}

