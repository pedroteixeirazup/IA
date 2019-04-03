#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000000
#define N 4
#define TABU N/2


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

int proxPasso(int rainhas[N], int tabu[TABU]){


    int lAux[N], lessValue = MAX, posRainha, posTabela, conflitoRainha, aux;

    memcpy(lAux, rainhas, sizeof(int)*N);

    for(int i = 0; i < N; i++){
        while(procura(tabu, i))
            i++;
        for(int j = 0; j < N; j++){
            lAux[i] = j;
            conflitoRainha = verificaCustoRainha(lAux);
            aux = conflitoRainha - 1;

            if(aux < lessValue && rainhas[i] != j){
                lessValue = aux;
                posRainha = i;
                posTabela = j;
            }
        }
    }

    rainhas[posRainha] = posTabela;
    conflitoRainha = verificaCustoRainha(rainhas);
    insereLista(tabu, posRainha);

    if(conflitoRainha == 0)
        return 1;

    if(proxPasso(rainhas, tabu))

        return 1;
    return 0;
}

int procura(int list[], int aux){
    for(int i = 0; i < TABU; i++)

        if(list[i] == aux)
            return 1;
    return 0;
}

void insereLista(int list[TABU], int number){

    int aux;
    for(int i = 0; i < TABU; i++){
        aux = list[i];
        list[i] = number;
        number = aux;
    }
}
int main(){
    int rainhas[N],tabu[TABU],conflitoRainha;

    for(int i = 0; i < N; i++)
        rainhas[i] = 0;

    for(int i = 0; i < N; i++)
        tabu[i] = -1;

    proxPasso(rainhas,tabu);

    printf("Ordem das rainhas:\n");
    for(int i = 0; i < N; i++){
        printf("%d ", rainhas[i]);
    }
    printf("\n");
    conflitoRainha = verificaCustoRainha(rainhas);
    printf("O numero de rainhas em conflito e: %d", conflitoRainha);

    return 0;
}

