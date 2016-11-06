#ifndef _Grafos_
#define _Grafos_
#include "ListaDinamica.h"
#include "Árvore.h"

typedef struct gr grafo;

grafo *criaGrafo(int numVertices);
int addVertice(grafo *g, int codAeroporto);
lista retornaLista(grafo *g, int v);
int adicAresta(grafo *g,TAD_ABB arvore,int v1,int v2);
int remAresta(grafo *g, int v1, int v2);
int numVertices(grafo *g);
int grauVertice(grafo *g, int v);
int ehAdjacente(grafo *g, int v1, int v2);
int destroiGrafo(grafo **g);
void listaConexoes(grafo *g,TAD_ABB arvore,char *cidade);

#endif // _Grafos_
