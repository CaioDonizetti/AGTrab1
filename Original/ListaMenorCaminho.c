#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaMenorCaminho.h"
#include "Grafos.h"
#include "�rvore.h"

typedef struct mn{
    dado informacao;
    int flag;
    struct mn *prox, *pai;
} noLista_MN;

typedef struct nn{
    noLista_MN *head;
    int n, ord;
    char origem[30],destino[30];
    float distanciaAtual;
} noDescritor_MN;

lista_MN criaLista_MN(int k, char *cidadeOrigem, char *cidadeDestino){
    lista_MN aux;
    if((k<0)||(k>2)) return NULL;
    aux = (noDescritor_MN *)malloc(sizeof(noDescritor_MN));
    if(!(aux)) return NULL;
    strcpy(aux->origem, cidadeOrigem);
    strcpy(aux->destino,cidadeDestino);
    aux->head = NULL;
    aux->ord = k;
    aux->n = 0;
    aux->distanciaAtual = 0;
    return aux;
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
        if ((*aux)->informacao.codAeroporto == p->informacao.codAeroporto){ //Se esse elemento ja estiver na lista...
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

int removeNo_MN(lista_MN l,int codAeroporto){
    if (!l) return 0;
    noLista_MN *aux,*pant;
    aux = l->head;
    pant = l->head;
    while ((aux) && (aux->informacao.codAeroporto != codAeroporto)){
        pant = aux;
        aux = aux->prox;
    }
    if (aux){
        pant->prox = aux->prox;
        free(aux);
        l->n--;
        return 1;
    }
    return 0;
}

int buscaCodigo_MN(lista_MN l,int codigo, dado *dr){
    if (!l) return 0;
    noLista_MN *aux;
    aux = l->head;
    while((aux->prox) && (aux->informacao.codAeroporto != codigo))
        aux = aux->prox;
    if (aux->informacao.codAeroporto == codigo){
        *dr = aux->informacao;
        return 1;
    }
    return 0;
}

int listaLista_MN(lista_MN l){
    float distanciaTotal;
    int i, cont = 1;
    char toString[15],ord[4];
    if (!l) return 0;
    if (l->n == 0) {
        printf("\nLista sem registros!\n");
        return 0;
    }
    noLista_MN *aux, *ant;
    aux = l->head;
    ant = aux;
    printf("\n\n      | Or. | Cod. | Cidade                             | Dist. Cid. Anterior   | Distancia Parcial     |");
    printf("\n      |-------------------------------------------------------------------------------------------------|");
    while(aux){
        itoa(cont,ord,10);
        printf("\n      | %s",ord);
        for (i=strlen(ord);i<4;i++) printf(" ");
        distanciaTotal = aux->informacao.distancia;
        printf("| %d  ",aux->informacao.codAeroporto);
        if (aux->informacao.codAeroporto < 10) printf(" ");
        printf(" | %s",aux->informacao.cidade);
        for (i=strlen(aux->informacao.cidade);i<35;i++)
            printf(" ");
        sprintf(toString,"%.2f",(aux->informacao.distancia - ant->informacao.distancia));
        printf("| %s KM",toString);
        for (i=(strlen(toString)+3);i<22;i++)
            printf(" ");
        sprintf(toString,"%.2f",aux->informacao.distancia);
        printf("| %s KM",toString);
        for (i=(strlen(toString)+3);i<22;i++)
            printf(" ");
        printf("|");
        ant = aux;
        aux = aux->prox;
        cont ++;
    }
    printf("\n      |-------------------------------------------------------------------------------------------------|");
    printf("\n        DISTANCIA TOTAL: %.2f KM\n\n",distanciaTotal);
    return 1;
}

int qtdaElementos_MN(lista_MN l){
    if (!l) return -1;
    return l->n;
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


lista_MN menorCaminho(grafo *g, int origem,int destino){
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

    //Inserindo a cidade de origem
    dado inf;
    RegistroArvore *reg = TAD_ABB_busca(a,origem); //Busca informa��es da cidade de origem
    if (!reg){ printf("    ERRO AO BUSCAR CIDADE DE ORIGEM NA �RVORE!"); return NULL; }
    strcpy(inf.cidade, origem);
    inf.codAeroporto = reg->cod;
    inf.distancia = 0;
    insereNovo_MN(lista,inf, NULL);  //Insere na lista a cidade de origem
    retorno = menorElemento(lista,&no); //Procura o no que contem o menor elemento

    //Loop para encontrar o menor caminho
    while (strcmp(no->informacao.cidade,destino)){  //Enquanto o menor caminho n�o for o que leva � cidade de destino...

        if (!retorno) { printf("\n\n    NAO E POSSIVEL CHEGAR A %s SAINDO DE %s!\n\n",destino, origem); return NULL; }
        listaGrafo = retornaLista(g,no->informacao.codAeroporto);  //Retorna as conexoes da cidade com menor caminho atual...

        for (i=0;i<qtdaElementos(listaGrafo);i++){ //Para cada elemento da lista (que s�o as cidades conectada � cidade de menor distancia no mom...
            dadoLista = retornaInfo(listaGrafo,i);
            if (dadoLista){
                inf.codAeroporto = dadoLista->cod;
                inf.distancia = dadoLista->distancia;
                strcpy(inf.cidade,TAD_ABB_buscaCidade(a,dadoLista->cod));

                retorno = insereNovo_MN(lista,inf,no);
                if (!retorno) printf("    ERRO AO INSERIR ELEMENTO NA LISTA DE MENOR CAMINHO: Cidade %s",inf.cidade);
            }
        }

        retorno = menorElemento(lista,&no); //Procura o no que contem o menor elemento
    }

    //Criando nova lista para inserir as cidades encontradas por onde se deve passar no menor caminho
    lista_MN listaResult = (criaLista_MN(1,origem,destino)); //Inser��o pela cabe�a
    while (no){
        retorno = insereNovo_MN(listaResult,no->informacao,NULL);
        if (!retorno) printf("\n\n    ERRO AO INSERIR ELEMENTO NA LISTA 'RESULT'!\n\n");
        no = no->pai;
    }
    eliminaLista_MN(&lista);
    return listaResult;

}

