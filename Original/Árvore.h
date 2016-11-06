#ifndef _Arvore_
#define _Arvore_
#include <stdio.h>
#include <stdlib.h>


typedef struct cid{
    char nomeCidade[30];
} cidadesStr;

struct registro {
   int cod;
   char chave[30];
   float latitude;
   float longitude;
};

typedef struct registro RegistroArvore;

typedef struct ABB* TAD_ABB;

RegistroArvore *TAD_ABB_busca(TAD_ABB arvore, char *chave);
TAD_ABB ABB_inicializa();
int TAD_ABB_criarVetorCidades(TAD_ABB arvore);
float calculaDistancia(RegistroArvore reg1, RegistroArvore reg2);
int TAD_ABB_inserir(TAD_ABB arvore, RegistroArvore *novo_reg);
void TAD_ABB_pecorrer_pre_ordem(TAD_ABB arvore);
void TAD_ABB_pecorrer_em_ordem(TAD_ABB arvore);
void TAD_ABB_pecorrer_pos_ordem(TAD_ABB arvore);
char *TAD_ABB_buscaCidade(TAD_ABB arvore, int codigo);
void TAD_ABB_exibeCidades(TAD_ABB arvore);
int TAD_ABB_altura(TAD_ABB arvore);
int TAD_ABB_num_nos(TAD_ABB arvore);
int TAD_ABB_remover_no(TAD_ABB arvore, char *chave);
int TAD_ABB_vazia(TAD_ABB arvore);
int TAD_ABB_libera_arvore(TAD_ABB *arvore);

#endif // _
