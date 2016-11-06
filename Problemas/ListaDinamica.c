#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaDinamica.h"

typedef struct m{info dado; struct m *prox;} noLista;
typedef struct n{
    noLista *head;
    int n, ord, cod;
} noDescritor;

lista criaLista(int k, int cod){
    lista aux;
    if((k<0)||(k>2)) return NULL;
    aux = (noDescritor *)malloc(sizeof(noDescritor));
    if(!(aux)) return NULL;
    aux->head = NULL;
    aux->ord = k;
    aux->n = 0;
    aux->cod = cod;
    return aux;
}


int eliminaLista(lista *l){
    if (!(*l)) return 0;
    noLista *p,*aux;
    p = aux = (*l)->head;
    while(p){
        aux = p;
        p=aux->prox;
        free(aux);
    }
    (*l)->n = 0;
    free(*l);
    return 1;
}

int insereNovo (lista l, info *nd){
    if(!(l)) return 0;
    switch (l->ord){
        case 0: return (insereOrd(l, nd));
                break;
        case 1: return (insereCabeca(l, nd));
                break;
        case 2: return (insereCauda(l, nd));
                break;
    }
    return 0;
}

int insereCabeca(lista l, info *nd){
    noLista *p;
    p = (noLista*)malloc(sizeof(noLista));
    if (!(p)) return 0;
    p->dado = *nd;
    p->prox = l->head;
    l->head = p;
    l->n++;
    return 1;
}

int insereOrd(lista l, info *nd){
    noLista *p, *paux, *pant;
    p=(noLista*)malloc(sizeof(noLista));
    if(!(p)) return 0;
    p->dado = *nd;
    p->prox = NULL;
    l->n++;
    if(!(l->head)){
        l->head = p;
        return 1;
    }
    paux=pant=l->head;
    while((nd->cod > paux->dado.cod)&&(paux)){
        pant = paux;
        paux = paux->prox;
    }
    paux=l->head;
    if(paux){
        p->prox = l->head;
        l->head = p;
    } else {
        pant->prox = p;
        p->prox = paux;
    }
    return 1;
}

int insereCauda (lista l, info *nd){
    noLista *p, *aux;
    p = (noLista*)malloc(sizeof(noLista));
    if(!(p)) return 0;
    p->dado = *nd;
    p->prox = NULL;
    aux = l->head;
    if (aux){
        while(aux->prox)
            aux=aux->prox;
        aux->prox=p;
    }else
        l->head=p;
    return 1;
}

int qtdaElementos(lista l){
    if (!l) return -1;
    return l->n;
}

info *retornaInfo(lista l, int v){
    int i = 0;
    noLista *aux;
    aux = l->head;
    while ((aux) && (i < v)){
        aux = aux->prox;
        i++;
    }
    return &(aux->dado);
}

