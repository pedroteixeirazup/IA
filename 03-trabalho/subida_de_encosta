#include <stdio.h>
#include <stdlib.h>

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

void swap(int tabuleiro[], int i, int j){

   int tmp = tabuleiro[i];
   tabuleiro[i] = tabuleiro[j];
   tabuleiro[j] = tmp;

}

int main(){
   int N,i;

   printf("Escolha a quantidade de rainhas que desejas inserir no problema:");

   scanf("%d", &N);

   //Repesentação das posições das rainhas no tabuleiro;
   int tabuleiro[N];

   printf("Digite as colunas em que desejas colocar as rainhas no tabuleiro:");
   for(i = 0; i < N; i++) scanf("%d", &tabuleiro[i]);

   int melhorCusto = calculaCusto(tabuleiro,N), novoCusto, swaps = 0;

   while(melhorCusto > 0){
      int i;
      for(i = 0; i < N-1; i++){

         swap(tabuleiro,i,i+1);

         novoCusto = calculaCusto(tabuleiro,N);

         if(melhorCusto > novoCusto){

            printf("Antes do swap %d: \n", ++swaps);
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
