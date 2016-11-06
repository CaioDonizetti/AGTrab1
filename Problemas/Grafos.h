#ifndef _Grafos_
#define _Grafos_
#include "ListaDinamica.h"

typedef struct gr grafo;

grafo *criaGrafo(int numVertices);
lista retornaLista(grafo *g, int v);
int adicAresta(grafo *g, int v1,int v2);
int addVertice(grafo *g, int cod);
int numVertices(grafo *g);
int destroiGrafo(grafo **g);

#endif // _Grafos_
