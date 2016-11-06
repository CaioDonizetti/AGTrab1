#ifndef _ListaMenorCaminho_
#define _ListaMenorCaminho_
#include "Árvore.h"
#include "Grafos.h"

typedef struct s{
    int codAeroporto;
    char cidade[30];
    float distancia;
} dado;

typedef struct nn *lista_MN;

int eliminaLista_MN(lista_MN *l);
int listaLista_MN(lista_MN l);
lista_MN menorCaminho(grafo *g, TAD_ABB a, char *origem, char *destino);

#endif
