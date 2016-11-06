#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaMenorCaminho.h"
#include "Grafos.h"

typedef struct mn{
    dado informacao;
    int flag;
    struct mn *prox, *pai;
} noLista_MN;

typedef struct nn{
    noLista_MN *head;
    int n, ord;
    int origem,destino;
    float distanciaAtual;
} noDescritor_MN;

lista_MN criaLista_MN(int k, int Origem, int Destino){
    lista_MN aux;
    if((k<0)||(k>2)) return NULL;
    aux = (noDescritor_MN *)malloc(sizeof(noDescritor_MN));
    if(!(aux)) return NULL;
    aux->origem = Origem;
    aux->destino = Destino;
    aux->head = NULL;
    aux->ord = k;
    aux->n = 0;
    aux->distanciaAtual = 0;
    return aux;
}

int insereNovo_MN (lista_MN l, dado nd, noLista_MN *pai){
    if(!(l)) return 0;
    switch (l->ord){
        case 0: return (insereOrd_MN(l, nd, pai));
                break;
        case 1: return (insereCabeca_MN(l, nd, pai));
                break;
        case 2: return (insereCauda_MN(l, nd, pai));
                break;
    }
    return 0;
}


int insereCabeca_MN(lista_MN l, dado nd, noLista_MN *pai){
    noLista_MN *p;
    p = (noLista_MN*)malloc(sizeof(noLista_MN));
    if (!(p)) return 0;
    p->informacao = nd;
    p->prox = l->head;
    p->pai = pai;
    p->flag = 0;
    l->head = p;
    l->n++;
    return 1;
}

int insereOrd_MN(lista_MN l, dado nd, noLista_MN *pai){
    noLista_MN *p, *paux, *pant;
    p=(noLista_MN*)malloc(sizeof(noLista_MN));
    if(!(p)) return 0;
    p->informacao = nd;
    p->prox = NULL;
    p->pai = pai;
    p->flag = 0;
    l->n++;
    if(!(l->head)){
        l->head = p;
        return 1;
    }
    paux=pant=l->head;
    while((nd.distancia > paux->informacao.distancia)&&(paux)){
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

int insereCauda_MN (lista_MN l, dado nd, noLista_MN *pai){
    noLista_MN *p, **aux;
    p = (noLista_MN*)malloc(sizeof(noLista_MN));
    if(!(p)) return 0;
    nd.distancia = nd.distancia + l->distanciaAtual;
    p->informacao = nd;
    p->prox = NULL;
    p->pai = pai;
    p->flag = 0;
    aux = &l->head;
    while(*aux){
        if ((*aux)->informacao.cod == p->informacao.cod){ //Se esse elemento ja estiver na lista...
            if (p->informacao.distancia <=  (*aux)->informacao.distancia){  //...e sua distancia for menor que a distancia atual
                (*aux)->informacao.distancia = p->informacao.distancia;     //...atualiza dist�ncia
                (*aux)->pai = pai;                                          //...e atualiza o n� pai
                return 1;
            }
            else return 1;                                      //Caso contrario (se estiver na lista, mas a distancia for maior), sai sem fazer nada
        }
        aux=&(*aux)->prox;
    }
    *aux=p;
    l->n++;
    return 1;
}

int menorElemento(lista_MN l, noLista_MN **no){
    noLista_MN *aux = l->head;
    noLista_MN *menor;
    while (aux){
        if (aux->flag == 0){
            menor = aux;
            break;
        }
        aux = aux->prox;
    }
    if (!aux) return 0;
    while (aux){
        if (aux->flag == 0)
            if ((menor->informacao.distancia > aux->informacao.distancia))
                menor = aux;
        aux = aux->prox;
    }
    *no = menor;
    if (*no) {
        (*no)->flag = 1;
        l->distanciaAtual = (*no)->informacao.distancia;
        return 1;
    }
    return 0;
}

lista_MN menorCaminho(grafo *g, int origem, int destino){
    //Variaveis para controle
    int retorno;
    noLista_MN *no;
    no = NULL;
    lista listaGrafo;
    info *dadoLista;
    int i;
    //Criando lista
    lista_MN lista = criaLista_MN(2,origem,destino);  //Cria lista, defininda a inser��o pela cauda
    if (!lista) { printf("    ERRO AO CRIAR LISTA DE MENOR CAMINHO!"); return NULL; }

    //Inserindo o vertice de origem
    dado inf;
    inf.cod = origem;
    inf.distancia = 0;
    insereNovo_MN(lista,inf, NULL);  //Insere na lista o vertice de origem
    retorno = menorElemento(lista,&no); //Procura o no que contem o menor elemento

    //Loop para encontrar o menor caminho
    while (no->informacao.cod!=destino){  //Enquanto o menor caminho n�o for o que leva � cidade de destino...

        if (!retorno) { printf("\n\n    NAO E POSSIVEL CHEGAR A %s SAINDO DE %s!\n\n",destino, origem); return NULL; }
        listaGrafo = retornaLista(g,no->informacao.cod);  //Retorna as conexoes dos vertices com menor caminho atual...

        for (i=0;i<qtdaElementos(listaGrafo);i++){ //Para cada elemento da lista 
            dadoLista = retornaInfo(listaGrafo,i);
            if (dadoLista){
                inf.cod = dadoLista->cod;
                inf.distancia = dadoLista->distancia;

                retorno = insereNovo_MN(lista,inf,no);
                if (!retorno) printf("    ERRO AO INSERIR ELEMENTO NA LISTA DE MENOR CAMINHO: Vertice %d",inf.cod);
            }
        }

        retorno = menorElemento(lista,&no); //Procura o no que contem o menor elemento
    }

    //Criando nova lista para inserir os vertices encontrados por onde se deve passar no menor caminho
    lista_MN listaResult = (criaLista_MN(1,origem,destino)); //Inser��o pela cabe�a
    while (no){
        retorno = insereNovo_MN(listaResult,no->informacao,NULL);
        if (!retorno) printf("\n\n    ERRO AO INSERIR ELEMENTO NA LISTA 'RESULT'!\n\n");
        no = no->pai;
    }
    eliminaLista_MN(&lista);
    return listaResult;

}

int eliminaLista_MN(lista_MN *l){
    if (!(*l)) return 0;
    noLista_MN *p,*aux;
    p = aux = (*l)->head;
    while(p){
        aux = p;
        p=p->prox;
        free(aux);
    }
    (*l)->n = 0;
    free(*l);
    return 1;
}


int listaLista_MN(lista_MN l, int *caminho){
    float distanciaTotal;
    int i, cont = 1;
    char toString[15];
    if (!l) return 0;
    if (l->n == 0) {
        printf("\nLista sem registros!\n");
        return 0;
    }
    noLista_MN *aux, *ant;
    aux = l->head;
    ant = aux;

    while(aux){
        if(aux->informacao.cod>=10){
            printf("\n      |         %d        |",aux->informacao.cod);
        }else{
            printf("\n      |         %d         |",aux->informacao.cod);
        }
        
        caminho[aux->informacao.cod] = 1;
        ant = aux;
        aux = aux->prox;
        cont ++;
    }

    printf("\n      |                   |");

    return 1;
}
