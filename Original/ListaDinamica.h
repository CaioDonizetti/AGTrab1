#ifndef _ListaDinamica_
#define _ListaDinamica_
#include "Árvore.h"

typedef struct dd{
    int cod;
    float distancia;
}info;

typedef struct n *lista;

lista criaLista(int k, int codAeroporto);
int eliminaLista(lista *l);
int insereNovo(lista l, info *nd);
int removeNo(lista l,int codigo);
int buscaCodigo(lista l,int codigo, info *dr);
void listaLista(lista l,TAD_ABB arvore);
info *retornaInfo(lista l, int v);
int retornaCodAeroporto(lista l);
int qtdaElementos(lista l);

#endif // _ListaDinamica_
