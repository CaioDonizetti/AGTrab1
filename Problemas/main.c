#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafos.h"
#include "ListaDinamica.h"
#include "ListaMenorCaminho.h"

int numReg(FILE *f){
    if (!f) return -1;

    int num = 0;

    fscanf(f,"%d\n",&num);

    return num;
}

int leituraArquivos(grafo **g, char *nomeArquivo){
    FILE *Arquivo;
    int cod1, cod2, retorno;

	Arquivo = fopen(nomeArquivo, "r");
	if(Arquivo == NULL){
		printf("Erro, nao foi possivel abrir o arquivo %s\n", nomeArquivo);
        return 0;
	}

    //lendo a primeira linha que não é uma aresta e sim qtd de vértice
    fscanf(Arquivo,"%d\n",&cod1);
    for(int i=1;i<=cod1;i++){
        retorno = addVertice(*g,i);
        if (!retorno) {
            printf("ERRO AO INSERIR VERTICE --> %d",i);
        }
    }

    printf("");

    while (!feof(Arquivo)) {
        fscanf(Arquivo,"%d %d\n",&cod1,&cod2);
        retorno = adicAresta(*g,cod1,cod2);
        if (!retorno)
            printf("\nERRO AO ADICIONAR ARESTA (%d, %d)!\n",cod1,cod2);
    }


    fclose(Arquivo);
    return 1;
}

int listandoMenorCaminho(grafo **g){
    lista_MN lm;
    int i=1, j=1, controle = 1;
    int origem = i;
    int destino = i+1;
    int *v1 = malloc ((numVertices(*g)+1) * sizeof (int));
    
    printf("\n\n      |      Vertices     |");
    printf("\n      |-------------------|");

    for(i=1;i<numVertices(*g);i++){
        if(origem != destino){
                        
            lm = menorCaminho(*g,origem,destino);

            if (lm) {
                listaLista_MN(lm, v1);
                if (!(eliminaLista_MN(&lm))) printf("\n      ERRO AO ELIMINAR LISTA USADA PARA DEFINIR MENOR CAMINHO!\n");
                origem = destino;
                controle = 1;
                for(j=1;j<=numVertices(*g);j++){
                    if(v1[j]!=1){
                        destino = j;
                        j=numVertices(*g);
                        controle = 0;
                    }
                    
                }
            } else {
                printf("Erro");
            }
        }
    }
    printf("\n      |-------------------|");
}


int main()
{
    char strArq1[]="Produto1.txt", strArq2[] = "Produto2.txt", strArq3[] = "Produto3.txt", strArq4[] = "Produto4.txt";
    lista_MN lm;

    FILE *P1 = fopen(strArq1, "r");
    int tam = numReg(P1);
    grafo *gp1 = criaGrafo(tam);
    fclose(P1);

    FILE *P2 = fopen(strArq2, "r");
    tam = numReg(P2);
    grafo *gp2 = criaGrafo(tam);
    fclose(P2);

    FILE *P3 = fopen(strArq3, "r");
    tam = numReg(P3);
    grafo *gp3 = criaGrafo(tam);
    fclose(P3);


    FILE *P4 = fopen(strArq4, "r");
    tam = numReg(P4);
    grafo *gp4 = criaGrafo(tam);
    fclose(P4);

    // Leitura dos arquivos
    // Se n�o conseguir ler arquivos, sai da execu��o
    if (!(leituraArquivos(&gp1,strArq1))) {
        printf("\n\nERRO AO LER ARQUIVO: %s!",strArq1);
        exit(1);
    }

    if (!(leituraArquivos(&gp2,strArq2))) {
        printf("\n\nERRO AO LER ARQUIVO: %s!",strArq2);
        exit(1);
    }

    if (!(leituraArquivos(&gp3,strArq3))) {
        printf("\n\nERRO AO LER ARQUIVO: %s!",strArq3);
        exit(1);
    }

    if (!(leituraArquivos(&gp4,strArq4))) {
        printf("\n\nERRO AO LER ARQUIVO: %s!",strArq4);
        exit(1);
    }

    printf("\n\nProduto 1");
    listandoMenorCaminho(&gp1);
    printf("\n\nProduto 2");
    listandoMenorCaminho(&gp2);
    printf("\n\nProduto 3");
    listandoMenorCaminho(&gp3);
    printf("\n\nProduto 4");
    listandoMenorCaminho(&gp4);
}