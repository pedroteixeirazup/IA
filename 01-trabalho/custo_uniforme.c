#include <stdio.h>
#include <stdlib.h>
#define MAX 10101010
#include <math.h>

struct no{
  int vertices,peso;
  struct no* prox;
};
struct grafo{
  int qtde_verticesices, qtde_arestas;
  int *grau;
  struct no** aresta;
};
typedef struct grafo Grafo;

/*Mapa*/
 char mapa[100][100] = {"Oradea","Zerind","Arad","Sibiu","Timisoara","Fagaras",
    "Rimnicu_Vilcea","Lugoj","Pitesti","Mehadia","Drobeta","Craiova","Bucareste","Giurgiu","Urziceni","Hirsova","Eforie","Vaslui","Iasi","Neamt"};



Grafo *cria_grafo(int nro_verticesices){
  if(nro_verticesices <=0) return NULL;
  Grafo *g = (Grafo *) malloc(sizeof(Grafo));
  if(g == NULL) return NULL;

  g->qtde_verticesices = nro_verticesices;
  g->qtde_arestas = 0;
  g->grau = (int *) calloc(nro_verticesices,sizeof(int ));
  if(g->grau == NULL){
    free(g); return NULL;
  }
  g->aresta = (struct no **) malloc(nro_verticesices*sizeof(struct no*));
  if(g->aresta == NULL){
    free(g->grau); free(g); return NULL;
  }
  int i,j;
  for(i=0;i<nro_verticesices;i++){
    g->aresta[i] = NULL;
  }
  return g;
}
int insere_aresta(Grafo *g,int v1,int v2,int p){
  if(g == NULL || v1 <0 || v2 <0 || v1>g->qtde_verticesices || v2 > g->qtde_verticesices) return -1;

  struct no *aux = g->aresta[v1];
  while(aux != NULL && aux->vertices != v2){
        aux = aux->prox;
 }
 if(aux != NULL) return 0;

struct no *novo = (struct no*) malloc(sizeof(struct no));

  if(novo == NULL) return 0;

  novo->vertices = v2;
  novo->peso = p;
  novo->prox = g->aresta[v1];
  g->aresta[v1] = novo;

  (g->qtde_arestas)++;
  g->grau[v1]++;
  g->grau[v2]++;

  return 1;
}

void printa_verticesices(Grafo *g){
  int i,j;
  printf("Grau:");
  for(i=0;i<g->qtde_verticesices;i++){
    printf("%d ",g->grau[i]);
  }
  struct no *aux;
  printf("\n");
  printf("Grafo:\n");
    for(i=0;i<g->qtde_verticesices;i++){
      printf("%d ",i);
      aux = g->aresta[i];
      while(aux!=NULL){
        printf("%d-%d ",aux->vertices,aux->peso);
        aux = aux->prox;
  }
  printf("\n");
}
  printf("\n");
}
int verifica_grafo(Grafo *g,int v1,int v2){
  if(g == NULL || v1 <0 || v2 <0 || v1>g->qtde_verticesices || v2 > g->qtde_verticesices) return -1;

  struct no *aux = g->aresta[v1];
  while(aux!=NULL &&  aux->vertices!= v2)
    aux = aux->prox;

    if(aux == NULL) return 0;
    else return 1;
}

int remove_aresta(Grafo *g,int v1,int v2){
  if(g == NULL || v1 <0 || v2 <0 || v1>g->qtde_verticesices || v2 > g->qtde_verticesices) return -1;

  struct no *aux = g->aresta[v1];
  struct no *ant = NULL;

  while(aux!=NULL && aux->vertices != v2){
        ant = aux;
        aux = aux->prox;
  }
  if(aux == NULL) return 0;

  if(ant == NULL){
    g->aresta[v1] = aux->prox;
  }else{
    ant = aux->prox;
  }
  free(aux);
  g->qtde_arestas--;
  g->grau[v1]--;
  g->grau[v2]--;
  return 1;
}

int consulta_aresta(Grafo *g,int v1,int v2,int *p){
  if(g == NULL || v1 <0 || v2 <0 || v1>g->qtde_verticesices || v2 > g->qtde_verticesices) return -1;

  struct no * aux = g->aresta[v1];
    while(aux!=NULL && aux->vertices != v2){
          aux = aux->prox;
    }
    if(aux == NULL) return 0;
    else *p = aux->peso;

    return 1;
}
void libera_grafo(Grafo **g){
  int i,j;
  struct no *aux;
  struct no *aux2;
  for(i=0;i<(*g)->qtde_verticesices;i++){
    aux = (*g)->aresta[i];
    while(aux!=NULL){
      aux2 = aux;
      aux = aux->prox;
      free(aux2);
    }
  }
  free((*g)->aresta);
  free((*g)->grau);
  free((*g));
  g = NULL;
}
void mostra_adjacentes(Grafo *g,int v){
  struct no*  aux;
  if(g == NULL || v <0 || v>g->qtde_verticesices)
    printf("Grafo inexistente ou verticesice invalido!\n");

     aux = g->aresta[v];

    if(aux == NULL)
      printf("O verticesice, %d , nao possui adjacentes\n",v);

        while(aux!=NULL){
          // Escreva (V, "->", aux->verticesice, "=", aux->peso);
           printf("V -> %d = %d\n",aux->vertices,aux->peso);
           aux = aux->prox;
      }

}
void mostra_grafo(Grafo *g){
    if(g == NULL) printf("Grafo inexistente\n");
    else if(g->qtde_arestas == 0) printf("Grafo vazio\n");
    int i,j;
    struct no*aux;
    for(i=0;i<g->qtde_verticesices;i++){
      printf("verticesive %d: ",i);
      printf("\n");
      mostra_adjacentes(g,i);
    }
}
void show_path(int init, int end, int *path){
   if(init == end)
      printf("%s", mapa[init]);
   else if(path[end] == -1)
      printf("Nao existe caminho de %s para %s\n", mapa[init],mapa[end]);
   else{
      show_path(init, path[end], path);
      printf("-> %s", mapa[end]);
   }
}

int min_distance(int *dist, int *seen, int n){
   int min = MAX, minpos,i;
   for(i = 0; i < n; i++){
      if(!seen[i] && dist[i] < min){
         min = dist[i];
         minpos = i;
      }
   }
   return minpos;
}
/*Custo uniforme*/
void dijkstra(Grafo *g, int init, int end){
   //Change aux->data for 1 to use unweigthed graph.
   int *dist,*seen,*path,i,j;
   path = (int*) malloc(g->qtde_verticesices*sizeof(int));
   seen = (int*) calloc(g->qtde_verticesices, sizeof(int));
   dist = (int*) malloc(g->qtde_verticesices*sizeof(int));

   for(i = 0; i < g->qtde_verticesices; i++)
      dist[i] = MAX, path[i] = -1;

   dist[init] = 0;
   struct no *aux;

   for(i = 0; i < g->qtde_verticesices-1; i++){
      int u = min_distance(dist, seen, g->qtde_verticesices);
      seen[u] = 1;

      for(aux = g->aresta[u]; aux != NULL; aux = aux->prox){
         if(!seen[aux->vertices] && dist[u] != MAX && (dist[u] + aux->peso < dist[aux->vertices])){
            dist[aux->vertices] = dist[u] + aux->peso;
            path[aux->vertices] = u;
         }
      }
   }
   printf("A menor distancia  de %s ate  %s: %d\nMenor caminho: ", mapa[init],mapa[end],dist[end]);
   show_path(init, end, path);
}
int main(){
  Grafo *g = NULL;
  int numvertices,peso;

  g = cria_grafo(19);


  insere_aresta(g,0,1,71);
  insere_aresta(g,0,3,151);
  insere_aresta(g,1,2,75);
  insere_aresta(g,2,3,140);
  insere_aresta(g,3,5,99);
  insere_aresta(g,2,4,118);
  insere_aresta(g,3,6,80);
  insere_aresta(g,4,7,118);
  insere_aresta(g,6,8,97);
  insere_aresta(g,8,12,101);
  insere_aresta(g,6,11,146);
  insere_aresta(g,7,9,70);
  insere_aresta(g,7,10,75);
  insere_aresta(g,10,12,120);
  insere_aresta(g,12,8,138);
  insere_aresta(g,12,13,90);
  insere_aresta(g,12,14,85);
  insere_aresta(g,14,15,98);
  insere_aresta(g,15,16,86);
  insere_aresta(g,14,17,142);
  insere_aresta(g,17,18,92);
  insere_aresta(g,18,19,87);


    dijkstra(g,0,12);

  libera_grafo(&g);
return 0;
}


