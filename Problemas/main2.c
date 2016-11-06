#include <stdio.h>
#include <stdlib.h>
#include "Grafos.h"
#include "Árvore.h"
#include "ListaDinamica.h"
#include "ListaMenorCaminho.h"
#include <string.h>

int numReg(FILE *f){
    if (!f) return -1;
    char c;
    int num = 0;
    c = fgetc(f);
    while (!feof(f)){
        if (c=='\n')
            num++;
        c = fgetc(f);
    }
    return num+1;
}

int leituraArquivos(TAD_ABB *arvore,grafo **g){
    system("mode con:cols=120 lines=70");
    char strLongitude[10], strLatitude[10],strArq1[]="aeroportos.txt", strArq2[] = "conexoes.txt", nome[50];
	float longitude, latitude;
	int codigo, retorno, cod1, cod2, i;
	RegistroArvore reg;
	FILE *arqInfo, *arqConexoes;

    //Trabalhndo com o arquivo de informações
	arqInfo = fopen(strArq1, "r");
	if(arqInfo == NULL){
		printf("Erro, nao foi possivel abrir o arquivo %s\n", strArq1);
        return 0;
	}

    while(!feof(arqInfo)){
        fscanf(arqInfo,"%d", &codigo);  //Lendo codigo
        fgetc(arqInfo);              //Lendo ';'

        i=0;
        while ((nome[i]=fgetc(arqInfo)) != ';') //Lendo o nome
            i++;
        nome[i]='\0';

        i=0;
        while ((strLongitude[i]=fgetc(arqInfo)) != ';') //Lendo longitude
            i++;
        strLongitude[i]='\0';
        i=0;

        while ((strLatitude[i]=fgetc(arqInfo)) != '\n' &&
                (strLatitude[i]!=EOF))                  //Lendo latitude
            i++;
        strLatitude[i]='\0';

        //Convertendo para float
        longitude = atof(strLongitude);
        latitude = atof(strLatitude);

        reg.cod = codigo;
        strcpy(reg.chave,nome);
        reg.latitude = latitude;
        reg.longitude = longitude;

        retorno = TAD_ABB_inserir(*arvore,&reg);  //Inserindo registro lido
        //Verifica se o registro foi inserido com sucesso
        if (!retorno)
            printf("ERRO AO INSERIR NA ÁRVORE --> %d - %s",codigo,nome);
        else{
            //Inserindo vértice no grafo
            retorno = addVertice(*g,codigo);
            if (!retorno) {
                printf("ERRO AO INSERIR VERTICE --> %d - %s",codigo,nome);
                TAD_ABB_remover_no(*arvore,nome);
            }
        }
        //printf("%d;%s;%f;%f\n", reg.cod, reg.chave, reg.longitude, reg.latitude);
    }
    fclose(arqInfo);

    retorno = TAD_ABB_criarVetorCidades(*arvore);
    if (!retorno) printf("\n\nERRO AO CRIAR VETOR DE CIDADES!\n\n");

    //Trabalhando com o arquivo de conexões
    arqConexoes = fopen(strArq2, "r");
	if (arqConexoes == NULL) {
		printf("Erro, nao foi possivel abrir o arquivo %s\n", strArq2);
        return 0;
	}

    while (!feof(arqConexoes)) {
        fscanf(arqConexoes,"%d %d\n",&cod1,&cod2);
        retorno = adicAresta(*g,*arvore,cod1,cod2);
        if (!retorno)
            printf("\nERRO AO ADICIONAR ARESTA (%d, %d)!\n",cod1,cod2);
    }
    fclose(arqConexoes);
    return 1;
}


int main()
{
    //Declaração e inicialização de variáveis
    TAD_ABB arvore = ABB_inicializa();
    FILE *f = fopen("aeroportos.txt", "r");
    int tam = numReg(f);
    lista_MN lm;
    RegistroArvore *reg1, *reg2;
    grafo *g = criaGrafo(tam+1);
    fclose(f);

    char aeroporto1[30], aeroporto2[30];
	int opcao=0;

	//Leitura dos arquivos
    //Se não conseguir ler arquivos, sai da execução
    if (!(leituraArquivos(&arvore,&g))) {
        printf("\n\nERRO AO LER ARQUIVOS!\n\n");
        system("pause");
        exit(1);
    }

    //Menu de Opções
    while (opcao != 8) {
        printf("           ******************  Grafos - Aeroportos Brasileiros  *****************\n\n");
        TAD_ABB_exibeCidades(arvore);

        printf("\n  1 - Adiciona Conexao\n");
        printf("  2 - Remove Conexao\n");
        printf("  3 - Numero de Aeroportos\n");
        printf("  4 - Numero de conexoes de um Aeroporto\n");
        printf("  5 - Verificar conexao entre 2 Aeroportos\n");
        printf("  6 - Menor Caminho\n");
        printf("  7 - Listar conexoes de um Aeroporto\n");
        printf("  8 - Sair\n");
        printf("      Escolha uma opcao: ");
        scanf("%d",&opcao);
        fflush(stdin);
        switch (opcao){
            case 1:
            case 2:
            case 5:
            case 6:
                printf("\n      Informe o Aeroporto 1: ");
                gets(aeroporto1);

                reg1 = TAD_ABB_busca(arvore,aeroporto1);
                if (!reg1) {
                    printf("\n      Aeroporto nao encontrado: %s\n",aeroporto1);
                }else{
                    printf("      Informe o Aeroporto 2: ");
                    gets(aeroporto2);
                    reg2 = TAD_ABB_busca(arvore,aeroporto2);
                    if (!reg2)
                        printf("\n      Aeroporto nao encontrado: %s\n",aeroporto2);
                }

                if ((reg1) && (reg2)){

                    if (opcao == 1)
                        if (!(adicAresta(g,arvore,reg1->cod,reg2->cod))) printf("\n     Erro ao adicionar conexao!\n");

                    if (opcao == 2)
                        if (!(remAresta(g,reg1->cod,reg2->cod))) printf("\n      Erro ao remover conexao!\n");

                    if (opcao == 5) {
                        if (ehAdjacente(g,reg1->cod,reg2->cod))
                            printf("\n      %s e %s sao adjacentes (se conectam diretamente)\n",aeroporto1,aeroporto2);
                        else
                            printf("\n      %s e %s nao sao adjacentes (nao existe uma conexao direta entre eles)\n",aeroporto1,aeroporto2);
                    }

                    if (opcao == 6){
                        lm = menorCaminho(g,arvore,aeroporto1,aeroporto2);
                        if (lm) {
                            listaLista_MN(lm);
                            if (!(eliminaLista_MN(&lm))) printf("\n      ERRO AO ELIMINAR LISTA USADA PARA DEFINIR MENOR CAMINHO!\n");
                        }
                    }

                }
                break;

            case 3:
                printf("\n      Total de aeroportos: %d\n",TAD_ABB_num_nos(arvore));
                break;

            case 4:
                printf("\n      Digite o Aeroporto: ");
                gets(aeroporto1);
                reg1 = TAD_ABB_busca(arvore,aeroporto1);
                if (reg1) printf("\n      Numero total de conexoes: %d\n",grauVertice(g,reg1->cod));
                else printf("\n      Aeroporto nao encontrado!\n");
                break;

            case 7:
                printf("\n      Aeroporto: ");
                gets(aeroporto1);
                listaConexoes(g,arvore,aeroporto1);
                break;

            case 8:
                break;
            default:
                printf("\n      Opcao invalida!\n");
        }
        if (opcao!=8){
            system("pause");
            system("cls");
        }
    }
    if (!(TAD_ABB_libera_arvore(&arvore))) { printf("\n      ERRO AO LIBERAR ARVORE DE BUSCA!\n"); system("pause"); }
    if (!(destroiGrafo(&g))) { printf("\n      ERRO AO DESTROIR O GRAFO!\n"); system("pause"); }
	return 0;
}
