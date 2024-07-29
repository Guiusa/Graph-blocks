#include "blocos.h"
#include <stdio.h>
#include <stdlib.h>

#define uint unsigned int

// ESTRUTURAS DE DADOS #########################################################
/*
 * Struct da fila
 *  - next      Próximo elemento queue_t da fila que está inserido
 *  - points    Endereço do nodo que esse elemento da fila referencia
 */
typedef struct queue_t {
    struct queue_t *next ;
    struct nodo_t *points ;
} queue_t ;

/*
* Struct do nodo
*  - adj        Fila de casas que são adjacentes ao nodo
*  - vizinhos   Quantos vizinhos tem no nodo
*/
typedef struct nodo_t {
    uint id ;
    struct queue_t *adj ;
    int vizinhos ;
} nodo_t ;
//##############################################################################



// FUNÇÕES AUXILIARES ##########################################################
/*
 * Inicializa um nodo no vetor principal do grafo
 */
static nodo_t *init_nodo_t(nodo_t* nodo, uint id) {
    nodo->adj = NULL ;
    nodo->vizinhos = 0 ;
    nodo->id = id ;
    return nodo ;
}



/*
 * Inicializa um elemento a ser adicionado nas listas de adjacência
 */
static queue_t *init_queue_t(nodo_t* points){
    queue_t* queue_node = (queue_t *) malloc(sizeof(queue_t)) ;
    queue_node->points = points ;
    queue_node->next = NULL ;
    return queue_node ;
}



/*
 * Adiciona um elemento à lista (adiciona no inicio para não percorrer)
 */
static void queue_append(nodo_t* head, queue_t* elem){
    elem->next = head->adj ;
    head->adj = elem ;
}



/*
 * Aloca um grafo com listas de adjacência
 */
static nodo_t* init_graph(uint n){
    nodo_t *graph = (nodo_t *) malloc(n * sizeof(nodo_t)) ;
    // Inicia todos os nodos do vetor principal
    for(uint i = 0; i<n; i++){
        nodo_t* aux = &graph[i] ;
        init_nodo_t(aux, i+1) ;
    }
    return graph ;
}



/*
 * Libera o grafo e inibe leaks
 */
static void destroy_graph(nodo_t *g, int n){
    for(int i = 0; i<n; i++)
        while(g[i].adj){
            queue_t *aux = g[i].adj ;
            g[i].adj = g[i].adj->next ;
            free(aux) ;
        }
    free(g) ;
}



/*
 * Printa os elementos enfileirados nas filas de adjacência
 */
static void print_fila(nodo_t* n){
    queue_t *aux = n->adj ;
    if(!aux) return ;
    while(aux){
        printf("->[%d]", aux->points->id) ;
        aux = aux->next ;
    }
}



/*
 * Printa o grafo
 */
static void print_graph(nodo_t *g, int n){
    for(int i = 0; i<n; i++){
        printf("%d\t", g[i].vizinhos) ;
        printf("\e[0;31m[%d]\e[0m", g[i].id) ;
        print_fila(&g[i]) ;
        printf("\n") ;
    }
}



/*
 * Lê o grafo da linha de comando
 */
static nodo_t* read_graph(void){
    uint n ;
    scanf("%d", &n) ;
    nodo_t *g = init_graph(n) ;
    
    uint v, u ;
    nodo_t *naux_v, *naux_u ;
    while(scanf("%u", &v) != EOF){
        scanf("%u", &u) ;
        naux_v = &g[v-1] ;
        naux_u = &g[u-1] ;

        queue_t* qaux_v = init_queue_t(naux_v) ;
        queue_t* qaux_u = init_queue_t(naux_u) ;
        
        queue_append(naux_v, qaux_u) ;
        queue_append(naux_u, qaux_v) ;

        naux_v->vizinhos++ ;
        naux_u->vizinhos++ ;
    }
    print_graph(g, n) ;
    return g ;
}
//##############################################################################



// IMPLEMENTAÇÃO DA BIBLIOTECA #################################################
info_t *info_blocos(unsigned int *num_blocos){
    nodo_t *g = read_graph() ;
    *num_blocos = 0 ;
    return NULL ;
}
//##############################################################################
