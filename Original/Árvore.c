#include "Árvore.h"
#include <string.h>
#include <math.h>
#define PI 3.14159265

typedef struct ABB_no  ABB_no;
struct ABB_no {
      RegistroArvore dado;
      ABB_no *esq;
      ABB_no *dir;
};
struct ABB {
   ABB_no *raiz;
   cidadesStr *cidades;
};

typedef struct ABB ABB;


char *TAD_ABB_buscaCidade(TAD_ABB arvore, int codigo){  //Dado um código, busca a cidade correpondente no Vetor de Cidades
    return arvore->cidades[codigo].nomeCidade;
 }


float calculaDistancia(RegistroArvore reg1, RegistroArvore reg2){
    return 6371*acos(cos(PI*(90-reg2.latitude)/180)*cos((90-reg1.latitude)*PI/180)+sin((90-reg2.latitude)*PI/180)*sin((90-reg1.latitude)*PI/180)*cos((reg1.longitude-reg2.longitude)*PI/180));
}

int ABB_altura(ABB_no *no){
    if (!no) return -1;
    int altDir, altEsq;
    altDir = ABB_altura(no->dir) + 1;
    altEsq = ABB_altura(no->esq) + 1;
    if (altDir > altEsq) return altDir;
    else return altEsq;
}

ABB_no *ABB_busca(ABB_no *no, char *chave){
    if (!no) return NULL;
    if (strcmp(chave, no->dado.chave)<0) return ABB_busca(no->esq,chave);
    else if (strcmp(chave, no->dado.chave)>0) return ABB_busca(no->dir,chave);
    else return no;
}

RegistroArvore *TAD_ABB_busca(TAD_ABB arvore, char *chave){
    ABB_no *no = ABB_busca(arvore->raiz,chave);
    if (!no) return NULL;
    return &no->dado;
}

int ABB_remover_no(ABB_no **no){
    ABB_no **aux,*aux2,*aux3;
    if (!(*no)->esq && !(*no)->dir){
        free(*no);
        (*no) = NULL;
        return 1;
    }
    if (!(*no)->esq){
        aux2 = *no;
        aux3 = (*no)->dir;
        free(aux2);
        *no = aux3;
        return 1;
    }
    if (!(*no)->dir){
        aux2 = *no;
        aux3 = (*no)->esq;
        free(aux2);
        *no = aux3;
        return 1;
    }
    aux = &(*no)->esq;
    while((*aux)->dir)
        aux = &(*aux)->dir;
    aux3 = (*aux)->esq;
    (*aux)->esq = ((*aux)==(*no)->esq) ? NULL : (*no)->esq;
    (*aux)->dir = (*no)->dir;
    aux2 = *no;
    *no = *aux;
    *aux = aux3;
    free(aux2);
    return 1;
}

int TAD_ABB_remover_no(TAD_ABB arvore, char *chave){
    ABB_no **no;
    no = &arvore->raiz;
    while (*no && strcmp((*no)->dado.chave,chave)){
        if (strcmp((*no)->dado.chave,chave)>0)
            no = &(*no)->esq;
        else if(strcmp((*no)->dado.chave,chave)<0)
            no = &(*no)->dir;
    }
    if (!(*no)) return 0;
    return ABB_remover_no(no);
}

int ABB_num_nos(ABB_no *no){
    if (!no)
        return 0;
    return ABB_num_nos(no->esq)+ABB_num_nos(no->dir) + 1;
}


int TAD_ABB_num_nos(TAD_ABB arvore){
    return ABB_num_nos(arvore->raiz);
}

int TAD_ABB_altura(TAD_ABB arvore){
    return ABB_altura(arvore->raiz);
}

int ABB_inserirNo(ABB_no** no,ABB_no *novo_no){
    if (!(*no)){
        *no = novo_no;
        return 1;
    }
    if (strcmp((*no)->dado.chave,novo_no->dado.chave)>0)
        return ABB_inserirNo(&(*no)->esq,novo_no);
    if (strcmp((*no)->dado.chave,novo_no->dado.chave)<0)
        return ABB_inserirNo(&(*no)->dir,novo_no);
    return 0;
}

int TAD_ABB_inserir(TAD_ABB arvore, RegistroArvore *novo_reg){
    ABB_no *novo_no;
    if (!(novo_no = (ABB_no *)malloc(sizeof(ABB_no)))) return 0;
    novo_no->dado = *novo_reg;
    novo_no->dir = novo_no->esq = NULL;
    return ABB_inserirNo(&(arvore->raiz),novo_no);
}

void ABB_percorrer_pre_ordem(ABB_no *no){
    if (!no) return;
    printf("%d\t%s\t%f\t%f\n",no->dado.cod,no->dado.chave,no->dado.longitude,no->dado.latitude);
    ABB_percorrer_pre_ordem(no->esq);
    ABB_percorrer_pre_ordem(no->dir);
}

void ABB_percorrer_pos_ordem(ABB_no *no){
    if (!no) return;
    ABB_percorrer_pos_ordem(no->esq);
    ABB_percorrer_pos_ordem(no->dir);
    printf("%d\t%s\t%f\t%f\n",no->dado.cod,no->dado.chave,no->dado.longitude,no->dado.latitude);
}

void ABB_percorrer_em_ordem(ABB_no *no){
    if (!no) return;
    ABB_percorrer_em_ordem(no->esq);
    printf("%d\t%s\t%f\t%f\n",no->dado.cod,no->dado.chave,no->dado.longitude,no->dado.latitude);
    ABB_percorrer_em_ordem(no->dir);
}

void TAD_ABB_pecorrer_pre_ordem(TAD_ABB arvore){
    ABB_percorrer_pre_ordem(arvore->raiz);
}

void TAD_ABB_pecorrer_pos_ordem(TAD_ABB arvore){
    ABB_percorrer_pos_ordem(arvore->raiz);
}

void TAD_ABB_pecorrer_em_ordem(TAD_ABB arvore){
    ABB_percorrer_em_ordem(arvore->raiz);
}


TAD_ABB ABB_inicializa(){
    ABB *arvore = (ABB *)malloc(sizeof(ABB));
    if (!(arvore))
        return NULL;
    arvore->raiz = NULL;
    arvore->cidades = NULL;
    return arvore;
}

int criaVetorCidadesAux(ABB_no *no,cidadesStr *cidades){
    if (!no) return 0;
    strcpy(cidades[no->dado.cod].nomeCidade,no->dado.chave);
    criaVetorCidadesAux(no->esq,cidades);
    criaVetorCidadesAux(no->dir,cidades);
    return 1;
}


int TAD_ABB_criarVetorCidades(TAD_ABB arvore){
    cidadesStr *cidades = (cidadesStr*)malloc(sizeof(struct cid)*(TAD_ABB_num_nos(arvore)+1));
    if (!(cidades)) return 0;
    int retorno = criaVetorCidadesAux(arvore->raiz,cidades);
    if (retorno){
        arvore->cidades = cidades;
        return 1;
    }
    return 0;
}

void TAD_ABB_exibeCidades(TAD_ABB arvore){
    int i,j;
    printf("\n      ");
    for (i=1;i<TAD_ABB_num_nos(arvore);i++){
        printf("%s",arvore->cidades[i].nomeCidade);
        for(j=strlen(arvore->cidades[i].nomeCidade);j<35;j++)
            printf(" ");
        if ((i%3)==0) printf("\n      ");
    }
    printf("\n\n");
}

int TAD_ABB_vazia(TAD_ABB arvore){
    if (!arvore->raiz) return 1;
    return 0;
}

void ABB_libera_arvore(ABB_no **no){
    if (!(*no)) return;
    ABB_libera_arvore(&(*no)->esq);
    ABB_libera_arvore(&(*no)->dir);
    free(*no);
    *no = NULL;
}

int TAD_ABB_libera_arvore(TAD_ABB *arvore){
    if (!arvore) return 0;
    ABB_libera_arvore(&(*arvore)->raiz);
    free((*arvore)->cidades);
    return 1;
}
