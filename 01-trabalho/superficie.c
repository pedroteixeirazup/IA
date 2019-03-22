#include <stdio.h>
#include <stdlib.h>
#define MAX 10101010
#include <math.h>

typedef struct node{
  int data;
  struct node *next;
}Node;

typedef struct queue{
  int size;
  Node *head;
  Node *tail;
}Queue;
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
/* FILA*/
Queue* make_queue(){
  Queue *q;
  q = (Queue*) malloc(sizeof(Queue));
  q->size = 0;
  q->head = NULL;
  q->tail = NULL;
  return q;
}

int empty(Queue* q){
  return (q->size == 0);
}

void push(Queue* q, int n){
  Node *new;
  new = (Node*) malloc(sizeof(Node));
  if(empty(q)){
    new->data = n;
    new->next = NULL;
    q->head = new;
    q->tail = new;
  }
  else{
    new->data = n;
    new->next = NULL;
    q->tail->next = new;
    q->tail = new;
  }
  q->size++;
}

void pop(Queue* q){
    Node *aux;
    aux = q->head;
    if(q->size == 1){
        q->head = NULL;
        q->tail = NULL;
    }
    else
        q->head = q->head->next;
    free(aux);
    q->size--;
}

int front(Queue* q){
  return q->head->data;
}

void free_queue(Queue* q){
   while(!empty(q))
      pop(q);
   free(q);
}
/* FIM FILA*/
/*Largura*/
void bfs(Grafo *g, int v){
   int *seen;
   seen = (int*) calloc(g->qtde_verticesices, sizeof(int));

   int u;
   struct no *aux;
   Queue *q;
   q = make_queue();

   seen[v] = 1;
   push(q, v);
   while(!empty(q)){
      u = front(q);
      pop(q);
      printf(" -> %s\n", mapa[u]);

      for(aux = g->aresta[u]; aux != NULL; aux = aux->prox){
         if(!seen[aux->vertices]){
            seen[aux->vertices] = 1;
            push(q, aux->vertices);
         }
      }
   }
   free_queue(q);
   printf("\nSeen: ");
   int i;
   for(i = 0; i < g->qtde_verticesices; i++)
      printf("%d ", seen[i]);
}

int main(){
  Grafo *g = NULL;

  g = cria_grafo(19);

  int i,j;


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

    bfs(g,0);

  printf("\n");

  libera_grafo(&g);
return 0;
}

