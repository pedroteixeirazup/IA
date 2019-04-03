#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
//CALCULA O CUSTO DO CONFRONTO DAS RAINHAS
int calculaCusto(int tabuleiro[],int N){
   int c = 0,i,j;

   for(i = 0; i < N ; i++){
      for(j = i+1; j < N; j++){
            if(tabuleiro[j] < tabuleiro[i])
               c++;
      }
   }

   return c;
}
//FAZ A TROCA DAS RAINHAS SE ESRTIVER CONFRONTO
void swap(int tabuleiro[], int i, int j){

   int tmp = tabuleiro[i];
   tabuleiro[i] = tabuleiro[j];
   tabuleiro[j] = tmp;

}

int main(){
   int N = 4,i;


    //COLUNAS EM QUE AS RAINHAS SE ENCONTRAM
   int tabuleiro[] = {4,1,3,2};

    printf("Ordem das rainhas:\n");
    for(i = 0; i < N; i++) printf("%d ", tabuleiro[i]);
    printf("\n\n\n");

   int melhorCusto = calculaCusto(tabuleiro,N), novoCusto, swaps = 0;

   //CONTROLA A MELHOR POSICAO PARA A RAINHA
   while(melhorCusto > 0){
      int i;
      for(i = 0; i < N-1; i++){

         swap(tabuleiro,i,i+1);

         novoCusto = calculaCusto(tabuleiro,N);

         if(melhorCusto > novoCusto){

            printf("Swap %d: \n", ++swaps);
            for(i = 0; i < N; i++) printf("%d ", tabuleiro[i]);
            printf("\n");
            melhorCusto = novoCusto;

         }else{
            swap(tabuleiro,i,i+1);
         }
      }
   }

   printf("Resposta Final: \n");

   for(i = 0; i < N; i++) printf("%d ",tabuleiro[i]);

 return 0;
}

