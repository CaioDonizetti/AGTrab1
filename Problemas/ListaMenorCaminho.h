#ifndef _ListaMenorCaminho_
#define _ListaMenorCaminho_
#include "Grafos.h"

typedef struct s{
    int cod;
    float distancia;
} dado;

typedef struct nn *lista_MN;

int eliminaLista_MN(lista_MN *l);
int listaLista_MN(lista_MN l, int *caminho);
lista_MN menorCaminho(grafo *g,int origem, int destino);

#endif
