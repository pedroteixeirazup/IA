#include "stdio.h"
#include<stdio.h> 
#include<stdbool.h> 
#define N 4  

bool estaSeguro(int tabuleiro[N][N], int linha, int col) 
{ 
    int i, j; 
  

    for (i = 0; i < col; i++) 
        if (tabuleiro[linha][i]) 
            return false; 
  

    for (i=linha, j=col; i>=0 && j>=0; i--, j--) 
        if (tabuleiro[i][j]) 
            return false; 
  
    for (i=linha, j=col; j>=0 && i<N; i++, j--) 
        if (tabuleiro[i][j]) 
            return false; 
  
    return true; 
} 

bool resolve(int tabuleiro[N][N], int col) 
{ 

    if (col >= N) 
        return true; 

    for (int i = 0; i < N; i++) 
    { 
        
        if ( estaSeguro(tabuleiro, i, col) ) 
        { 
 
            tabuleiro[i][col] = 1; 
  
        
            if ( resolve(tabuleiro, col + 1) ) 
                return true; 
  
            tabuleiro[i][col] = 0; 
        } 
    } 
  

    return false; 
} 

void mostra(int tabuleiro[N][N]) 
{ 
    for (int i = 0; i < N; i++) 
    { 
        for (int j = 0; j < N; j++) 
            printf(" %d ", tabuleiro[i][j]); 
        printf("\n"); 
    } 
} 
  
int main() 
{ 
     int tabuleiro[4][4] = { 
        {0, 0, 0, 0}, 
        {0, 0, 0, 0}, 
        {0, 0, 0, 0}, 
        {0, 0, 0, 0} 
    }; 
  
    if ( resolve(tabuleiro, 0) == false ) 
    { 
      printf("Solucao nao encontrada.\n"); 
      return false; 
    } 
  
    mostra(tabuleiro); 
    return 0; 
} 
