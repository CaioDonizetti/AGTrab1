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

lista retornaLista(grafo *g, int v){
    if (!g) return NULL;
    return g->l[v];
}

int addVertice(grafo *g, int codAeroporto){
    if (!g) return 0;
    if (!(g->l[codAeroporto] = criaLista(1,codAeroporto))) return 0;
    return 1;
}

void listaConexoes(grafo *g,TAD_ABB arvore,char *cidade){
    RegistroArvore *reg = TAD_ABB_busca(arvore,cidade);
    if (!reg) {
        printf("\n      CIDADE NAO ENCONTRADA!\n\n");
        return;
    }
    if (!g) return;
    lista l;
    l = retornaLista(g,reg->cod);
    listaLista(l,arvore);
}

int adicAresta(grafo *g,TAD_ABB arvore,int v1,int v2){
    RegistroArvore *reg1 = TAD_ABB_busca(arvore,TAD_ABB_buscaCidade(arvore,v1));
    RegistroArvore *reg2 = TAD_ABB_busca(arvore,TAD_ABB_buscaCidade(arvore,v2));
    float distancia = calculaDistancia(*reg1,*reg2);
    info dado;
    dado.cod = v2;
    dado.distancia = distancia;
    if (!g) return 0;
    insereNovo(retornaLista(g,v1),&dado);
    dado.cod = v1;
    insereNovo(retornaLista(g,v2),&dado);
    return 1;
}

int remAresta(grafo *g,int v1,int v2){
    if (!g) return 0;
    removeNo(retornaLista(g,v1),v2);
    removeNo(retornaLista(g,v2),v1);
    return 1;
}

int numVertices(grafo *g){
    if (!g) return -1;
    return g->nVertices;
}

int grauVertice(grafo *g, int v){
    int i;
    if (!g) return -1;
    for (i=0;i<g->nVertices;i++)
        if (retornaCodAeroporto(g->l[i]) == v)
            return qtdaElementos(g->l[i]);
    return -1;
}

int ehAdjacente(grafo *g, int v1, int v2){
    info i;
    if (!g)
        return 0;
    lista l = retornaLista(g,v1);
    if (!l)
        return 0;
    if (!(buscaCodigo(l,v2,&i))) return 0;
    return 1;
}

int destroiGrafo(grafo **g){
    int i;
    if (!(*g)) return 0;
    for (i=1;i<(*g)->nVertices;i++)
        if (!(eliminaLista(&(*g)->l[i]))) return 0;
    free((*g)->l[0]);  //Como os aeroportos começam com o codigo 1, não é criada uma lista para a primeira posição do vetor
    free(*g);
    return 1;
}
