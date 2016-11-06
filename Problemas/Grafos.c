#include <stdlib.h>
#include <stdio.h>
#include "Grafos.h"

struct gr{
    lista *l;
    int nVertices;
};

grafo *criaGrafo(int numVertices){
    lista *l = (lista*)malloc(sizeof(lista)*numVertices);
    if (!(l)) return NULL;
    grafo *g = (grafo *)malloc(sizeof(struct gr));
    if (!(g)){
        eliminaLista(l);
        free(l);
        return NULL;
    }
    g->l = l;
    g->nVertices = numVertices;
    return g;
}

int adicAresta(grafo *g,int v1,int v2){
    float distancia = 1;
    info dado;
    dado.cod = v2;
    dado.distancia = distancia;
    if (!g) return 0;
    insereNovo(retornaLista(g,v1),&dado);
    return 1;
}

lista retornaLista(grafo *g, int v){
    if (!g) return NULL;
    return g->l[v];
}

int addVertice(grafo *g, int cod){
    if (!g) return 0;
    if (!(g->l[cod] = criaLista(1,cod))) return 0;
    return 1;
}

int numVertices(grafo *g){
    if (!g) return -1;
    return g->nVertices;
}

int destroiGrafo(grafo **g){
    int i;
    if (!(*g)) return 0;
    for (i=1;i<(*g)->nVertices;i++)
        if (!(eliminaLista(&(*g)->l[i]))) return 0;
    free((*g)->l[0]);  //Como os aeroportos come�am com o codigo 1, n�o � criada uma lista para a primeira posi��o do vetor
    free(*g);
    return 1;
}
