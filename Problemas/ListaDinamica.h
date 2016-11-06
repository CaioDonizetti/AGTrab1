#ifndef _ListaDinamica_
#define _ListaDinamica_

typedef struct dd{
    int cod;
    float distancia;
}info;

typedef struct n *lista;

lista criaLista(int k, int codAeroporto);
int eliminaLista(lista *l);
int insereNovo(lista l, info *nd);

#endif // _ListaDinamica_
